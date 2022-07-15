#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int err = 0;
  int scale = 0;
  if ((src == 1 / 0.0 || src == 0 / 0.0 || src == -1 / 0.0 ||
       src == -0 / 0.0) ||
      dst == NULL) {
    err = 1;
  } else if (src) {
    fullclean(dst);
    s21_float floatDigit = {0};
    floatDigit.f = src;
    if ((dst->sign = floatDigit.sign)) {
      floatDigit.f = -floatDigit.f;
    }
    int expFloat = floatDigit.exp - 127;
    double dbl = floatDigit.f;
    while (scale < 28 && (int)dbl / (int)pow(2, 21) == 0) {
      dbl *= 10;
      scale++;
    }
    dbl = round(dbl);
    if (scale <= 28 && (expFloat > -94 && expFloat < 96)) {
      while (fmod(dbl, 10) == 0 && scale > 0) {
        dbl /= 10;
        scale--;
      }
      floatDigit.f = dbl;
      expFloat = floatDigit.exp - 127;
      set_bit(dst, expFloat, 1);
      int bitFloat = 0;
      for (int mantis = 22; mantis >= 0; mantis--) {
        bitFloat = (floatDigit.i >> mantis) & 1;
        set_bit(dst, --expFloat, bitFloat);
      }
      dst->exp = scale;
    } else {
      err = 1;
    }
  } else {
    fullclean(dst);
  }
  return err;
}
