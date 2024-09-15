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


#include "../inc.d/sett.h"


const char *name_for_window_manager                       = "Kalender von "
                                                            "Simon Euchner"    ;

const char *calendar_window_bg_color                      = "#000000"          ;
const char *calendar_window_font_color                    = "#000000"          ;

const char *calendar_quit_button_bg_color                 = "#000000"          ;
const char *calendar_quit_button_font_color               = "#FF0000"          ;
const int   calendar_quit_button_width                    = 50                 ;
const int   calendar_quit_button_height                   = 30                 ;
const int   calendar_quit_button_margin                   = 5                  ;
const char *calendar_quit_button_bg_color_hover           = "#FFFF00"          ;
const char *calendar_quit_button_font_color_hover         = "#000000"          ;
const char *calendar_quit_button_bg_color_active          = "#FF0000"          ;
const char *calendar_quit_button_font_color_active        = "#000000"          ;

const char *calendar_header_text                          = "Kalender %d"      ;
const char *calendar_header_bg_color                      = "#AAAAAA"          ;
const char *calendar_header_font_color                    = "#000000"          ;
const int   calendar_header_font_size                     = 22                 ;

const int   calendar_margin_thickness                     = 10                 ;

const char *calendar_month_name_frame_bg_color            = "#AAAAAA"          ;
const int   calendar_month_name_frame_font_size           = 18                 ;

const int   calendar_calendar_font_size                   = 16                 ;

const char *calendar_day_name_frame_bg_color              = "#AAAAAA"          ;

const char *calendar_day_button_bg_color                  = "#808080"          ;
const char *calendar_day_button_font_color                = "#000000"          ;
const int   calendar_day_button_width                     = 45                 ;
const int   calendar_day_button_height                    = 20                 ;
const char *calendar_day_button_bg_color_hover            = "#000000"          ;
const char *calendar_day_button_font_color_hover          = "#AAAAAA"          ;
const char *calendar_day_button_bg_color_active           = "#000000"          ;
const char *calendar_day_button_font_color_active         = "#FFFFFF"          ;
const char *calendar_day_button_off_bg_color              = "#404040"          ;
const char *calendar_day_button_marked_bg_color           = "#FFFF00"          ;
const char *calendar_day_button_marked_font_color         = "#000000"          ;
const char *calendar_day_button_marked_bg_color_hover     = "#DD0000"          ;
const char *calendar_day_button_marked_font_color_hover   = "#000000"          ;
const char *calendar_day_button_marked_bg_color_active    = "#FF0000"          ;
const char *calendar_day_button_marked_font_color_active  = "#000000"          ;

const char *calendar_note_button_label                    = "Notizen"          ;
const char *calendar_note_button_bg_color                 = "#AAAAAA"          ;
const char *calendar_note_button_bg_color_hover           = "#FFFF00"          ;
const char *calendar_note_button_bg_color_active          = "#FF0000"          ;

const char *calendar_year_button_bg_color                 = "#AAAAAA"          ;
const char *calendar_year_button_bg_color_hover           = "#FFFF00"          ;
const char *calendar_year_button_bg_color_active          = "#FF0000"          ;

const int   calendar_month_distance_vert                  = 40                 ;
const int   calendar_month_distance_hori                  = 10                 ;

const int   text_input_window_width                       = 600                ;
const int   text_input_window_height                      = 400                ;

const char *tiw_notepad_bg_color                          = "#808080"          ;
const char *tiw_notepad_font_color                        = "#000000"          ;
const int   tiw_notepad_font_size                         = 22                 ;

/* Weekdays name must be abbreviated to two characters                        */
const char *day_labels[BPR]                               = { "Mo",
                                                              "Di",
                                                              "Mi",
                                                              "Do",
                                                              "Fr",
                                                              "Sa",
                                                              "So"  };

/* Set to number of characters (excluding '\0') in longest month name         */
const int   max_month_len                                 =           9        ;
const char *month_labels[MPY]                             = { "Januar",
                                                              "Februar",
                                                              "März",
                                                              "April",
                                                              "Mai",
                                                              "Juni",
                                                              "Juli",
                                                              "August",
                                                              "September",
                                                              "Oktober",
                                                              "November",
                                                              "Dezember"   };

/* Absolute path to directory *data.d*; IMPORTANT: KEEP / CHARACTER AT END    */
const char *abspath_to_datd = "./dat.d/"                                       ;

/* --- Change things here only if you know what you are doing --------------- */

/* Please read *days.c* for more information on these settings.               */
const int inityear                                 =           2024            ;
const int first_days_inityear[MPY]                 = { 1, 4, 5, 1,
                                                       3, 6, 1, 4,
                                                       7, 2, 5, 7  };
/* -------------------------------------------------------------------------- */
