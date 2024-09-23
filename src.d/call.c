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
 * Create calendar layout and append it to the vbox.                          *
 *                                                                            *
 * -------------------------------------------------------------------------- */


#include "../inc.d/call.h"

/* Create layout of the actual calendar                                       */
void create_calendar_layout(int **calendar_data,
                            GtkWidget *calendar_vbox,
                            GtkWidget *calendar_hbox,
                            GtkWidget *calendar_grid,
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
                            GtkWidget *calendar_notes_button) {

    /* Integers for looping                                                   */
    int i, i0, j, j0, k, l, m, n;

    /* Place margin frames/grid in vbox and hbox                              */
    gtk_box_append(GTK_BOX(calendar_vbox), calendar_margin_top);
    gtk_box_append(GTK_BOX(calendar_vbox), calendar_hbox);
    gtk_box_append(GTK_BOX(calendar_hbox), calendar_margin_left);
    gtk_box_append(GTK_BOX(calendar_hbox), calendar_grid);
    gtk_box_append(GTK_BOX(calendar_hbox), calendar_margin_right);
    gtk_box_append(GTK_BOX(calendar_vbox), calendar_margin_bottom);

    /* Add day names to frames and attach frames to grid: y = -2              */
    for (i=0; i<BPR; i++) {
        gtk_frame_set_child(GTK_FRAME(calendar_day_name_frames[i]),
                            calendar_day_name_labels[i]);
        gtk_grid_attach(GTK_GRID(calendar_grid),
                        calendar_day_name_frames[i],
                        i, -2,
                        1, 1);
    }

    /* Place button to open notes on grid: < = -2                             */
    gtk_grid_attach(GTK_GRID(calendar_grid),
                    calendar_notes_button,
                    BPR+1, -2,
                    3, 1);
    gtk_button_set_label(GTK_BUTTON(calendar_notes_button),
                         calendar_notes_button_label);

    /* Place buttons to change year on grid: y = -2                           */
    gtk_grid_attach(GTK_GRID(calendar_grid),
                    calendar_prev_year_button,
                    2*(BPR+1), -2,
                    2, 1);
    gtk_grid_attach(GTK_GRID(calendar_grid),
                    calendar_next_year_button,
                    2*(BPR+1)+2+1, -2,
                    2, 1);

    /* Place separator frames on grid (hsep_a at y = -1)                      */
    gtk_grid_attach(GTK_GRID(calendar_grid),
                    calendar_hsep_a,
                    0, -1,
                    BPR*MPR+MPR-1, 1);
    gtk_grid_attach(GTK_GRID(calendar_grid),
                    calendar_hsep_b,
                    0, 1*(BPC+1)-1,
                    BPR*MPR+MPR-1, 1);
    gtk_grid_attach(GTK_GRID(calendar_grid),
                    calendar_hsep_c,
                    0, 2*(BPC+1)-1,
                    BPR*MPR+MPR-1, 1);
    gtk_grid_attach(GTK_GRID(calendar_grid),
                    calendar_vsep_a,
                    1*(BPR+1)-1, 0,
                    1, BPC*MPC+MPC-1);
    gtk_grid_attach(GTK_GRID(calendar_grid),
                    calendar_vsep_b,
                    2*(BPR+1)-1, 0,
                    1, BPC*MPC+MPC-1);
    gtk_grid_attach(GTK_GRID(calendar_grid),
                    calendar_vsep_c,
                    3*(BPR+1)-1, 0,
                    1, BPC*MPC+MPC-1);

    /* Add month name frames to grid                                          */
    k = 0;
    for (j=0; j<MPC; j++) {
        for (i=0; i<MPR; i++) {
            gtk_grid_attach(GTK_GRID(calendar_grid),
                            calendar_month_name_frames[k++],
                            i*(BPR+1), j*(BPC+1)-1,
                            BPR, 1);
        }
    }

    /* Place each day button on grid with correct label                       */
    char buffer[3];
    m = 0;
    for (j=0; j<MPC; j++) {
        j0 = j*(BPC+1);
        for (i=0; i<MPR; i++) {
            i0 = i*(BPR+1);
            for (l=0; l<BPC; l++) {
                for (k=0; k<BPR; k++) {
                    gtk_grid_attach(GTK_GRID(calendar_grid),
                                    calendar_day_buttons[m],
                                    i0+k, j0+l,
                                    1, 1);
                    if ((n = calendar_data[m/((int)BPM)][m%((int)BPM)]) != 0) {
                        sprintf(buffer, "%2d", n);
                        gtk_button_set_label(
                                GTK_BUTTON(calendar_day_buttons[m]), buffer);
                    }
                    m++;
                }
            }
        }
    }
}
