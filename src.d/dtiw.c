/* -------------------------------------------------------------------------- *
 *                                                                            *
 * This file is part of the application *calendar* by Simon Euchner.          *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 *                                                                            *
 * LICENSE: GPL-3.0                                                           *
 *                                                                            *
 * IMPORTANT: THIS IS FREE SOFTWARE WITHOUT ANY WARRANTY. THE USER IS FREE TO *
 *            MODIFY AND REDISTRIBUTE THIS SOFTWARE UNDER THE TERMS OF THE    *
 *            LICENSE LISTED ABOVE PUBLISHED BY THE FREE SOFTWARE FOUNDATION. *
 *            THE PUBLISHER, SIMON EUCHNER, IS NOT RESPONSIBLE FOR ANY        *
 *            NEGATIVE EFFECTS THIS SOFTWARE MAY CAUSE.                       *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 *                                                                            *
 * Definition of functions allowing to draw the complete text input window.   *
 *                                                                            *
 * -------------------------------------------------------------------------- */


#include "../inc.d/dtiw.h"


static void create_tiw_header(const int,
                              const char *,
                              const char *,
                              const char *,
                              GtkWidget *,
                              GtkWidget *,
                              GtkWidget *,
                              GtkWidget *);

static void create_tiw_layout(GtkWidget *,
                              GtkWidget *,
                              GtkWidget *,
                              GtkWidget *,
                              GtkWidget *,
                              GtkWidget *,
                              GtkWidget *);


/* Initialize widgets for text input window; note the more general name, as   *
 * this function will be reused for the notes window later to not duplicate   *
 * code unnecessarily.                                                        */
void window_widgets_initialize(GtkWidget *tiw_window,
                               int window_width,
                               int window_height,
                               GtkWidget *tiw_header_label,
                               GtkWidget *tiw_quit_button,
                               GtkWidget *tiw_header,
                               GtkWidget *tiw_margin_left,
                               GtkWidget *tiw_margin_right,
                               GtkWidget *tiw_margin_top,
                               GtkWidget *tiw_margin_bottom,
                               GtkWidget *tiw_notepad) {

    /* Names of widgets are set to the calendar versions of them (when        *
     * possible) to apply consistent CSS settings with repsect to the actual  *
     * calendar. To this end, also different settings from the calendar are   *
     * applied to the text input window widgets.                              */

    gtk_widget_set_name(tiw_window, "calendar_window");
    gtk_window_set_resizable(GTK_WINDOW(tiw_window), FALSE);
    gtk_window_set_default_size(GTK_WINDOW(tiw_window),
                                window_width,
                                window_height);

    gtk_widget_set_name(tiw_quit_button, "calendar_quit_button");
    gtk_widget_set_halign(tiw_quit_button, GTK_ALIGN_END);
    gtk_widget_set_size_request(tiw_quit_button,
                                calendar_quit_button_width,
                                calendar_quit_button_height);
    gtk_widget_set_margin_end(tiw_quit_button, calendar_quit_button_margin);
    gtk_widget_set_margin_top(tiw_quit_button, calendar_quit_button_margin);
    gtk_widget_set_margin_bottom(tiw_quit_button, calendar_quit_button_margin);

    gtk_widget_set_halign(tiw_header_label, GTK_ALIGN_START);
    gtk_widget_set_name(tiw_header, "calendar_header");
    gtk_widget_set_hexpand(tiw_header, TRUE);

    gtk_widget_set_name(tiw_margin_left,   "calendar_margin");
    gtk_widget_set_name(tiw_margin_right,  "calendar_margin");
    gtk_widget_set_name(tiw_margin_top,    "calendar_margin");
    gtk_widget_set_name(tiw_margin_bottom, "calendar_margin");
    gtk_widget_set_size_request(tiw_margin_left,
                                calendar_margin_thickness, -1);
    gtk_widget_set_size_request(tiw_margin_right,
                                calendar_margin_thickness, -1);
    gtk_widget_set_size_request(tiw_margin_top,
                                -1, calendar_margin_thickness);
    gtk_widget_set_size_request(tiw_margin_bottom,
                                -1, calendar_margin_thickness);

    gtk_widget_set_name(tiw_notepad, "tiw_notepad");
    gtk_widget_set_hexpand(tiw_notepad, TRUE);
    gtk_widget_set_vexpand(tiw_notepad, TRUE);
    gtk_text_view_set_top_margin(GTK_TEXT_VIEW(tiw_notepad), 10);
    gtk_text_view_set_bottom_margin(GTK_TEXT_VIEW(tiw_notepad), 10);
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(tiw_notepad), 10);
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW(tiw_notepad), 10);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(tiw_notepad), GTK_WRAP_WORD_CHAR);
    gtk_text_view_set_monospace(GTK_TEXT_VIEW(tiw_notepad), TRUE);
}

