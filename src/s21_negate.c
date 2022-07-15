#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  full_clean(result);
  int err = 0;
  if (result == NULL || value.exp > 28) err = 1;
  if (!err) {
    *result = value;
    if (!result->mantysa[0] && !result->mantysa[1] && !result->mantysa[2]) {
      result->sign = 0;
    } else {
      result->sign = ~result->sign;
    }
  }
  return err;
}
