#include "s21_decimal.h"

void err_clean(s21_decimal *value, int *err) {
  if (*err) {
    if (value->sign) *err = 2;
    fullclean(value);
  }
}

int check_decimal(s21_decimal value) {
  int err = 0;
  if (value.exp > 28 || value.sign > 1 || value.mjNotUse != 0 ||
      value.jrNotUse != 0)
    err = 1;
  return err;
}

void check_empty(s21_decimal *value) {
  if (get_first_bit(*value) == -1) fullclean(value);
}

int shift_left(s21_decimal *value, int moves) {
  int err = 0;
  s21_decimal tmp = *value;
  for (int i = 0; i < moves; i++) {
    for (int j = 95; j > 0; j--) {
      if (j == 95 && get_bit(tmp, j)) {
        err = 1, j = -1;  // overflow
      } else {
        set_bit(&tmp, j, get_bit(tmp, j - 1));
      }
    }
    set_bit(&tmp, 0, 0);
  }
  if (err == 0) *value = tmp;
  return err;
}

int shift_right(s21_decimal *value, int moves) {
  int err = 0;
  s21_decimal tmp = *value;
  for (int i = 0; i < moves; i++) {
    for (int j = 0; j < 95; j++) {
      if (j == 0 && get_bit(tmp, j))
        err = 1, j = 96;  // overflow
      else
        set_bit(&tmp, j, get_bit(tmp, j + 1));
    }
    set_bit(&tmp, 95, 0);
  }
  if (err == 0) *value = tmp;
  return err;
}

int cast_scale(s21_decimal *value_1, s21_decimal *value_2) {
  int err = 0;
  int ower = 0;
  s21_decimal *minExp = (value_1->exp < value_2->exp) ? value_1 : value_2;
  s21_decimal v1 = {{0}};
  s21_decimal v2 = {{0}};
  if (value_1->exp > 28 || value_2->exp > 28) {
    err = 2;
  } else {
    int deltaScale = value_1->exp - value_2->exp;
    if (deltaScale < 0) deltaScale = -deltaScale;
    int limitDec = 95 - lastBitDec(*minExp);
    int checkScale = deltaScale * 3;
    int check = (checkScale > limitDec) ? 0 : 1;
    if (check) {
      if (deltaScale != 0) {
        if (deltaScale < 0) deltaScale *= -1;
        for (int i = 0; i < deltaScale; i++) {
          v1 = *minExp;
          v2 = *minExp;
          shift_left(&v1, 1);
          shift_left(&v2, 3);
          ower = addition(v1, v2, minExp);
        }
        minExp->exp =
            (value_1->exp < value_2->exp) ? value_2->exp : value_1->exp;
      }
    }
    if (!check || ower) err = 1;
  }
  return err;
}
