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
 * Definition of functions allowing to draw the complete window where notes   *
 * may be placed.                                                             *
 *                                                                            *
 * -------------------------------------------------------------------------- */


#include "../inc.d/dniw.h"


static void create_niw_header(GtkWidget *,
                              GtkWidget *,
                              GtkWidget *,
                              GtkWidget *);

static void create_niw_layout(GtkWidget *,
                              GtkWidget *,
                              GtkWidget *,
                              GtkWidget *,
                              GtkWidget *,
                              GtkWidget *,
                              GtkWidget *);


void create_window_for_notes(const char *abspath_to_notes_file,
                             GtkWidget *notes_vbox,
                             GtkWidget *notes_hbox,
                             GtkWidget *notes_header_label,
                             GtkWidget *notes_quit_button,
                             GtkWidget *notes_header,
                             GtkWidget *notes_margin_left,
                             GtkWidget *notes_margin_right,
                             GtkWidget *notes_margin_top,
                             GtkWidget *notes_margin_bottom,
                             GtkTextBuffer *notes_buffer,
                             GtkWidget *notes_notepad) {

    /* --- Read file contents into buffer; if file does not exist load
     *     empty string into it --------------------------------------------- */
    FILE *file;
    if ((file = fopen(abspath_to_notes_file, "r"))) {
        gtk_text_buffer_set_text(notes_buffer, "", -1);
        fseek(file, 0l, SEEK_END);
        long int num_bytes = ftell(file);
        fseek(file, 0l, SEEK_SET);
        char *buffer = (char *)malloc(num_bytes + 1);
        if (!buffer) {
            printf("%s\n", "Error allocating memory to read file *notes.txt*.");
            exit(1);
        }
        fread(buffer, 1, num_bytes, file);
        buffer[num_bytes] = '\0';
        fclose(file);
        gtk_text_buffer_set_text(notes_buffer, buffer, -1);
        free(buffer);
    } else {
        gtk_text_buffer_set_text(notes_buffer, "", -1);
    }

    /* Draw header                                                            */
    create_niw_header(notes_vbox,
                      notes_header_label,
                      notes_quit_button,
                      notes_header);

    /* Create text input window layout                                        */
    create_niw_layout(notes_vbox,
                      notes_hbox,
                      notes_margin_left,
                      notes_margin_right,
                      notes_margin_top,
                      notes_margin_bottom,
                      notes_notepad);
}

/* Draw header                                                                */
static void create_niw_header(GtkWidget *notes_vbox,
                              GtkWidget *notes_header_label,
                              GtkWidget *notes_quit_button,
                              GtkWidget *notes_header) {

    /* Reuse notes button label as header label                               */
    gtk_label_set_text(GTK_LABEL(notes_header_label),
                       calendar_notes_button_label);
    gtk_frame_set_child(GTK_FRAME(notes_header), notes_header_label);

    /* Draw header                                                            */
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_attach(GTK_GRID(grid), notes_header, 0, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), notes_quit_button, 1, 0, 2, 1);
    gtk_box_append(GTK_BOX(notes_vbox), grid);
}

/* Creat text input window layout                                             */
static void create_niw_layout(GtkWidget *notes_vbox,
                              GtkWidget *notes_hbox,
                              GtkWidget *notes_margin_left,
                              GtkWidget *notes_margin_right,
                              GtkWidget *notes_margin_top,
                              GtkWidget *notes_margin_bottom,
                              GtkWidget *notes_notepad) {

    gtk_box_append(GTK_BOX(notes_vbox), notes_margin_top);
    gtk_box_append(GTK_BOX(notes_vbox), notes_hbox);
    gtk_box_append(GTK_BOX(notes_hbox), notes_margin_left);
    gtk_box_append(GTK_BOX(notes_hbox), notes_notepad);
    gtk_box_append(GTK_BOX(notes_hbox), notes_margin_right);
    gtk_box_append(GTK_BOX(notes_vbox), notes_margin_bottom);
}
