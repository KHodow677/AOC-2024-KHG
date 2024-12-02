#include "aoc/1.h"
#include "khg_utl/array.h"
#include "khg_utl/file_reader.h"
#include "khg_utl/map.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

static int compare_ints_arr(const void* a, const void* b) {
  return (*(int*)a - *(int*)b);
}

static int compare_ints_map(const utl_key_type a, const utl_key_type b) {
  const int* ia = (const int*)a;
  const int* ib = (const int*)b;
  return (*ia - *ib);
}

void day0101(const char *input_path, const uint16_t num_lines) {
  printf("Advent of Code 2024: Day 1 Part 1\n");
  printf("Using file: %s\n", input_path);
  utl_file_reader *reader = utl_file_reader_open(input_path, UTL_READ_TEXT);
  utl_array *arr1 = utl_array_create(sizeof(int), num_lines);
  utl_array *arr2 = utl_array_create(sizeof(int), num_lines);
  int num1, num2, count = 0;
  char buffer[256];
  while (utl_file_reader_read_line(buffer, sizeof(buffer), reader)) {
    printf("buffer: %s\n", buffer);
    if (sscanf(buffer, "%i\t%i", &num1, &num2) == 2) {
      utl_array_set(arr1, count, &num1);
      utl_array_set(arr2, count, &num2);
      count++;
    } 
  }
  utl_array_sort(arr1, compare_ints_arr);
  utl_array_sort(arr2, compare_ints_arr);
  int total_distance = 0;
  for (int i = 0; i < num_lines; i++) {
    total_distance += abs(*(int *)utl_array_at(arr1, i) - *(int *)utl_array_at(arr2, i));
  }
  printf("Answer: %i\n", total_distance);
  utl_array_deallocate(arr1);
  utl_array_deallocate(arr2);
  utl_file_reader_close(reader);
};

void day0102(const char *input_path, const uint16_t num_lines) {
  printf("Advent of Code 2024: Day 1 Part 2\n");
  printf("Using file: %s\n", input_path);
  utl_file_reader* reader = utl_file_reader_open(input_path, UTL_READ_TEXT);
  utl_array *arr1 = utl_array_create(sizeof(int), num_lines);
  utl_array *arr2 = utl_array_create(sizeof(int), num_lines);
  int num1, num2, count = 0;
  char buffer[256];
  while (utl_file_reader_read_line(buffer, sizeof(buffer), reader)) {
    if (sscanf(buffer, "%i\t%i", &num1, &num2) == 2) {
      utl_array_set(arr1, count, &num1);
      utl_array_set(arr2, count, &num2);
      count++;
    } 
  }
  utl_map *freq_table = utl_map_create(compare_ints_map, free, free);
  for (int i = 0; i < num_lines; i++) {
    int num = *(int *)utl_array_at(arr2, i);
    int *val = utl_map_at(freq_table, &num);
    if (val == NULL) {
      int *idx = malloc(sizeof(int));
      int *freq = malloc(sizeof(int));
      *idx = num;
      *freq = 1;
      utl_map_insert(freq_table, idx, freq);
    }
    else {
      (*val)++;
    }
  }
  int similarity_score = 0;
  for (int i = 0; i < num_lines; i++) {
    int num = *(int *)utl_array_at(arr1, i);
    int *freq = (int *)utl_map_at(freq_table, &num);
    if (!freq) {
      continue;
    }
    similarity_score += num * (*freq);
  }
  printf("Answer: %i\n", similarity_score);
  utl_map_deallocate(freq_table);
  utl_array_deallocate(arr1);
  utl_array_deallocate(arr2);
  utl_file_reader_close(reader);
};

