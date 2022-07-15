#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int err = 0;
  if ((src == 1 / 0.0 || src == 0 / 0.0 || src == -1 / 0.0 ||
       src == -0 / 0.0) ||
      dst == NULL) {
    err = 1;
  } else if (src) {
    full_clean(dst);
    if (src < 0) {
      dst->sign = 1;
      src = -src;
    }
    dst->bits[0] = src;
  } else {
    full_clean(dst);
  }
  return err;
}
