#include "aoc/4.h"
#include "khg_utl/algorithm.h"
#include "khg_utl/file_reader.h"
#include "khg_utl/vector.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define NUM_XMAS_DIRECTIONS 8
#define NUM_MAS_DIRECTIONS 4

typedef struct {
  int x;
  int y;
} xmas_direction;

typedef struct {
  int current_char_progress;
  int x_index;
  int y_index;
  xmas_direction direction;
} possible_xmas;

static const xmas_direction XMAS_DIRECTIONS[NUM_XMAS_DIRECTIONS] = { { -1, -1 }, { 0, -1 }, { 1, -1 }, { -1, 0 }, { 1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 } };
static const xmas_direction MAS_DIRECTIONS[NUM_XMAS_DIRECTIONS] = { { -1, -1 }, { 1, 1 }, { -1, 1 }, { 1, -1 } };
static const char *XMAS = "XMAS";
static const char *MAS = "MAS";

static int compare_chars(const void *a, const void *b) {
  return *(const char*)a - *(const char*)b;
}

static char get_char_at_coords(const int max, const char lines[max][max+1], const possible_xmas *px) {
  int new_x = px->x_index + px->direction.x;
  int new_y = px->y_index + px->direction.y;
  if (new_y < 0 || new_y >= max || new_x < 0 || new_x >= max) {
    return '\0';
  }
  return lines[new_y][new_x];
}

static int consider_xmas(const int max, const char lines[max][max+1], possible_xmas *xmas) {
  int xmas_count = 0;
  for (int i = 0; i < NUM_XMAS_DIRECTIONS; i++) {
    xmas->direction.x = XMAS_DIRECTIONS[i].x;
    xmas->direction.y = XMAS_DIRECTIONS[i].y;
    while (xmas->current_char_progress < strlen(XMAS)) {
      char current_char = get_char_at_coords(max, lines, xmas);
      xmas->current_char_progress++;
      if (current_char == XMAS[xmas->current_char_progress]) {
        xmas->direction.x += XMAS_DIRECTIONS[i].x;
        xmas->direction.y += XMAS_DIRECTIONS[i].y;
        if (strlen(XMAS) - 1 == xmas->current_char_progress) {
          xmas_count++;
          xmas->direction.x = 0;
          xmas->direction.y = 0;
          break;
        }
        continue;
      }
      else {
        xmas->direction.x = 0;
        xmas->direction.y = 0;
        break;
      }
    }
    xmas->current_char_progress = 0;
  }
  return xmas_count;
}

static int consider_x_mas(const int max, const char lines[max][max+1], possible_xmas *xmas) {
  for (int i = 0; i < NUM_MAS_DIRECTIONS; i+=2) {
    xmas->direction.x = MAS_DIRECTIONS[i].x;
    xmas->direction.y = MAS_DIRECTIONS[i].y;
    char current_char = get_char_at_coords(max, lines, xmas);
    if (current_char == MAS[0] || current_char == MAS[2]) {
      xmas->direction.x = MAS_DIRECTIONS[i+1].x;
      xmas->direction.y = MAS_DIRECTIONS[i+1].y;
      char opp_char = get_char_at_coords(max, lines, xmas);
      if ((opp_char == MAS[0] || opp_char == MAS[2]) && opp_char != current_char) {
        continue;
      }
    }
    return 0;
  }
  return 1;
}

void day0401(const char *input_path, const uint16_t num_lines) {
  printf("Advent of Code 2024: Day 4 Part 1\n");
  printf("Using file: %s\n", input_path);
  utl_file_reader *reader = utl_file_reader_open(input_path, UTL_READ_TEXT);
  utl_vector *possible = utl_vector_create(sizeof(possible_xmas));
  char lines[num_lines][num_lines+1];
  size_t line_size = sizeof(lines[0]) / sizeof(lines[0][0]);
  char buffer[num_lines+2];
  int count = 0;
  while (utl_file_reader_read_line(buffer, sizeof(buffer), reader)) {
    strcpy(lines[count], buffer);
    count++;
  }
  for (int y_index = 0; y_index < count; y_index++) {
    char x = XMAS[0];
    char *x_loc = utl_algorithm_find(lines[y_index], strlen(lines[y_index]), sizeof(char), &x, compare_chars);
    while (x_loc != NULL) {
      int x_index = (int)(x_loc - lines[y_index]);
      possible_xmas px = { 0, x_index, y_index, { 0, 0 } };
      utl_vector_push_back(possible, &px);
      x_loc = utl_algorithm_find(x_loc + 1, strlen(lines[y_index]) - x_index - 1, sizeof(char), &x, compare_chars);
    }
  }
  int xmas_count = 0;
  for (int i = 0; i < utl_vector_size(possible); i++) {
    xmas_count += consider_xmas(num_lines, lines, utl_vector_at(possible, i));
  }
  printf("Answer: %i\n", xmas_count);
  utl_vector_deallocate(possible);
  utl_file_reader_close(reader);
};

void day0402(const char *input_path, const uint16_t num_lines) {
  printf("Advent of Code 2024: Day 4 Part 2\n");
  printf("Using file: %s\n", input_path);
  utl_file_reader* reader = utl_file_reader_open(input_path, UTL_READ_TEXT);
  utl_vector *possible = utl_vector_create(sizeof(possible_xmas));
  char lines[num_lines][num_lines+1];
  size_t line_size = sizeof(lines[0]) / sizeof(lines[0][0]);
  char buffer[num_lines+2];
  int count = 0;
  while (utl_file_reader_read_line(buffer, sizeof(buffer), reader)) {
    strcpy(lines[count], buffer);
    count++;
  }
  for (int y_index = 0; y_index < count; y_index++) {
    char x = MAS[1];
    char *x_loc = utl_algorithm_find(lines[y_index], strlen(lines[y_index]), sizeof(char), &x, compare_chars);
    while (x_loc != NULL) {
      int x_index = (int)(x_loc - lines[y_index]);
      possible_xmas px = { 0, x_index, y_index, { 0, 0 } };
      utl_vector_push_back(possible, &px);
      x_loc = utl_algorithm_find(x_loc + 1, strlen(lines[y_index]) - x_index - 1, sizeof(char), &x, compare_chars);
    }
  }
  int x_mas_count = 0;
  for (int i = 0; i < utl_vector_size(possible); i++) {
    x_mas_count += consider_x_mas(num_lines, lines, utl_vector_at(possible, i));
  }
  printf("Answer: %i\n", x_mas_count);
  utl_vector_deallocate(possible);
  utl_file_reader_close(reader);
};

