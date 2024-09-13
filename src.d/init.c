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
 * Function to initialize widgets, set properties and load CSS settings.      *
 *                                                                            *
 * -------------------------------------------------------------------------- */


#include "../inc.d/init.h"


void initialize(int **calendar_data,
                int *calendar_dbtm,
                GtkWidget *calendar_window,
                GtkWidget *calendar_header_label,
                GtkWidget *calendar_quit_button,
                GtkWidget *calendar_header,
                GtkWidget *calendar_margin_left,
                GtkWidget *calendar_margin_right,
                GtkWidget *calendar_margin_top,
                GtkWidget *calendar_margin_bottom,
                GtkWidget **calendar_day_name_frames,
                GtkWidget **calendar_day_name_labels,
                GtkWidget *calendar_prev_year_button,
                GtkWidget *calendar_next_year_button,
                GtkWidget *calendar_hsep_a,
                GtkWidget *calendar_hsep_b,
                GtkWidget *calendar_hsep_c,
                GtkWidget *calendar_vsep_a,
                GtkWidget *calendar_vsep_b,
                GtkWidget *calendar_vsep_c,
                GtkWidget **calendar_month_name_frames,
                GtkWidget **calendar_day_buttons,
                GtkWidget *calendar_note_button) {

    gtk_widget_set_name(calendar_window, "calendar_window");
    gtk_window_set_resizable(GTK_WINDOW(calendar_window), FALSE);

    gtk_widget_set_name(calendar_quit_button, "calendar_quit_button");
    gtk_widget_set_halign(calendar_quit_button, GTK_ALIGN_END);
    gtk_widget_set_size_request(calendar_quit_button,
                                calendar_quit_button_width,
                                calendar_quit_button_height);
    gtk_widget_set_margin_end(calendar_quit_button,
                              calendar_quit_button_margin);
    gtk_widget_set_margin_top(calendar_quit_button,
                              calendar_quit_button_margin);
    gtk_widget_set_margin_bottom(calendar_quit_button,
                              calendar_quit_button_margin);

    gtk_widget_set_halign(calendar_header_label, GTK_ALIGN_START);
    gtk_widget_set_name(calendar_header, "calendar_header");
    gtk_widget_set_hexpand(calendar_header, TRUE);

    gtk_widget_set_name(calendar_margin_left,   "calendar_margin");
    gtk_widget_set_name(calendar_margin_right,  "calendar_margin");
    gtk_widget_set_name(calendar_margin_top,    "calendar_margin");
    gtk_widget_set_name(calendar_margin_bottom, "calendar_margin");
    gtk_widget_set_size_request(calendar_margin_left,
                                calendar_margin_thickness, -1);
    gtk_widget_set_size_request(calendar_margin_right,
                                calendar_margin_thickness, -1);
    gtk_widget_set_size_request(calendar_margin_top,
                                -1, calendar_margin_thickness);
    gtk_widget_set_size_request(calendar_margin_bottom,
                                -1, calendar_margin_thickness);

    for (int i=0; i<BPR; i++) {
        gtk_widget_set_name(calendar_day_name_frames[i],
                            "calendar_day_name_frame");
        gtk_widget_set_halign(calendar_day_name_labels[i], .5);
        gtk_widget_set_valign(calendar_day_name_labels[i], .5);
    }

    gtk_widget_set_name(calendar_prev_year_button, "calendar_year_button");
    gtk_widget_set_name(calendar_next_year_button, "calendar_year_button");

    gtk_widget_set_name(calendar_hsep_a, "calendar_sep");
    gtk_widget_set_name(calendar_hsep_b, "calendar_sep");
    gtk_widget_set_name(calendar_hsep_c, "calendar_sep");
    gtk_widget_set_name(calendar_vsep_a, "calendar_sep");
    gtk_widget_set_name(calendar_vsep_b, "calendar_sep");
    gtk_widget_set_name(calendar_vsep_c, "calendar_sep");
    gtk_widget_set_size_request(calendar_hsep_a,
                                -1, calendar_month_distance_vert);
    gtk_widget_set_size_request(calendar_hsep_b,
                                -1, calendar_month_distance_vert);
    gtk_widget_set_size_request(calendar_hsep_c,
                                -1, calendar_month_distance_vert);
    gtk_widget_set_size_request(calendar_vsep_a,
                                calendar_month_distance_hori, -1);
    gtk_widget_set_size_request(calendar_vsep_b,
                                calendar_month_distance_hori, -1);
    gtk_widget_set_size_request(calendar_vsep_c,
                                calendar_month_distance_hori, -1);

    for (int i=0; i<MPY; i++) {
        gtk_widget_set_name(calendar_month_name_frames[i],
                            "calendar_month_name_frame");
        gtk_widget_set_valign(calendar_month_name_frames[i], GTK_ALIGN_END);
    }

    for (int i=0; i<MPY*BPM; i++) {
        if (calendar_data[i/((int)BPM)][i%((int)BPM)] != 0) {
            if (calendar_dbtm[i]) {
                gtk_widget_set_name(calendar_day_buttons[i],
                                    "calendar_day_button_marked");
            } else {
                gtk_widget_set_name(calendar_day_buttons[i],
                                    "calendar_day_button");
            }
        } else {
            gtk_widget_set_name(calendar_day_buttons[i],
                                "calendar_day_button_off");
        }
        gtk_widget_set_size_request(calendar_day_buttons[i],
                                    calendar_day_button_width,
                                    calendar_day_button_height);
    }

    gtk_widget_set_name(calendar_note_button, "calendar_note_button");

    load_css();
}
