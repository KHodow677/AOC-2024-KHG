#pragma once

#include "khg_utl/map.h"
#include <stdint.h>

typedef struct func_input {
  void (*func)(const char *, const uint16_t);
  const char *input_path;
  uint16_t count;
} func_input;

utl_map *create_day_map();

