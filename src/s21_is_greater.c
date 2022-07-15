#include "s21_decimal.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int err = 0;
  if (value_1.exp > 28 || value_2.exp > 28) {
    err = 0;
  } else {
    if (s21_is_less(value_2, value_1)) err = 1;
  }
  return err;
}
