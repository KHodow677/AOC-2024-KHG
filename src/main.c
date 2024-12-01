#include "day_map.h"
#include "khg_utl/map.h"

const int main(int argc, char *argv[]) {
  utl_map *day_map = create_day_map();
  if (argc > 1) {
    func_input *fi = utl_map_at(day_map, argv[1]);
    if (fi) {
      fi->func(fi->input_path, fi->count);
    }
  }
  utl_map_deallocate(day_map);
  return 0;
}

