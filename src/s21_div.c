#include "s21_decimal.h"

void s21_div_int(s21_decimal dividend, s21_decimal divisor,
                 s21_decimal *quotient, s21_decimal *rem) {
  s21_decimal original_divisor = divisor;
  shift_left(&divisor, (get_first_bit(dividend) - get_first_bit(divisor)));
  if (s21_is_greater_or_equal(dividend, divisor)) {
    set_bit(quotient, 0, 1);
    s21_sub(dividend, divisor, rem);
  } else {
    *rem = dividend;
  }

  while (s21_is_not_equal(divisor, original_divisor)) {
    shift_right(&divisor, 1);
    if (s21_is_greater_or_equal(*rem, divisor)) {
      shift_left(quotient, 1);
      set_bit(quotient, 0, 1);
      s21_sub(*rem, divisor, rem);
    } else {
      shift_left(quotient, 1);
    }
  }
}

s21_decimal div_only_bits(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal res = {{0, 0, 0}}, rem = {{0, 0, 0}};
  for (int i = get_first_bit(value_1); i >= 0; i--) {
    if (get_bit(value_1, i)) set_bit(&rem, 0, 1);
    if (s21_is_greater_or_equal(rem, value_2)) {
      subtraction(rem, value_2, &rem);
      if (i != 0) shift_left(&rem, 1);
      if (get_bit(value_1, i - 1)) set_bit(&rem, 0, 1);
      shift_left(&res, 1);
      set_bit(&res, 0, 1);
    } else {
      shift_left(&res, 1);
      if (i != 0) shift_left(&rem, 1);
      if (i - 1 >= 0 && get_bit(value_1, i - 1)) set_bit(&rem, 0, 1);
    }
  }
  return res;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  full_clean(result);
  s21_decimal tmp = {{1, 0, 0, 0}}, divisor = value_2, dividend = value_1,
              quotient = {{0}};
  int err = 0, sign = 1;
  if (result != NULL) {
    if (value_1.sign == value_2.sign) sign = 0;
    divisor.sign = 0;
    dividend.sign = 0;
    if (get_first_bit(value_2) == -1) {
      err = 3;
    } else if (get_first_bit(value_1) == -1) {
      full_clean(result);
    } else if ((get_first_bit(value_1) == 95 && s21_is_less(divisor, tmp) &&
                sign) ||
               (get_first_bit(value_2) == 95 && s21_is_less(dividend, tmp) &&
                sign)) {
      err = 1;
    } else if ((get_first_bit(value_1) == 95 && s21_is_less(divisor, tmp) &&
                !sign) ||
               (get_first_bit(value_2) == 95 && s21_is_less(dividend, tmp) &&
                !sign)) {
      err = 2;
    } else if (value_1.exp > 28 || value_2.exp > 28) {
      err = 2;
    } else if (get_first_bit(value_1) == -1) {
      clean(&quotient);
      sign = 0;
    } else if (s21_is_equal(dividend, divisor)) {
      clean(&quotient), quotient.mantysa[0] = 1;
    } else if (get_first_bit(value_2) == 0) {
      quotient = value_1;
    } else {
      err = cast_scale(&dividend, &divisor);
      while (!s21_is_less_or_equal(divisor, dividend) && !err) {
        if (quotient.exp < 28 && get_first_bit(dividend) < 96) {
          mult_ten(&dividend);
          quotient.exp++;
        } else {
          err = 2;
          full_clean(result);
          break;
        }
      }
      while (!err) {
        s21_div_int(dividend, divisor, &quotient, &tmp);
        if (get_first_bit(tmp) != -1) {
          if (quotient.exp < 28 && get_first_bit(dividend) < 90) {
            mult_ten(&dividend);
            quotient.exp++;
            clean(&quotient);
            clean(&tmp);
          } else {
            break;
          }
        } else {
          break;
        }
      }
    }
    quotient.sign = sign;
    if (!err) (*result) = quotient;
    err_clean(result, &err);
  }
  return err;
}
