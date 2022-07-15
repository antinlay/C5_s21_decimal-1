#include "s21_decimal.h"

int mult_ten(s21_decimal *value) {
  int err = 0;
  s21_decimal v1 = *value, v2 = *value;
  if (shift_left(&v1, 1) || shift_left(&v2, 3) || addition(v1, v2, value))
    err = 1;
  return err;
}

int round_one(s21_decimal value, s21_decimal *result) {
  int err = 0;
  if (value.exp == 0) {
    err = 1;
  } else {
    s21_decimal tmp = value;
    tmp.exp = 1;
    s21_round(tmp, result);
    (*result).exp = value.exp - 1;
  }
  return err;
}

int multiply(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = 0;
  full_clean(result);
  if (get_first_bit(value_1) != -1 && get_first_bit(value_2) != -1) {
    for (int i = 0; i < 95; i++) {
      s21_decimal temp = value_1;
      if (get_bit(value_2, i) == 1) {
        if (shift_left(&temp, i)) err = 1;
        addition(temp, *result, result);
      }
    }
  }
  return err;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = 0;
  s21_decimal x = value_1, y = value_2, z = {{0}};
  if (result != NULL) {
    if (value_1.exp > 28 || value_2.exp > 28) {
      err = 2;
    } else {
      if (!err) {
        while (1) {
          if (((multiply(x, y, &z) == 1) || (x.exp + y.exp > 28)) && err == 0) {
            err = 1;
            if (get_first_bit(x) - get_first_bit(y) <= 0 && (x.exp < y.exp)) {
              if (round_one(y, &y)) err = 1;
            } else {
              if (round_one(x, &x)) err = 1;
            }
          } else {
            break;
          }
        }
        *result = z;
        (*result).exp = x.exp + y.exp;
        (*result).sign = -(value_1.sign - value_2.sign);
        err_clean(result, &err);
      }
    }
  }
  return err;
}
