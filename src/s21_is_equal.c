#include "s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int err = 1;
  if (value_1.exp > 28 || value_2.exp > 28) {
    err = 0;
  } else {
    if ((get_first_bit(value_1) + get_first_bit(value_2)) != 0) {
      if (value_1.sign != value_2.sign) {
        err = 0;
      } else {
        cast_scale(&value_1, &value_2);
        for (int i = 95; i >= 0; i--) {
          if (get_bit(value_1, i) != get_bit(value_2, i)) err = 0, i = -1;
        }
      }
    }
  }
  return err;
}
