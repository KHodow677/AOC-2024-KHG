#include "aoc/5.h"
#include "khg_utl/algorithm.h"
#include "khg_utl/file_reader.h"
#include "khg_utl/map.h"
#include "khg_utl/vector.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static utl_map *CURRENT_RULES = NULL;

static bool is_empty_line(char *line) {
  while (isspace((unsigned char)*line)) {
    line++;
  }
  return *line == '\0';
}

static int compare_ints(const void *a, const void *b) {
  return (*(int *)a - *(int *)b);
}

static int compare_ints_map(const utl_key_type a, const utl_key_type b) {
  return (*(const int *)a - *(const int *)b);
}

static int compare_rules(const void *a, const void *b) {
  int int_a = *(int *)a;
  int int_b = *(int *)b;
  utl_vector *rule_vector_a = utl_map_at(CURRENT_RULES, &int_a);
  if (rule_vector_a) {
    int *rule_data = utl_vector_data(rule_vector_a);
    int rule_size = utl_vector_size(rule_vector_a);
    if (utl_algorithm_find(rule_data, rule_size, sizeof(int), &int_b, compare_ints)) {
      return -1;
    }
  }
  utl_vector *rule_vector_b = utl_map_at(CURRENT_RULES, &int_b);
  if (rule_vector_b) {
    int *rule_data = utl_vector_data(rule_vector_b);
    int rule_size = utl_vector_size(rule_vector_b);
    if (utl_algorithm_find(rule_data, rule_size, sizeof(int), &int_a, compare_ints)) {
      return 1;
    }
  }
  return 0;
}


static void free_rule(void *r) {
  utl_vector_deallocate((utl_vector *)r);
}

static void add_rule(char *buffer) {
  int num1 = atoi(strtok(buffer, "|"));
  int num2 = atoi(strtok(NULL, "|"));
  utl_vector *rule1 = utl_map_at(CURRENT_RULES, &num1);
  if (rule1) {
    utl_vector_push_back(rule1, &num2);
  }
  else {
    int *r1 = malloc(sizeof(int));
    *r1 = num1;
    utl_vector *r2 = utl_vector_create(sizeof(int));
    utl_vector_push_back(r2, &num2);
    utl_map_insert(CURRENT_RULES, r1, r2);
  }
}

static bool check_list_correct(utl_vector *list, utl_map *rules) {
  int *data = utl_vector_data(list);
  int size = utl_vector_size(list);
  int current_page = data[size - 1];
  utl_vector *rule_vector = utl_map_at(rules, &current_page);
  if (rule_vector) {
    int *rule_data = utl_vector_data(rule_vector);
    int rule_size = utl_vector_size(rule_vector);
    for (int i = 0; i < size; i++) {
      int val = data[i];
      if (utl_algorithm_find(rule_data, rule_size, sizeof(int), &val, compare_ints)) {
        return false;
      }
    }
  }
  return true;
}

static void build_check_page(utl_vector *list, char *buffer, bool *is_correct) {
  char *token = strtok(buffer, ",");
  while (token) {
    int num = atoi(token);
    utl_vector_push_back(list, &num);
    if (!check_list_correct(list, CURRENT_RULES)) {
      *is_correct = false;
    }
    token = strtok(NULL, ",");
  }
}

void day0501(const char *input_path, const uint16_t num_lines) {
  printf("Advent of Code 2024: Day 5 Part 1\n");
  printf("Using file: %s\n", input_path);
  utl_file_reader *reader = utl_file_reader_open(input_path, UTL_READ_TEXT);
  char buffer[256];
  bool rule_section = true;
  CURRENT_RULES = utl_map_create(compare_ints_map, free, free_rule);
  utl_vector *list = utl_vector_create(sizeof(int));
  int tally = 0;
  while (utl_file_reader_read_line(buffer, sizeof(buffer), reader)) {
    if (is_empty_line(buffer)) {
      rule_section = false;
      continue;
    }
    if (rule_section) {
      add_rule(buffer);
    }
    else {
      bool is_correct = true;
      build_check_page(list, buffer, &is_correct);
      tally += is_correct ? ((int *)utl_vector_data(list))[utl_vector_size(list) / 2] : 0;
    }
    utl_vector_clear(list);
  }
  printf("Answer: %i\n", tally);
  utl_map_deallocate(CURRENT_RULES);
  utl_vector_deallocate(list);
  utl_file_reader_close(reader);
};

void day0502(const char *input_path, const uint16_t num_lines) {
  printf("Advent of Code 2024: Day 5 Part 2\n");
  printf("Using file: %s\n", input_path);
  utl_file_reader *reader = utl_file_reader_open(input_path, UTL_READ_TEXT);
  char buffer[256];
  bool rule_section = true;
  CURRENT_RULES = utl_map_create(compare_ints_map, free, free_rule);
  utl_vector *list = utl_vector_create(sizeof(int));
  int tally = 0;
  while (utl_file_reader_read_line(buffer, sizeof(buffer), reader)) {
    if (is_empty_line(buffer)) {
      rule_section = false;
      continue;
    }
    if (rule_section) {
      add_rule(buffer);
    }
    else {
      bool is_correct = true;
      build_check_page(list, buffer, &is_correct);
      if (!is_correct) {
        utl_algorithm_sort(utl_vector_data(list), utl_vector_size(list), sizeof(int), compare_rules);
        tally += ((int *)utl_vector_data(list))[utl_vector_size(list) / 2];
      }
    }
    utl_vector_clear(list);
  }
  printf("Answer: %i\n", tally);
  utl_map_deallocate(CURRENT_RULES);
  utl_vector_deallocate(list);
  utl_file_reader_close(reader);
};

