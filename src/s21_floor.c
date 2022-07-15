#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int err = 0;
  if (result == NULL || value.exp > 28) err = 1;
  if (!err) {
    fullclean(result);
    s21_decimal one = {{1}};
    s21_decimal res = {0};
    s21_decimal zero = {0};
    s21_truncate(value, result);
    if (value.sign) {
      subtraction(value, *result, &res);
      res.exp = 0;
      if (!s21_is_equal(res, zero)) {
        addition(one, *result, result);
      }
      result->sign = 1;
    }
  }
  return err;
}
