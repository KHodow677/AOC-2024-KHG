#include "aoc/3.h"
#include "khg_utl/file_reader.h"
#include <stdint.h>
#include <stdio.h>

void day0301(const char *input_path, const uint16_t num_lines) {
  printf("Advent of Code 2024: Day 3 Part 1\n");
  printf("Using file: %s\n", input_path);
  utl_file_reader *reader = utl_file_reader_open(input_path, UTL_READ_TEXT);
  utl_file_reader_close(reader);
};

void day0302(const char *input_path, const uint16_t num_lines) {
  printf("Advent of Code 2024: Day 3 Part 2\n");
  printf("Using file: %s\n", input_path);
  utl_file_reader* reader = utl_file_reader_open(input_path, UTL_READ_TEXT);
  utl_file_reader_close(reader);
};
