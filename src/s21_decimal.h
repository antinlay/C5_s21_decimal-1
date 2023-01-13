#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <math.h>
#include <stdio.h>

typedef union {
  unsigned int bits[4];
  struct {
    unsigned int mantysa[3];
    unsigned int jrNotUse : 16;
    unsigned int exp : 8;
    unsigned int mjNotUse : 7;
    unsigned int sign : 1;
  };
} s21_decimal;

typedef union {
  float f;
  unsigned int i;
  struct {
    unsigned int mntsa : 23;
    unsigned int exp : 8;
    unsigned int sign : 1;
  };
} s21_float;

int shift_left(s21_decimal *value, int moves);
int shift_right(s21_decimal *value, int moves);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// bit functions
int bit_num(int bit);
int int_num(int bit);
int last_bit_dec(s21_decimal src);
int get_first_bit(s21_decimal value);
int get_bit(s21_decimal src, int bitNum);
int compare_durex(s21_decimal value_1, s21_decimal value_2);
void clean(s21_decimal *value);
void full_clean(s21_decimal *value);
void set_bit(s21_decimal *decVal, int bit, int bin);
void cp_mantysa(s21_decimal value_1, s21_decimal *value_2);
// shift functions
int check_decimal(s21_decimal value);
int cast_scale(s21_decimal *value_1, s21_decimal *value_2);
void check_empty(s21_decimal *value);
void err_clean(s21_decimal *value, int *err);
// additional functions
int subtraction(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int addition(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int multiply(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int mult_ten(s21_decimal *value);
void round_bank(s21_decimal value, s21_decimal *result);
void s21_div_int(s21_decimal dividend, s21_decimal divisor,
                 s21_decimal *quotient, s21_decimal *rem);
s21_decimal rnd(s21_decimal value, s21_decimal *tmp);
s21_decimal div_only_bits(s21_decimal value_1, s21_decimal value_2);

#endif  // SRC_S21_DECIMAL_H_
