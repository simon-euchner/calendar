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
 * Functions to create and load CSS settings.                                 *
 *                                                                            *
 * -------------------------------------------------------------------------- */


#include "../inc.d/csss.h"


static void get_css_string(char *);


/* Load CSS settings and apply them                                           */
void load_css(void) {
    GtkCssProvider *css_provider = gtk_css_provider_new();
    char css_string[LEN];
    get_css_string(css_string);
    gtk_css_provider_load_from_string(GTK_CSS_PROVIDER(css_provider),
                                      css_string);
    gtk_style_context_add_provider_for_display(gdk_display_get_default(),
                                               GTK_STYLE_PROVIDER(css_provider),
                                               600);
}

/* Generate CSS string from file *settings.c*                                 */
static void get_css_string(char *buffer) {

    /* Format string                                                          */
    char fmtstr[] = "#calendar_window {"
                    "    background-color: %s;"
                    "}"
                    "#calendar_quit_button {"
                    "    background: %s;"
                    "    color: %s;"
                    "    font-family: Monospace;"
                    "    font-weight: bold;"
                    "    font-size: %dpx;"
                    "    border-radius: 0px;"
                    "    border-width: 0px;"
                    "    padding: 0px;"
                    "}"
                    "#calendar_quit_button:hover {"
                    "    background: %s;"
                    "    color: %s;"
                    "}"
                    "#calendar_quit_button:active {"
                    "    background: %s;"
                    "    color: %s;"
                    "}"
                    "#calendar_header {"
                    "    background-color: %s;"
                    "    color: %s;"
                    "    font-family: Monospace;"
                    "    font-weight: bold;"
                    "    font-size: %dpx;"
                    "    border-radius: 0px;"
                    "    border-width: 0px;"
                    "}"
                    "#calendar_margin {"
                    "    background-color: %s;"
                    "    border-radius: 0px;"
                    "    border-width: 0px;"
                    "}"
                    "#calendar_day_name_frame {"
                    "    background-color: %s;"
                    "    color: %s;"
                    "    font-family: Monospace;"
                    "    font-weight: bold;"
                    "    font-size: %dpx;"
                    "    border-radius: 0px;"
                    "    border-width: 1px;"
                    "    border-color: %s;"
                    "}"
                    "#calendar_notes_button {"
                    "    background: %s;"
                    "    color: %s;"
                    "    font-family: Monospace;"
                    "    font-weight: bold;"
                    "    font-size: %dpx;"
                    "    border-radius: 0px;"
                    "    border-width: 1px;"
                    "    border-color: %s;"
                    "    margin: 0px;"
                    "    padding: 0px;"
                    "}"
                    "#calendar_notes_button:hover {"
                    "    background: %s;"
                    "}"
                    "#calendar_notes_button:active {"
                    "    background: %s;"
                    "}"
                    "#calendar_year_button {"
                    "    background: %s;"
                    "    color: %s;"
                    "    font-family: Monospace;"
                    "    font-weight: bold;"
                    "    font-size: %dpx;"
                    "    border-radius: 0px;"
                    "    border-width: 1px;"
                    "    border-color: %s;"
                    "    margin: 0px;"
                    "    padding: 0px;"
                    "}"
                    "#calendar_year_button:hover {"
                    "    background: %s;"
                    "}"
                    "#calendar_year_button:active {"
                    "    background: %s;"
                    "}"
                    "#calendar_sep {"
                    "    background-color: %s;"
                    "    border-radius: 0px;"
                    "    border-width: 0px;"
                    "}"
                    "#calendar_month_name_frame {"
                    "    background-color: %s;"
                    "    color: %s;"
                    "    font-family: Monospace;"
                    "    font-weight: bold;"
                    "    font-size: %dpx;"
                    "    border-radius: 0px;"
                    "    border-width: 1px;"
                    "    border-color: %s;"
                    "}"
                    "#calendar_day_button {"
                    "    background: %s;"
                    "    color: %s;"
                    "    font-family: Monospace;"
                    "    font-weight: bold;"
                    "    font-size: %dpx;"
                    "    border-radius: 0px;"
                    "    border-width: 1px;"
                    "    border-color: %s;"
                    "    margin: 0px;"
                    "    padding: 0px;"
                    "}"
                    "#calendar_day_button:hover {"
                    "    background-color: %s;"
                    "    color: %s;"
                    "}"
                    "#calendar_day_button:active {"
                    "    background-color: %s;"
                    "    color: %s;"
                    "}"
                    "#calendar_day_button_off {"
                    "    background: %s;"
                    "    border-radius: 0px;"
                    "    border-width: 1px;"
                    "    border-color: %s;"
                    "    margin: 0px;"
                    "    padding: 0px;"
                    "}"
                    "#calendar_day_button_marked {"
                    "    background: %s;"
                    "    color: %s;"
                    "    font-family: Monospace;"
                    "    font-weight: bold;"
                    "    font-size: %dpx;"
                    "    border-radius: 0px;"
                    "    border-width: 1px;"
                    "    border-color: %s;"
                    "    margin: 0px;"
                    "    padding: 0px;"
                    "}"
                    "#calendar_day_button_marked:hover {"
                    "    background-color: %s;"
                    "    color: %s;"
                    "}"
                    "#calendar_day_button_marked:active {"
                    "    background-color: %s;"
                    "    color: %s;"
                    "}"
                    "#calendar_today_button {"
                    "    background: %s;"
                    "    color: %s;"
                    "    font-family: Monospace;"
                    "    font-weight: bold;"
                    "    font-size: %dpx;"
                    "    border-radius: 0px;"
                    "    border-width: 1px;"
                    "    border-color: %s;"
                    "    margin: 0px;"
                    "    padding: 0px;"
                    "}"
                    "#calendar_today_button:hover {"
                    "    background-color: %s;"
                    "    color: %s;"
                    "}"
                    "#calendar_today_button:active {"
                    "    background-color: %s;"
                    "    color: %s;"
                    "}"
                    "textview {"
                    "    background: %s;"
                    "    color: %s;"
                    "    font-family: Monospace;"
                    "    font-weight: bold;"
                    "    font-size: %dpx;"
                    "}";

    /* Fill buffer with *fmtstr*, now with inserted values from *settings.c*  */
    sprintf(buffer, fmtstr, /* calendar_window                                */
                            calendar_window_bg_color,
                            /* calendar_quit_button                           */
                            calendar_quit_button_bg_color,
                            calendar_quit_button_font_color,
                            calendar_header_font_size,
                            calendar_quit_button_bg_color_hover,
                            calendar_quit_button_font_color_hover,
                            calendar_quit_button_bg_color_active,
                            calendar_quit_button_font_color_active,
                            /* calendar_header                                */
                            calendar_header_bg_color,
                            calendar_header_font_color,
                            calendar_header_font_size,
                            /* calendar_margin                                */
                            calendar_window_bg_color,
                            /* calendar_day_name_frame                        */
                            calendar_day_name_frame_bg_color,
                            calendar_window_font_color,
                            calendar_calendar_font_size,
                            calendar_window_bg_color,
                            /* calendar_notes_button                          */
                            calendar_notes_button_bg_color,
                            calendar_window_font_color,
                            calendar_calendar_font_size,
                            calendar_window_bg_color,
                            calendar_notes_button_bg_color_hover,
                            calendar_notes_button_bg_color_active,
                            /* calendar_year_button                           */
                            calendar_year_button_bg_color,
                            calendar_window_font_color,
                            calendar_calendar_font_size,
                            calendar_window_bg_color,
                            calendar_year_button_bg_color_hover,
                            calendar_year_button_bg_color_active,
                            /* calendar_sep_bg_color                          */
                            calendar_window_bg_color,
                            /* calendar_month_name_frame                      */
                            calendar_month_name_frame_bg_color,
                            calendar_window_font_color,
                            calendar_month_name_frame_font_size,
                            calendar_window_bg_color,
                            /* calendar_day_button                            */
                            calendar_day_button_bg_color,
                            calendar_day_button_font_color,
                            calendar_calendar_font_size,
                            calendar_window_bg_color,
                            calendar_day_button_bg_color_hover,
                            calendar_day_button_font_color_hover,
                            calendar_day_button_bg_color_active,
                            calendar_day_button_font_color_active,
                            /* calendar_day_button_off                        */
                            calendar_day_button_off_bg_color,
                            calendar_window_bg_color,
                            /* calendar_day_button_marked                    */
                            calendar_day_button_marked_bg_color,
                            calendar_day_button_marked_font_color,
                            calendar_calendar_font_size,
                            calendar_window_bg_color,
                            calendar_day_button_marked_bg_color_hover,
                            calendar_day_button_marked_font_color_hover,
                            calendar_day_button_marked_bg_color_active,
                            calendar_day_button_marked_font_color_active,
                            /* calendar_today_button                         */
                            calendar_today_button_bg_color,
                            calendar_today_button_font_color,
                            calendar_calendar_font_size,
                            calendar_window_bg_color,
                            calendar_day_button_marked_bg_color_hover,
                            calendar_day_button_marked_font_color_hover,
                            calendar_day_button_marked_bg_color_active,
                            calendar_day_button_marked_font_color_active,
                            /* tiw_notepad                                    */
                            tiw_notepad_bg_color,
                            tiw_notepad_font_color,
                            tiw_notepad_font_size);
}
