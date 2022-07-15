#include "s21_decimal.h"

int bit_num(int bit) { return bit % 32; }
int int_num(int bit) { return bit / 32; }

int lastBitDec(s21_decimal src) {
  int num = 0;
  for (int i = 95; i >= 0; i--) {
    if (get_bit(src, i)) {
      num = i;
      break;
    }
  }
  return num;
}

int get_bit(s21_decimal decVal, int bit) {
  int res = 0;
  if (int_num(bit) < 4) {
    unsigned int mask = 1 << bit_num(bit);
    res = decVal.bits[int_num(bit)] & mask;
  }
  return !!res;
}

void set_bit(s21_decimal *decVal, int bit, int bin) {
  unsigned int mask = 1u << (bit_num(bit));
  if (int_num(bit) < 4 && bin) {
    decVal->bits[int_num(bit)] |= mask;
  } else if (int_num(bit) < 4 && !bin) {
    decVal->bits[int_num(bit)] &= ~mask;
  }
}

int get_first_bit(s21_decimal value) {
  int i = -1;
  for (i = 95; i >= 0; i--) {
    if (get_bit(value, i)) break;
  }
  return i;
}

void cp_mantysa(s21_decimal value_1, s21_decimal *value_2) {
  value_2->mantysa[0] = value_1.mantysa[0];
  value_2->mantysa[1] = value_1.mantysa[1];
  value_2->mantysa[2] = value_1.mantysa[2];
}

int compare_durex(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  s21_decimal x = value_1, y = value_2;
  x.sign = 0, y.sign = 0;
  result = s21_is_less_or_equal(x, y);
  return result;
}

void clean(s21_decimal *value) {
  value->bits[0] = 0;
  value->bits[1] = 0;
  value->bits[2] = 0;
}

void fullclean(s21_decimal *value) {
  clean(value);
  value->bits[3] = 0;
}
