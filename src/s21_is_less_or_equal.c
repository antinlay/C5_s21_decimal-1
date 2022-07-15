
#include "s21_decimal.h"
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int err = 0;
  if (value_1.exp > 28 || value_2.exp > 28) {
    err = 0;
  } else {
    if ((value_1.sign == 1 && value_2.sign == 0) ||
        s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2))
      err = 3;
  }
  return err > 2 ? 1 : 0;
}
