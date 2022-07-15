
#include "s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int err = 0, tmp = get_first_bit(value_1) + get_first_bit(value_2);
  if (value_1.exp > 28 || value_2.exp > 28) {
    err = 0;
  } else {
    if (tmp != -2) {
      if (value_1.sign == 1 && value_2.sign == 0) {
        err = 1;
      } else if (value_1.sign == value_2.sign) {
        cast_scale(&value_1, &value_2);
        for (int i = 95; i >= 0; i--) {
          tmp = get_bit(value_1, i) - get_bit(value_2, i);
          if (value_1.sign == 0) {
            if (tmp == 1) i = -1;
            if (tmp == -1) err = 1, i = -1;
          } else {
            if (tmp == -1) i = -1;
            if (tmp == 1) err = 1, i = -1;
          }
        }
      }
    }
  }
  return err;
}
