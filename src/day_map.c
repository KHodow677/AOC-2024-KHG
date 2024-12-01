#include "day_map.h"
#include "aoc/1.h"
#include "khg_utl/map.h"
#include "khg_utl/string.h"
#include <stdlib.h>
#include <string.h>

static int compare_strings(const utl_key_type a, const utl_key_type b) {
  return strcmp((const char *)a, (const char *)b);
}

static void insert_func_input(utl_map *day_map, const char *day, const char *input) {
  func_input *fi = malloc(sizeof(func_input));
  *fi = (func_input) { day01, "res/assets/inputs/1.txt" };
  utl_map_insert(day_map, utl_string_strdup("day01"), fi);
}

utl_map *create_day_map() {
  utl_map *day_map = utl_map_create(compare_strings, free, free);
  insert_func_input(day_map, "day01", "res/assets/inputs/1.txt");
  return day_map;
}

