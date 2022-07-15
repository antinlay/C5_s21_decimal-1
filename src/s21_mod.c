#include "s21_decimal.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  fullclean(result);
  s21_decimal tmp = {{1}};
  int err = 0, sign = 0;
  if (result != NULL) {
    if (value_1.exp > 28 || value_2.exp > 28) {
      err = 2;
    } else {
      if (!check_decimal(value_1) && !check_decimal(value_2)) {
        if ((value_1.sign && value_2.sign)) sign = 1;
        value_1.sign = 0;
        value_2.sign = 0;
        if (get_first_bit(value_2) == -1) {
          err = 3;
        } else if (get_first_bit(value_1) == -1 ||
                   s21_is_equal(value_1, value_2)) {
          fullclean(result);
        } else {
          cast_scale(&value_1, &value_2);
          s21_div_int(value_1, value_2, &tmp, result);
          (*result).sign = sign;
        }
      } else {
        err = 1;
      }
    }
  }
  return err;
}
