#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int err = 0;
  s21_truncate(src, &src);
  if (dst == NULL) {
    err = 1;
  } else {
    if (src.mantysa[0] <= INT32_MAX && !src.mantysa[1] && !src.mantysa[2]) {
      *dst = src.mantysa[0];
      if (src.sign) *dst *= -1;
      err = 0;
    } else {
      err = 1;
      *dst = 0;
    }
  }
  return err;
}
