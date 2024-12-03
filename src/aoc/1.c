#include "aoc/1.h"
#include "khg_utl/algorithm.h"
#include "khg_utl/file_reader.h"
#include "khg_utl/map.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static int compare_ints(const void *a, const void *b) {
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
  const char *delimiter = "   ";
  utl_file_reader *reader = utl_file_reader_open(input_path, UTL_READ_TEXT);
  int arr1[num_lines];
  int arr2[num_lines];
  int *arrs[2] = { arr1, arr2 };
  int count = 0;
  char buffer[256];
  while (utl_file_reader_read_line(buffer, sizeof(buffer), reader)) {
    char *token = strtok(buffer, delimiter);
    int num_count = 0;
    while (token) {
      int num = atoi(token);
      arrs[num_count][count] = num;
      token = strtok(NULL, delimiter);
      num_count++;
    }
    count++;
  }
  utl_algorithm_sort(arr1, num_lines, sizeof(int), compare_ints);
  utl_algorithm_sort(arr2, num_lines, sizeof(int), compare_ints);
  int total_distance = 0;
  for (int i = 0; i < num_lines; i++) {
    total_distance += abs(arrs[0][i] - arrs[1][i]);
  }
  printf("Answer: %i\n", total_distance);
  utl_file_reader_close(reader);
};

void day0102(const char *input_path, const uint16_t num_lines) {
  printf("Advent of Code 2024: Day 1 Part 2\n");
  printf("Using file: %s\n", input_path);
  const char *delimiter = "   ";
  utl_file_reader* reader = utl_file_reader_open(input_path, UTL_READ_TEXT);
  int arr1[num_lines];
  int arr2[num_lines];
  int *arrs[2] = { arr1, arr2 };
  int count = 0;
  char buffer[256];
  while (utl_file_reader_read_line(buffer, sizeof(buffer), reader)) {
    char *token = strtok(buffer, delimiter);
    int num_count = 0;
    while (token) {
      int num = atoi(token);
      arrs[num_count][count] = num;
      token = strtok(NULL, delimiter);
      num_count++;
    }
    count++;
  }
  utl_map *freq_table = utl_map_create(compare_ints_map, free, free);
  for (int i = 0; i < num_lines; i++) {
    int num = arrs[1][i];
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
    int num = arrs[0][i];
    int *freq = (int *)utl_map_at(freq_table, &num);
    if (!freq) {
      continue;
    }
    similarity_score += num * (*freq);
  }
  printf("Answer: %i\n", similarity_score);
  utl_map_deallocate(freq_table);
  utl_file_reader_close(reader);
};
