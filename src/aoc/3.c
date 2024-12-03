#include "aoc/3.h"
#include "khg_utl/file_reader.h"
#include "khg_utl/string.h"
#include <ctype.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int parse_mul(utl_string *str, size_t pos, bool mul_on) {
  if (mul_on && str->data_str[pos] == 'm') {
    size_t beg_pos = pos + 4;
    size_t end_pos = beg_pos;
    while (isdigit(str->data_str[end_pos]) && end_pos - beg_pos < 3) {
      end_pos++;
    }
    char x_str[4] = {0};
    strncpy(x_str, str->data_str + beg_pos, end_pos - beg_pos);
    int x = atoi(x_str);
    if (str->data_str[end_pos] != ',') {
      pos = utl_string_find(str, "mul(", pos + 1);
      return 0;
    }
    end_pos++;
    beg_pos = end_pos;
    while (isdigit(str->data_str[end_pos]) && end_pos - beg_pos < 3) {
      end_pos++;
    }
    char y_str[4] = {0};
    strncpy(y_str, str->data_str + beg_pos, end_pos - beg_pos);
    int y = atoi(y_str);
    if (str->data_str[end_pos] != ')') {
      pos = utl_string_find(str, "mul(", pos + 1);
      return 0;
    }
    end_pos++;
    return x * y;
  }
  return 0;
}

static size_t find_next_and_toggle(utl_string *str, const size_t pos, bool *toggle) {
  size_t do_pos = utl_string_find(str, "do()", pos);
  size_t dont_pos = utl_string_find(str, "don't()", pos);
  size_t mul_pos = utl_string_find(str, "mul(", pos);
  if (do_pos != -1 && (dont_pos == -1 || do_pos < dont_pos) && (mul_pos == -1 || do_pos < mul_pos)) {
    *toggle = true;
    return do_pos + 4;
  }
  if (dont_pos != -1 && (do_pos == -1 || dont_pos < do_pos) && (mul_pos == -1 || dont_pos < mul_pos)) {
    *toggle = false;
    return dont_pos + 7;
  }
  return mul_pos;
}

void day0301(const char *input_path, const uint16_t num_lines) {
  printf("Advent of Code 2024: Day 3 Part 1\n");
  printf("Using file: %s\n", input_path);
  utl_file_reader *reader = utl_file_reader_open(input_path, UTL_READ_TEXT);
  char buffer[(int)pow(2, 16)];
  utl_file_reader_read(buffer, sizeof(char), sizeof(buffer) - 1, reader);
  utl_string *str_buffer = utl_string_create(buffer);
  size_t pos = utl_string_find(str_buffer, "mul(", 0);
  int sum = 0;
  while (pos != -1) {
    sum += parse_mul(str_buffer, pos, true);
    pos = utl_string_find(str_buffer, "mul(", pos + 1);
  }
  printf("Answer: %i\n", sum);
  utl_string_deallocate(str_buffer);
  utl_file_reader_close(reader);
};

void day0302(const char *input_path, const uint16_t num_lines) {
  printf("Advent of Code 2024: Day 3 Part 2\n");
  printf("Using file: %s\n", input_path);
  utl_file_reader* reader = utl_file_reader_open(input_path, UTL_READ_TEXT);
  char buffer[(int)pow(2, 16)];
  utl_file_reader_read(buffer, sizeof(char), sizeof(buffer) - 1, reader);
  utl_string *str_buffer = utl_string_create(buffer);
  size_t do_pos = utl_string_find(str_buffer, "do()", 0);
  size_t dont_pos = utl_string_find(str_buffer, "don't()", 0);
  size_t pos = utl_string_find(str_buffer, "mul(", 0);
  int sum = 0;
  bool mul_on = true;
  while (pos != -1) {
    sum += parse_mul(str_buffer, pos, mul_on);
    pos = find_next_and_toggle(str_buffer, pos + 1, &mul_on);
  }
  printf("Answer: %i\n", sum);
  utl_string_deallocate(str_buffer);
  utl_file_reader_close(reader);
};

