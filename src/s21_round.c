#include "s21_decimal.h"

s21_decimal rnd(s21_decimal value, s21_decimal *tmp) {
  s21_decimal v1 = {{0, 0, 0, 0}}, v2 = {{0, 0, 0, 0}}, res = {{0, 0, 0, 0}};
  s21_truncate(value, &v1);  // greater
  --value.exp;
  s21_truncate(value, &v2);  //  less
  mult_ten(&v1);             // 14
  s21_sub(v2, v1, tmp);
  ++value.exp;
  s21_truncate(value, &res);
  return res;
}

void s21_roundBank(s21_decimal value, s21_decimal *result) {
  fullclean(result);
  s21_decimal one = {{1}};
  s21_decimal res = {0};
  int rem = 0;
  s21_truncate(value, result);
  subtraction(value, *result, &res);
  res.exp = value.exp - 1;
  s21_from_decimal_to_int(res, &rem);
  if (rem > 5) {
    s21_add(one, *result, result);
  }
  if (rem == 5) {
    if (get_bit(*result, 0)) s21_add(one, *result, result);
  }
}

int s21_round(s21_decimal value, s21_decimal *result) {
  fullclean(result);
  s21_decimal tmp = {{0, 0, 0, 0}}, one = {{1, 0, 0, 0}};
  int err = 0;
  if (result == NULL || value.exp > 28) err = 1;
  if (!err) {
    if (value.exp) {
      *result = rnd(value, &tmp);
      if (tmp.mantysa[0] >= 5 && value.sign)
        s21_sub(*result, one, result);
      else if (tmp.mantysa[0] >= 5 && !value.sign)
        s21_add(*result, one, result);
    } else {
      *result = value;
    }
  }
  return err;
}
