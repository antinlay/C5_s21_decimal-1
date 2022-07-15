#include "s21_decimal.h"

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  int err = 1;
  if (value_1.exp > 28 || value_2.exp > 28) {
    err = 0;
  } else {
    if (s21_is_equal(value_1, value_2)) err = 0;
  }
  return err;
}