/* Initialize widgets for text input window                                   */
char *create_text_input_window(const int tiw_year,
                               const char *tiw_day,
                               const int tiw_day_number,
                               const char *tiw_month,
                               const int tiw_month_number,
                               const char *tiw_weekday,
                               GtkWidget *tiw_vbox,
                               GtkWidget *tiw_hbox,
                               GtkWidget *tiw_header_label,
                               GtkWidget *tiw_quit_button,
                               GtkWidget *tiw_header,
                               GtkWidget *tiw_margin_left,
                               GtkWidget *tiw_margin_right,
                               GtkWidget *tiw_margin_top,
                               GtkWidget *tiw_margin_bottom,
                               GtkTextBuffer *tiw_buffer,
                               GtkWidget *tiw_notepad) {

    /* --- Read file contents into buffer; if file does not exist load
     *     empty string into it --------------------------------------------- */
    FILE *file;
    int len_fname = 2+1+2+1+MYL+4+1;
    char fname[len_fname];
    char *abspath_to_note = (char *)malloc(strlen(abspath_to_datd)+len_fname);
    snprintf(fname,
             len_fname,
             "%02d-%02d-%d.txt",
             tiw_day_number,
             tiw_month_number,
             tiw_year);
    strcpy(abspath_to_note, abspath_to_datd);
    strcat(abspath_to_note, fname);

    if ((file = fopen(abspath_to_note, "r"))) {
        gtk_text_buffer_set_text(tiw_buffer, "", -1);
        fseek(file, 0l, SEEK_END);
        long int num_bytes = ftell(file);
        fseek(file, 0l, SEEK_SET);
        char *buffer = (char *)malloc(num_bytes + 1);
        if (!buffer) {
            printf("Error allocating memory to read file *%s*.\n", fname);
            exit(1);
        }
        fread(buffer, 1, num_bytes, file);
        buffer[num_bytes] = '\0';
        fclose(file);
        gtk_text_buffer_set_text(tiw_buffer, buffer, -1);
        free(buffer);
    } else {
        gtk_text_buffer_set_text(tiw_buffer, "", -1);
    }

    /* Draw header                                                            */
    create_tiw_header(tiw_year,
                      tiw_day,
                      tiw_month,
                      tiw_weekday,
                      tiw_vbox,
                      tiw_header_label,
                      tiw_quit_button,
                      tiw_header);

    /* Create text input window layout                                        */
    create_tiw_layout(tiw_vbox,
                      tiw_hbox,
                      tiw_margin_left,
                      tiw_margin_right,
                      tiw_margin_top,
                      tiw_margin_bottom,
                      tiw_notepad);

    return abspath_to_note;
}

/* Draw header                                                                */
static void create_tiw_header(const int tiw_year,
                              const char *tiw_day,
                              const char *tiw_month,
                              const char *tiw_weekday,
                              GtkWidget *tiw_vbox,
                              GtkWidget *tiw_header_label,
                              GtkWidget *tiw_quit_button,
                              GtkWidget *tiw_header) {

    /* Set label                                                              */
    int len = 2 + 2 + 2 + 3 + max_month_len + 3 + MYL + 1;
    char buffer[len];
    snprintf(buffer, len, "%s  %s - %s - %d",
             tiw_weekday, tiw_day, tiw_month, tiw_year);
    gtk_label_set_text(GTK_LABEL(tiw_header_label), buffer);
    gtk_frame_set_child(GTK_FRAME(tiw_header), tiw_header_label);

    /* Draw header                                                            */
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_attach(GTK_GRID(grid), tiw_header, 0, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), tiw_quit_button, 1, 0, 2, 1);
    gtk_box_append(GTK_BOX(tiw_vbox), grid);
}

/* Creat text input window layout                                             */
static void create_tiw_layout(GtkWidget *tiw_vbox,
                              GtkWidget *tiw_hbox,
                              GtkWidget *tiw_margin_left,
                              GtkWidget *tiw_margin_right,
                              GtkWidget *tiw_margin_top,
                              GtkWidget *tiw_margin_bottom,
                              GtkWidget *tiw_notepad) {

    gtk_box_append(GTK_BOX(tiw_vbox), tiw_margin_top);
    gtk_box_append(GTK_BOX(tiw_vbox), tiw_hbox);
    gtk_box_append(GTK_BOX(tiw_hbox), tiw_margin_left);
    gtk_box_append(GTK_BOX(tiw_hbox), tiw_notepad);
    gtk_box_append(GTK_BOX(tiw_hbox), tiw_margin_right);
    gtk_box_append(GTK_BOX(tiw_vbox), tiw_margin_bottom);
}
