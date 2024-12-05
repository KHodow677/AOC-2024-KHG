#include "aoc/2.h"
#include "khg_utl/file_reader.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool is_safe(int *levels, int size) {
  bool only_pos_diff = true, only_neg_diff = true;
  for (int i = 0; i < size - 1; i++) {
    int diff = levels[i] - levels[i + 1];
    only_pos_diff &= (diff < 0 && abs(diff) <= 3);
    only_neg_diff &= (diff > 0 && abs(diff) <= 3);
    if (abs(diff) == 0 || abs(diff) > 3 || (only_pos_diff == only_neg_diff)) {
      return false;
    }
  }
  return true;
}

void day0201(const char *input_path, const uint16_t num_lines) {
  printf("Advent of Code 2024: Day 2 Part 1\n");
  printf("Using file: %s\n", input_path);
  utl_file_reader *reader = utl_file_reader_open(input_path, UTL_READ_TEXT);
  int count = 0;
  char buffer[256];
  while (utl_file_reader_read_line(buffer, sizeof(buffer), reader)) {
    int levels[256];
    int size = 0;
    char *token = strtok(buffer, " ");
    while (token) {
      levels[size++] = atoi(token);
      token = strtok(NULL, " ");
    }
    if (is_safe(levels, size)) {
      count++;
    }
  }
  printf("Answer: %i\n", count);
  utl_file_reader_close(reader);
};

void day0202(const char *input_path, const uint16_t num_lines) {
  printf("Advent of Code 2024: Day 2 Part 2\n");
  printf("Using file: %s\n", input_path);
  utl_file_reader *reader = utl_file_reader_open(input_path, UTL_READ_TEXT);
  int count = 0;
  char buffer[256];
  while (utl_file_reader_read_line(buffer, sizeof(buffer), reader)) {
    int levels[256];
    int size = 0;
    char *token = strtok(buffer, " ");
    while (token) {
      levels[size++] = atoi(token);
      token = strtok(NULL, " ");
    }
    if (is_safe(levels, size)) {
      count++;
      continue;
    }
    bool actually_safe = false;
    for (int i = 0; i < size; i++) {
      int temp_levels[256];
      int temp_size = 0;
      for (int j = 0; j < size; j++) {
        if (j != i) {
          temp_levels[temp_size++] = levels[j];
        }
      }
      if (is_safe(temp_levels, temp_size)) {
        actually_safe = true;
        break;
      }
    }
    count += actually_safe;
  }
  printf("Answer: %i\n", count);
  utl_file_reader_close(reader);
}

