#include "s21_decimal.h"

int subtraction(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int owerflow = 0, err = 0;
  int cast = 0;
  if (value_1.exp != value_2.exp) cast = cast_scale(&value_1, &value_2);
  if (cast) {
    round_bank(value_2, &value_2);
    cast_scale(&value_1, &value_2);
  }
  result->exp = value_2.exp;
  for (int BITi = 0; BITi <= 95; BITi++) {
    int x = get_bit(value_1, BITi);
    int y = get_bit(value_2, BITi);
    set_bit(result, BITi, (x ^ y ^ owerflow));
    if (!x && y) {
      owerflow = 1;
    }
    if (x && !y) {
      owerflow = 0;
    }
  }
  if (owerflow) err = 2;
  return err;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  full_clean(result);
  int err = 0;
  if (result != NULL) {
    if (value_1.exp > 28 || value_2.exp > 28) {
      err = 2;
    } else {
      err = cast_scale(&value_1, &value_2);
      int comp = compare_durex(value_1, value_2);
      if (s21_is_equal(value_1, value_2)) {
        clean(result);
      } else if (!value_1.sign && !value_2.sign) {
        if (comp) {
          err = subtraction(value_2, value_1, result);
          result->sign = 1;
        } else {
          err = subtraction(value_1, value_2, result);
        }
      } else if ((!value_1.sign && value_2.sign)) {
        err = addition(value_2, value_1, result);
      } else if (value_1.sign && !value_2.sign) {
        value_1.sign = 0;
        err = addition(value_1, value_2, result);
        result->sign = 1;
      } else if (value_1.sign && value_2.sign) {
        if (comp) {
          err = subtraction(value_2, value_1, result);
        } else {
          err = subtraction(value_1, value_2, result);
          result->sign = 1;
        }
      }
      err_clean(result, &err);
    }
  }
  return err;
}
