#include "s21_decimal.h"

int addition(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int owerflow = 0, err = 0;
  if (value_1.exp != value_2.exp) cast_scale(&value_1, &value_2);
  result->exp = value_2.exp;
  for (int BITi = 0; BITi <= 95; BITi++) {
    int x = get_bit(value_1, BITi);
    int y = get_bit(value_2, BITi);
    set_bit(result, BITi, ((x ^ y) ^ owerflow));
    owerflow = ((x + y + owerflow) > 1) ? 1 : 0;
    if (BITi == 95 && owerflow) {
      full_clean(result);
      err = 1;
    }
  }
  return err;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  full_clean(result);
  int err = 0;
  if (result != NULL) {
    if (value_1.exp > 28 || value_2.exp > 28) {
      err = 2;
    } else {
      int comp = compare_durex(value_1, value_2);
      if ((!value_1.sign && !value_2.sign) || (value_1.sign && value_2.sign)) {
        err = addition(value_1, value_2, result);
        if (value_1.sign && value_2.sign) result->sign = 1;
      } else if ((!value_1.sign && value_2.sign) ||
                 (value_1.sign && !value_2.sign)) {
        result->sign = (comp) ? value_2.sign : value_1.sign;
        err = (comp) ? subtraction(value_2, value_1, result)
                     : subtraction(value_1, value_2, result);
        if (!result->bits[0] && !result->bits[1] && !result->bits[2] &&
            result->sign)
          result->sign = 0;
      }
      err_clean(result, &err);
      check_empty(result);
    }
  }
  return err;
}
