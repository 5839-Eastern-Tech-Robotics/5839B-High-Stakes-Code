#include "robot/ui/lcd.hpp"
#include "liblvgl/core/lv_obj.h"
#include "liblvgl/core/lv_obj_pos.h"
#include "liblvgl/core/lv_obj_style.h"
#include "liblvgl/core/lv_obj_tree.h"
#include "liblvgl/extra/layouts/flex/lv_flex.h"
#include "liblvgl/extra/widgets/list/lv_list.h"
#include "liblvgl/misc/lv_area.h"
#include "liblvgl/widgets/lv_label.h"
#include "robodash/core.h"
#include "robodash/impl/styles.h"
#include <sys/types.h>
#include <utility>

// ============================= Callbacks ============================= //
void LCD::pg_up_cb(lv_event_t *event) {
	LCD *selector = (LCD *)lv_obj_get_user_data(lv_event_get_target(event));
	lv_coord_t scroll_y = lv_obj_get_height(selector->display) * 0.5;
	lv_obj_scroll_by_bounded(selector->display, 0, scroll_y, LV_ANIM_ON);
}

void LCD::pg_down_cb(lv_event_t *event) {
	LCD *selector = (LCD *)lv_obj_get_user_data(lv_event_get_target(event));
	lv_coord_t scroll_y = lv_obj_get_height(selector->display) * -0.5;
	lv_obj_scroll_by_bounded(selector->display, 0, scroll_y, LV_ANIM_ON);
}

// ========================== Constructor =========================== //

LCD::LCD(std::string name) {
  this->view = rd_view_create(name.c_str());
  lv_obj_set_style_bg_color(view->obj, color_bg, 0);

  this->display = lv_obj_create(view->obj);
  lv_obj_set_size(display, 180, 220);
  lv_obj_align(display, LV_ALIGN_CENTER, -40, 0);
  lv_obj_add_style(display, &style_transp, 0);

  lv_obj_t *list_btns = lv_obj_create(view->obj);
  lv_obj_add_style(list_btns, &style_transp, 0);
  lv_obj_set_size(list_btns, 32, 192);
  lv_obj_align(list_btns, LV_ALIGN_RIGHT_MID, 20, 0);
  lv_obj_clear_flag(list_btns, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_layout(list_btns, LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(list_btns, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(list_btns, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_CENTER);

  // Up page button
  lv_obj_t *pg_up_btn = lv_btn_create(list_btns);
  lv_obj_add_style(pg_up_btn, &style_transp, 0);
  lv_obj_set_size(pg_up_btn, 32, 32);
  lv_obj_add_event_cb(pg_up_btn, &pg_up_cb, LV_EVENT_CLICKED, NULL);
  lv_obj_set_user_data(pg_up_btn, this);
  lv_obj_add_flag(pg_up_btn, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_text_opa(pg_up_btn, 128, LV_STATE_PRESSED);
  lv_obj_set_flex_grow(pg_up_btn, 1);

  lv_obj_t *pg_up_img = lv_img_create(pg_up_btn);
  lv_obj_align(pg_up_img, LV_ALIGN_CENTER, 0, 0);
  lv_img_set_src(pg_up_img, LV_SYMBOL_UP "\n" LV_SYMBOL_UP);
  lv_obj_set_style_text_line_space(pg_up_img, -10, LV_PART_MAIN);

  // Down page button
  lv_obj_t *pg_down_btn = lv_btn_create(list_btns);
  lv_obj_add_style(pg_down_btn, &style_transp, 0);
  lv_obj_set_size(pg_down_btn, 32, 32);
  lv_obj_add_event_cb(pg_down_btn, &pg_down_cb, LV_EVENT_CLICKED, NULL);
  lv_obj_set_user_data(pg_down_btn, this);
  lv_obj_add_flag(pg_down_btn, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_text_opa(pg_down_btn, 128, LV_STATE_PRESSED);
  lv_obj_set_flex_grow(pg_down_btn, 1);

  lv_obj_t *pg_down_img = lv_img_create(pg_down_btn);
  lv_obj_align(pg_down_img, LV_ALIGN_CENTER, 0, 0);
  lv_img_set_src(pg_down_img, LV_SYMBOL_DOWN "\n" LV_SYMBOL_DOWN);
  lv_obj_set_style_text_line_space(pg_down_img, -10, LV_PART_MAIN);
}

// =============================== Methods ===================================== //

void LCD::clear() {
    for (std::pair<uint, LCD::line_t> line : this->contents) {
        lv_obj_del(line.second.obj);
        contents.erase(line.first);
    }
}

void LCD::clear(uint line) {
    if (!this->contents.contains(line)) return;

    if (line < maxLine) {
        lv_label_set_text(contents.at(line).obj, "");
        contents.at(line).contents = "";
    } else {
        lv_obj_del(contents.at(line).obj);
        contents.erase(line);
        int i = 1;
        while (line - i >= 0) {
            if (!contents.contains(line - i)) continue;
            if (contents.at(line - i).contents.empty()) {
                lv_obj_del(contents.at(line - i).obj);
                contents.erase(line - i);
                i++;
            } else break;
        }
    }
}

void LCD::focus() {
    rd_view_focus(this->view);
}

void LCD::print(uint line, std::string str) {
    if (contents.contains(line)) {
        contents.at(line).contents = str;
        lv_label_set_text(contents.at(line).obj, str.c_str());
    } else {
        lv_obj_t *new_btn = lv_list_add_btn(display, NULL, str.c_str());
        contents.insert(std::make_pair(line, line_t({new_btn, str})));

		lv_obj_add_style(new_btn, &style_list_btn, 0);
		lv_obj_set_style_transform_width(new_btn, -8, 0);
    }
}