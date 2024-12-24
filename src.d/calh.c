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
 * Create calendar header and append it to the vbox.                          *
 *                                                                            *
 * -------------------------------------------------------------------------- */


#include "../inc.d/calh.h"


/* Create header for calendar window                                          */
void create_calendar_header(const int *year,
                            GtkWidget *vbox,
                            GtkWidget *calendar_header_label,
                            GtkWidget *calendar_quit_button,
                            GtkWidget *calendar_header) {

    /* Set label                                                              */
    int len = strlen(calendar_header_text) - 2 + 1;
    char buffer[len+MYL];
    snprintf(buffer, len+MYL, calendar_header_text, *year);
    gtk_label_set_text(GTK_LABEL(calendar_header_label), buffer);
    gtk_frame_set_child(GTK_FRAME(calendar_header), calendar_header_label);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_attach(GTK_GRID(grid), calendar_header, 0, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), calendar_quit_button, 1, 0, 2, 1);
    gtk_box_append(GTK_BOX(vbox), grid);
}
