/* -------------------------------------------------------------------------- *
 *                                                                            *
 * This file is part of the application *calendar* by Simon Euchner.          *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 *                                                                            *
 * LICENSES: GPL-3.0                                                          *
 *                                                                            *
 * IMPORTANT: THIS IS FREE SOFTWARE WITHOUT ANY WARRANTY. THE USER IS IF FREE *
 *            TO MODIFY AND REDISTRIBUTE THIS SOFTWARE UNDER THE TERMS OF THE *
 *            LICENSE LISTED ABOVE PUBLISHED BY THE FREE SOFTWARE FOUNDATION. *
 *            THE PUBLISHER, SIMON EUCHNER, IS NOT RESPONSIBLE FOR ANY        *
 *            NEGATIVE EFFECTS THIS SOFTWARE MAY CAUSE.                       *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 *                                                                            *
 * This file can be used to configure *calender*. After changing a value,     *
 * please recompile to apply the changes.                                     *
 *                                                                            *
 * -------------------------------------------------------------------------- */


#ifndef SETT_H
#define SETT_H

#include "defi.h"

extern const char *name_for_window_manager;
extern const char *calendar_window_bg_color;
extern const char *calendar_window_font_color;
extern const char *calendar_quit_button_bg_color;
extern const char *calendar_quit_button_font_color;
extern const int   calendar_quit_button_width;
extern const int   calendar_quit_button_height;
extern const int   calendar_quit_button_margin;
extern const char *calendar_quit_button_bg_color_hover;
extern const char *calendar_quit_button_font_color_hover;
extern const char *calendar_quit_button_bg_color_active;
extern const char *calendar_quit_button_font_color_active;
extern const char *calendar_header_text;
extern const char *calendar_header_bg_color;
extern const char *calendar_header_font_color;
extern const int   calendar_header_font_size;
extern const int   calendar_margin_thickness;
extern const char *calendar_month_name_frame_bg_color;
extern const int   calendar_month_name_frame_font_size;
extern const int   calendar_calendar_font_size;
extern const char *calendar_day_name_frame_bg_color;
extern const char *calendar_day_button_bg_color;
extern const char *calendar_day_button_font_color;
extern const int   calendar_day_button_width;
extern const int   calendar_day_button_height;
extern const char *calendar_day_button_bg_color_hover;
extern const char *calendar_day_button_font_color_hover;
extern const char *calendar_day_button_bg_color_active;
extern const char *calendar_day_button_font_color_active;
extern const char *calendar_day_button_off_bg_color;
extern const char *calendar_day_button_marked_bg_color;
extern const char *calendar_day_button_marked_font_color;
extern const char *calendar_day_button_marked_bg_color_hover; 
extern const char *calendar_day_button_marked_font_color_hover;
extern const char *calendar_day_button_marked_bg_color_active;
extern const char *calendar_day_button_marked_font_color_active;
extern const int   calendar_notes_window_width;
extern const int   calendar_notes_window_height;
extern const char *calendar_notes_button_label;
extern const char *calendar_notes_button_bg_color;
extern const char *calendar_notes_button_bg_color_hover;
extern const char *calendar_notes_button_bg_color_active;
extern const char *calendar_year_button_bg_color;
extern const char *calendar_year_button_bg_color_hover;
extern const char *calendar_year_button_bg_color_active;
extern const int   calendar_month_distance_vert;
extern const int   calendar_month_distance_hori;
extern const int   text_input_window_width;
extern const int   text_input_window_height;
extern const char *tiw_notepad_bg_color;
extern const char *tiw_notepad_font_color;
extern const int   tiw_notepad_font_size;
extern const char *day_labels[BPR];
extern const int   max_month_len;
extern const char *month_labels[MPY];
extern const char *abspath_to_datd;
extern const int   inityear;
extern const int   first_days_inityear[MPY];

#endif
