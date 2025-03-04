#pragma once

#include "liblvgl/core/lv_obj.h"
#include "liblvgl/lvgl.h"
#include "robodash/core.h"
#include <cstdio>
#include <map>
#include <string>
#include <sys/types.h>
#include <vector>

class LCD {
public:
  LCD(std::string name = "LCD");
  void clear();
  void clear(uint line);

  void print(uint line, std::string str);

  template <typename... Params>
  void printf(uint line, std::string fmt, Params... args) {
    char fstr[sizeof(fmt) + sizeof...(args)];
    sprintf(fstr, fmt.c_str(), args...);
    print(line, fstr);
  }

  void focus();

private:
  struct line_t {
    lv_obj_t *obj;
    std::string contents;
  };

  rd_view_t *view;
  std::map<uint, line_t> contents{};
  uint maxLine = 0;

  lv_obj_t *display;
  static void pg_up_cb(lv_event_t *event);
  static void pg_down_cb(lv_event_t *event);
};