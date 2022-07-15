#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  fullclean(result);
  int err = 0;
  s21_decimal ten = {{10, 0, 0, 0}};
  if (result == NULL || value.exp > 28) err = 1;
  if (!err) {
    if (value.sign) result->sign = 1;
    if (value.exp) {
      value.sign = 0;
      for (int i = value.exp; i > 0; i--) {
        value = div_only_bits(value, ten);
      }
    }
    cp_mantysa(value, result);
    result->exp = 0;
  }
  return err;
}
