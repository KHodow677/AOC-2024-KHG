#include "day_map.h"
#include "aoc/1.h"
#include "aoc/3.h"
#include "khg_utl/map.h"
#include "khg_utl/string.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static int compare_strings(const utl_key_type a, const utl_key_type b) {
  return strcmp((const char *)a, (const char *)b);
}

static void insert_func_input(utl_map *day_map, const char *day, void (*func)(const char *, const uint16_t), const char *input, const uint16_t num_lines) {
  func_input *fi = malloc(sizeof(func_input));
  *fi = (func_input) { func, input, num_lines };
  utl_map_insert(day_map, utl_string_strdup(day), fi);
}

utl_map *create_day_map() {
  utl_map *day_map = utl_map_create(compare_strings, free, free);
  insert_func_input(day_map, "day0101", day0101, "res/assets/inputs/1.txt", 1000);
  insert_func_input(day_map, "day0102", day0102, "res/assets/inputs/1.txt", 1000);
  insert_func_input(day_map, "day0301", day0301, "res/assets/inputs/3_test.txt", 1);
  insert_func_input(day_map, "day0302", day0302, "res/assets/inputs/3_test.txt", 1);
  return day_map;
}
