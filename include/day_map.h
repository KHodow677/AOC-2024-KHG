#pragma once

#include "khg_utl/map.h"

typedef struct func_input {
  void (*func)(const char *);
  const char *input_path;
} func_input;

utl_map *create_day_map();

