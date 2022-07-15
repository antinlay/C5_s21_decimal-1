#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int err = 0;
  if (dst != NULL) {
    *dst = 0;
    for (int i = 0; i < 96; i++) {
      if (get_bit(src, i)) {
        *dst += pow(2, i);
      }
    }
    while (src.exp != 0) {
      *dst /= 10;
      src.exp--;
    }
    if (src.sign) *dst = -*dst;
  } else {
    err = 1;
  }
  return err;
}
