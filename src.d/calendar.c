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
 * Main source file of the calendar program *calendar*.                       *
 *                                                                            *
 * -------------------------------------------------------------------------- */


#include <gtk/gtk.h>
#include <errno.h>
#include <time.h>
#include "../inc.d/days.h"
#include "../inc.d/defi.h"
#include "../inc.d/init.h"
#include "../inc.d/calh.h"
#include "../inc.d/call.h"
#include "../inc.d/dhcs.h"


static void activate(GtkApplication *, gpointer);


int main(int argc, char **argv)
{

    GtkApplication *calendar;
    int status;

    calendar = gtk_application_new("simon.euchner.calendar",
                                   G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(calendar, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(calendar), argc, argv);
    g_object_unref(calendar);

    return status;
}


/* Function called when *calendar* is activated                               */
static void activate(GtkApplication *calendar, gpointer data) {

    /* --- Prepare runtime data --------------------------------------------- */

    /* Read *year* from file *year.txt*; Note: sizeof(char)=1 byte            */
    int year, len_of_path = strlen(abspath_to_datd);
    FILE *file;
    char *abspath_to_year_file = (char *)malloc(len_of_path+8+1);
    strcpy(abspath_to_year_file, abspath_to_datd);
    strcat(abspath_to_year_file, "year.txt");
    if ((file = fopen(abspath_to_year_file, "r"))) {
        fscanf(file, "%d\n", &year);
        fclose(file);
    } else {
        printf("%s\n", "Error opening file *year.txt* for reading.");
        exit(1);
    }

    /* Read in which days of *year* to mark; 0: do not mark, 1: mark          */
    int counter, len_fname = 4+1+MYL+4+1;
    char fname[len_fname], curr_index;
    char *abspath_to_dbtm_file = (char *)malloc(len_of_path+len_fname);
    int *calendar_dbtm = (int *)malloc(MPY*BPM*sizeof(int));
    snprintf(fname, len_fname, "dbtm-%d.txt", year);
    strcpy(abspath_to_dbtm_file, abspath_to_datd);
    strcat(abspath_to_dbtm_file, fname);
    counter = 0;
    if ((file = fopen(abspath_to_dbtm_file, "r"))) {
        while ((curr_index = fgetc(file)) != EOF)
            calendar_dbtm[counter++] = curr_index - '0';
    } else if (errno == ENOENT) {
        for (; counter<MPY*BPM; calendar_dbtm[counter++] = 0);
    } else {
        printf("Error opening file *%s* for reading.\n", fname);
        exit(1);
    }

    /* Compute which day corresponds to which weekday                         */
    int jan[BPM], feb[BPM], mar[BPM], apr[BPM],
        mai[BPM], jun[BPM], jul[BPM], aug[BPM],
        sep[BPM], oct[BPM], nov[BPM], dec[BPM];
    int *calendar_data[] = { jan, feb, mar, apr,
                             mai, jun, jul, aug,
                             sep, oct, nov, dec  };
    get_days(calendar_data, year, inityear, first_days_inityear);

    /* Define path to notes file                                              */
    char *abspath_to_notes_file = (char *)malloc(len_of_path+9+1);
    strcpy(abspath_to_notes_file, abspath_to_datd);
    strcat(abspath_to_notes_file, "notes.txt");

    /* Determine current year and which button represents today               */
    int calendar_today_button_index, calendar_today_year, shift = 0;
    calendar_today_button_index = calendar_today_year = 0;
    if (calendar_today_button_policy) {
        time_t current_time; time(&current_time);
        struct tm *today = localtime(&current_time);
        today->tm_mon = today->tm_mon+1;
        calendar_today_year = today->tm_year+1900;
        calendar_today_button_index
            = (today->tm_mon-1)*(int)BPM+today->tm_mday-1;
        while (!calendar_data[today->tm_mon-1][shift++])
            calendar_today_button_index++;
    }
    /* ---------------------------------------------------------------------- */

    /* --- Define widgets, initialize, set properties and load CSS ---------- */
    (void)data;
    GtkWidget *calendar_window;
    GtkWidget *calendar_vbox;
    GtkWidget *calendar_header_label, *calendar_quit_button, *calendar_header;
    GtkWidget *calendar_margin_left, *calendar_margin_right;
    GtkWidget *calendar_margin_top, *calendar_margin_bottom;
    GtkWidget *calendar_hbox, *calendar_grid;
    GtkWidget *calendar_day_name_frames[BPR];
    GtkWidget *calendar_day_name_labels[BPR];
    GtkWidget *calendar_prev_year_button, *calendar_next_year_button;
    GtkWidget *calendar_hsep_a, *calendar_hsep_b, *calendar_hsep_c;
    GtkWidget *calendar_vsep_a, *calendar_vsep_b, *calendar_vsep_c;
    GtkWidget *calendar_month_name_frames[MPY];
    GtkWidget *calendar_day_buttons[MPY*BPM];
    GtkWidget *calendar_notes_button;

    calendar_window           = gtk_application_window_new(calendar);
    calendar_vbox             = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    calendar_header_label     = gtk_label_new(NULL);
    calendar_quit_button      = gtk_button_new_with_label("X");
    calendar_header           = gtk_frame_new(NULL);
    calendar_margin_left      = gtk_frame_new(NULL);
    calendar_margin_right     = gtk_frame_new(NULL);
    calendar_margin_top       = gtk_frame_new(NULL);
    calendar_margin_bottom    = gtk_frame_new(NULL);
    calendar_hbox             = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    calendar_grid             = gtk_grid_new();
    for (int i=0; i<BPR; i++) {
        calendar_day_name_frames[i] = gtk_frame_new(NULL);
        calendar_day_name_labels[i] = gtk_label_new(day_labels[i]);
    }
    calendar_prev_year_button = gtk_button_new_with_label("<<");
    calendar_next_year_button = gtk_button_new_with_label(">>");
    calendar_hsep_a           = gtk_frame_new(NULL);
    calendar_hsep_b           = gtk_frame_new(NULL);
    calendar_hsep_c           = gtk_frame_new(NULL);
    calendar_vsep_a           = gtk_frame_new(NULL);
    calendar_vsep_b           = gtk_frame_new(NULL);
    calendar_vsep_c           = gtk_frame_new(NULL);
    for (int i=0; i<MPY; i++)
        calendar_month_name_frames[i] = gtk_frame_new(month_labels[i]);
    for (int i=0; i<MPY*BPM; i++)
        calendar_day_buttons[i] = gtk_button_new_with_label(NULL);
    calendar_notes_button = gtk_button_new_with_label(NULL);
    /* ---------------------------------------------------------------------- */

    /* Initialize and set properties of defined widgets                       */
    initialize(calendar_data,
               calendar_dbtm,
               calendar_window,
               calendar_header_label,
               calendar_quit_button,
               calendar_header,
               calendar_margin_left,
               calendar_margin_right,
               calendar_margin_top,
               calendar_margin_bottom,
               calendar_day_name_frames,
               calendar_day_name_labels,
               calendar_prev_year_button,
               calendar_next_year_button,
               calendar_hsep_a,
               calendar_hsep_b,
               calendar_hsep_c,
               calendar_vsep_a,
               calendar_vsep_b,
               calendar_vsep_c,
               calendar_month_name_frames,
               calendar_day_buttons,
               calendar_notes_button);

    /* Create header for calendar window                                      */
    create_calendar_header(&year,
                           calendar_vbox,
                           calendar_header_label,
                           calendar_quit_button,
                           calendar_header);

    /* Create actual calendar                                                 */
    create_calendar_layout(calendar_data,
                           calendar_vbox,
                           calendar_hbox,
                           calendar_grid,
                           calendar_margin_left,
                           calendar_margin_right,
                           calendar_margin_top,
                           calendar_margin_bottom,
                           calendar_day_name_frames,
                           calendar_day_name_labels,
                           calendar_prev_year_button,
                           calendar_next_year_button,
                           calendar_hsep_a,
                           calendar_hsep_b,
                           calendar_hsep_c,
                           calendar_vsep_a,
                           calendar_vsep_b,
                           calendar_vsep_c,
                           calendar_month_name_frames,
                           calendar_day_buttons,
                           calendar_notes_button);

    /* Connect signals and define callback functions                          */
    define_handlers_connect_signals(abspath_to_year_file,
                                    &year,
                                    abspath_to_dbtm_file,
                                    calendar_dbtm,
                                    calendar,
                                    calendar_window,
                                    calendar_header_label,
                                    calendar_quit_button,
                                    calendar_prev_year_button,
                                    calendar_next_year_button,
                                    calendar_day_buttons,
                                    abspath_to_notes_file,
                                    calendar_notes_button);

    /* Present main window *calendar_window* with title for window manager    */
    gtk_window_set_title(GTK_WINDOW(calendar_window), name_for_window_manager);
    gtk_window_set_child(GTK_WINDOW(calendar_window), calendar_vbox);
    gtk_window_present(GTK_WINDOW(calendar_window));
}
