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
 * Define signal handlers and connect signals.                                *
 *                                                                            *
 * -------------------------------------------------------------------------- */


#include "../inc.d/dhcs.h"


static void quit_calendar(GtkWidget *, gpointer);
static void go_to_prev_year(GtkWidget *, gpointer);
static void go_to_next_year(GtkWidget *, gpointer);
static void change_year_worker(const char *, SharedData *);
static void open_text_input_window(GtkWidget *, gpointer);
static void send_destroy_signal_to_window(GtkWidget *, gpointer);
static void save_and_quit_tiw(GtkWidget *, gpointer);
static void open_window_for_notes(GtkWidget *, gpointer);
static void save_and_quit_notes(GtkWidget *widget, gpointer g_data);


/* Connect signals                                                            *
 *                                                                            *
 * Plan: Gather all shared data in a variable of type *SharedData*. All data  *
 * which is NOT a GTK object, i.e. lifetime not handled by GTKs               *
 * reference-counting, must be dereferenced in the callback function of the   *
 * quit button.                                                               */
void define_handlers_connect_signals(const int calendar_today_year,
                                     const int calendar_today_button_index,
                                     char *abspath_to_year_file,
                                     const int *year,
                                     char *abspath_to_dbtm_file,
                                     int *calendar_dbtm,
                                     GtkApplication *calendar,
                                     GtkWidget *calendar_window,
                                     GtkWidget *calendar_header_label,
                                     GtkWidget *calendar_quit_button,
                                     GtkWidget *calendar_prev_year_button,
                                     GtkWidget *calendar_next_year_button,
                                     GtkWidget **calendar_day_buttons,
                                     char *abspath_to_notes_file,
                                     GtkWidget *calendar_notes_button) {

    /* Integers for looping                                                   */
    int i, j;

    /* --- Prepare shared data ---------------------------------------------- */
    SharedData *shared_data = (SharedData *)malloc(sizeof(SharedData));
    shared_data->abspath_to_year_file = abspath_to_year_file;
    shared_data->year = *year;
    shared_data->calendar = calendar;
    shared_data->calendar_window = calendar_window;
    shared_data->calendar_header_label = calendar_header_label;
    for (i=0; i<MPY*BPM; i++)
        shared_data->calendar_day_buttons[i] = calendar_day_buttons[i];
    shared_data->abspath_to_dbtm_file = abspath_to_dbtm_file;
    shared_data->calendar_dbtm = calendar_dbtm;
    shared_data->abspath_to_notes_file = abspath_to_notes_file;
    shared_data->calendar_today_year         = calendar_today_year;
    shared_data->calendar_today_button_index = calendar_today_button_index;
    /* ---------------------------------------------------------------------- */

    /* --- Connect signals -------------------------------------------------- */

    /* calendar_change_year_button: Swicthes to different year                */
    g_signal_connect(calendar_prev_year_button,
                     "clicked",
                     G_CALLBACK(go_to_prev_year),
                     shared_data);
    g_signal_connect(calendar_next_year_button,
                     "clicked",
                     G_CALLBACK(go_to_next_year),
                     shared_data);

    /* calendar_day_buttons: Open text input window                           */
    for (i=0; i<MPY; i++) {
        for (j=0; j<BPM-5; j++) {
            g_signal_connect(GTK_BUTTON(calendar_day_buttons[i*(int)BPM+j]),
                             "clicked",
                             G_CALLBACK(open_text_input_window),
                             shared_data);
        }
    }

    /* calendar_quit_button/WM close window: Quits program *calendar*         */
    g_signal_connect(calendar_quit_button,
                     "clicked",
                     G_CALLBACK(send_destroy_signal_to_window),
                     calendar_window);
    g_signal_connect(calendar_window,
                     "destroy",
                     G_CALLBACK(quit_calendar),
                     shared_data);

    /* calendar_notes_button: Open text window for notes                      */
    g_signal_connect(calendar_notes_button,
                     "clicked",
                     G_CALLBACK(open_window_for_notes),
                     shared_data);
    /* ---------------------------------------------------------------------- */
}

/* Callback: Send destroy signal to window                                    */
static void send_destroy_signal_to_window(GtkWidget *widget, gpointer g_data) {
    (void)widget;
    gtk_window_destroy(GTK_WINDOW(g_data));
}

/* Callback: Quit program *calendar*                                          */
static void quit_calendar(GtkWidget *widget, gpointer g_data) {

    (void)widget;
    SharedData *shared_data = (SharedData *)g_data;

    /* Write to disk which days are marked in current year                    */
    int counter, sum_dbtm = 0;
    for (counter = 0; counter<MPY*BPM; counter++)
        sum_dbtm = sum_dbtm + shared_data->calendar_dbtm[counter];
    if (!sum_dbtm) {
        if (remove(shared_data->abspath_to_dbtm_file)) {
            if (errno != ENOENT) {
                printf("Error deleting dbtm file with no marks. errno: %d\n",
                       errno);
                exit(1);
            }
        }
    } else {
        FILE *file = fopen(shared_data->abspath_to_dbtm_file, "w");
        for (counter = 0; counter<MPY*BPM; counter++) {
            fprintf(file, "%d", shared_data->calendar_dbtm[counter]);
        }
        fclose(file);
    }

    /* Quit *calendar*                                                        */
    g_application_quit(G_APPLICATION(shared_data->calendar));

    /* Clean up                                                               */
    free(shared_data->abspath_to_year_file);
    free(shared_data->abspath_to_dbtm_file);
    free(shared_data->calendar_dbtm);
    free(shared_data->abspath_to_notes_file);
    free(shared_data);
}

/* Callback: Go to preveous year                                              */
static void go_to_prev_year(GtkWidget *widget, gpointer g_data) {
    (void)widget;
    SharedData *shared_data = (SharedData *)g_data;
    change_year_worker("prev", shared_data);
}

/* Callback: Go to next year                                                  */
static void go_to_next_year(GtkWidget *widget, gpointer g_data) {
    (void)widget;
    SharedData *shared_data = (SharedData *)g_data;
    change_year_worker("next", shared_data);
}

/* Worker function to change year                                             */
static void change_year_worker(const char *which, SharedData* shared_data) {

    /* Refresh *year* and header label                                        */
    if (!strcmp(which, "prev")) shared_data->year--;
    if (!strcmp(which, "next")) shared_data->year++;
    int len = strlen(calendar_header_text) - 2 + 1;
    char buffer_header[len+MYL];
    snprintf(buffer_header, len+MYL, calendar_header_text, shared_data->year);
    gtk_label_set_text(GTK_LABEL(shared_data->calendar_header_label),
                       buffer_header);

    /* --- Read in which days of the new year are marked and delete the
     *     file of the old year in case no days have been marked, if
     *     there are marked days, write *calendar_dbtm* of the old year to
     *     disk; refresh *shared_data* -------------------------------------- */
    FILE *file;

    /* Check if *old* year had marked days and handle file accordingly        */
    int counter, sum_dbtm_old = 0;
    for (counter = 0; counter<MPY*BPM; counter++)
        sum_dbtm_old = sum_dbtm_old + shared_data->calendar_dbtm[counter];
    if (!sum_dbtm_old) {
        if (remove(shared_data->abspath_to_dbtm_file)) {
            if (errno != ENOENT) {
                printf("Error deleting dbtm file with no marks. errno: %d\n",
                       errno);
                exit(1);
            }
        }
    } else {
        file = fopen(shared_data->abspath_to_dbtm_file, "w");
        for (counter = 0; counter<MPY*BPM; counter++)
            fprintf(file, "%d", shared_data->calendar_dbtm[counter]);
        fclose(file);
    }

    /* Get data of *new* year                                                 */
    int len_of_path, len_fname;
    len_of_path = strlen(abspath_to_datd);
    len_fname = 4+1+MYL+4+1;
    char fname[len_fname], curr_index;
    char buffer_dbtm[len_of_path+len_fname];
    snprintf(fname, len_fname, "dbtm-%d.txt", shared_data->year);
    strcpy(buffer_dbtm, abspath_to_datd);
    strcat(buffer_dbtm, fname);
    strcpy(shared_data->abspath_to_dbtm_file, buffer_dbtm);
    counter = 0;
    if ((file = fopen(shared_data->abspath_to_dbtm_file, "r"))) {
        while ((curr_index = fgetc(file)) != EOF)
            shared_data->calendar_dbtm[counter++] = curr_index - '0';
        fclose(file);
    } else {
        if (errno == ENOENT) {
            for (; counter<MPY*BPM; shared_data->calendar_dbtm[counter++] = 0);
        } else {
            printf("Error opening file *%s* for reading.\n", fname);
            exit(1);
        }
    }
    /* ---------------------------------------------------------------------- */

    /* Compute new day labels                                                 */
    int jan[BPM], feb[BPM], mar[BPM], apr[BPM],
        mai[BPM], jun[BPM], jul[BPM], aug[BPM],
        sep[BPM], oct[BPM], nov[BPM], dec[BPM];
    int *calendar_data[] = { jan, feb, mar, apr,
                             mai, jun, jul, aug,
                             sep, oct, nov, dec  };
    get_days(calendar_data, shared_data->year, inityear, first_days_inityear);

    /* Write labels to day buttons                                            */
    int n = 0;
    char buffer_day[3];
    for (int i=0; i<MPY*BPM; i++) {
        if ((n = calendar_data[i/((int)BPM)][i%((int)BPM)])) {
            sprintf(buffer_day, "%2d", n);
            gtk_button_set_label(
                    GTK_BUTTON(shared_data->calendar_day_buttons[i]),
                    buffer_day);
            if (shared_data->calendar_dbtm[i]) {
                gtk_widget_set_name(shared_data->calendar_day_buttons[i],
                                    "calendar_day_button_marked");
            } else {
                gtk_widget_set_name(shared_data->calendar_day_buttons[i],
                                    "calendar_day_button");
            }
        } else {
            gtk_button_set_label(
                    GTK_BUTTON(shared_data->calendar_day_buttons[i]),
                    NULL);
            gtk_widget_set_name(shared_data->calendar_day_buttons[i],
                                "calendar_day_button_off");
        }
    }

    /* Mark current day with policy *calendar_today_button_policy*            */
    int index = shared_data->calendar_today_button_index;
    mark_today(calendar_today_button_policy,
               shared_data->year,
               shared_data->calendar_today_year,
               shared_data->calendar_day_buttons[index]);

    /* Write new year to file *year.txt*                                      */
    file = fopen(shared_data->abspath_to_year_file, "w");
    fprintf(file, "%d\n", shared_data->year);
    fclose(file);
}

/* Callback: Open a text input window                                         */
static void open_text_input_window(GtkWidget *widget, gpointer g_data) {

    /* Check if the clicked day actually is a valid day and return if not     */
    if (!(*gtk_button_get_label(GTK_BUTTON(widget)))) return;

    /* Get full date of clicked day                                           */
    SharedData *shared_data = (SharedData *)g_data;
    const char *tiw_month, *tiw_weekday;
    char tiw_day[3];
    int i, tiw_year, tiw_month_number, tiw_day_number;
    tiw_year = shared_data->year;
    snprintf(tiw_day, 3, "%s", gtk_button_get_label(GTK_BUTTON(widget)));
    sscanf(tiw_day, "%d", &tiw_day_number);
    i = -1;
    while (shared_data->calendar_day_buttons[++i] != widget);
    shared_data->tiw_pressed_day_index = i;
    tiw_month_number = i/((int)BPM) + 1;
    tiw_month = month_labels[tiw_month_number-1];
    tiw_weekday = day_labels[i%((int)BPR)];

    /* --- Define widgets for text input window (tiw) and initialize them --- */
    GtkWidget *tiw_window;
    GtkWidget *tiw_vbox, *tiw_hbox;
    GtkWidget *tiw_header_label, *tiw_quit_button, *tiw_header;
    GtkWidget *tiw_margin_left, *tiw_margin_right;
    GtkWidget *tiw_margin_top, *tiw_margin_bottom;
    GtkTextBuffer *tiw_buffer;
    GtkWidget *tiw_notepad;

    tiw_window          = gtk_window_new();
    tiw_vbox            = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    tiw_hbox            = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    tiw_header_label    = gtk_label_new(NULL);
    tiw_quit_button     = gtk_button_new_with_label("X");
    tiw_header          = gtk_frame_new(NULL);
    tiw_margin_left     = gtk_frame_new(NULL);
    tiw_margin_right    = gtk_frame_new(NULL);
    tiw_margin_top      = gtk_frame_new(NULL);
    tiw_margin_bottom   = gtk_frame_new(NULL);
    tiw_buffer          = gtk_text_buffer_new(NULL);
    tiw_notepad         = gtk_text_view_new_with_buffer(tiw_buffer);

    window_widgets_initialize(tiw_window,
                              text_input_window_width,
                              text_input_window_height,
                              tiw_header_label,
                              tiw_quit_button,
                              tiw_header,
                              tiw_margin_left,
                              tiw_margin_right,
                              tiw_margin_top,
                              tiw_margin_bottom,
                              tiw_notepad);
    /* ---------------------------------------------------------------------- */

    /* Draw text input window                                                 */
    shared_data->abspath_to_note = create_text_input_window(tiw_year,
                                                            tiw_day,
                                                            tiw_day_number,
                                                            tiw_month,
                                                            tiw_month_number,
                                                            tiw_weekday,
                                                            tiw_vbox,
                                                            tiw_hbox,
                                                            tiw_header_label,
                                                            tiw_quit_button,
                                                            tiw_header,
                                                            tiw_margin_left,
                                                            tiw_margin_right,
                                                            tiw_margin_top,
                                                            tiw_margin_bottom,
                                                            tiw_buffer,
                                                            tiw_notepad);

    /* Connect signals                                                        */
    shared_data->tiw_window = tiw_window;
    shared_data->tiw_buffer = tiw_buffer;
    g_signal_connect(tiw_quit_button,
                     "clicked",
                     G_CALLBACK(send_destroy_signal_to_window),
                     tiw_window);
    g_signal_connect(tiw_window,
                     "destroy",
                     G_CALLBACK(save_and_quit_tiw),
                     shared_data);

    /* Present text input window *tiw_window* with title for window manager   */
    gtk_window_set_modal(GTK_WINDOW(tiw_window), TRUE); /* Disable            *
                                                         * interaction with   *
                                                         * parent window      */
    gtk_window_set_title(GTK_WINDOW(tiw_window), name_for_window_manager);
    gtk_window_set_child(GTK_WINDOW(tiw_window), tiw_vbox);
    gtk_window_present(GTK_WINDOW(tiw_window));
}

/* Callback: Save text to file and quit text input window                     */
static void save_and_quit_tiw(GtkWidget *widget, gpointer g_data) {

    (void)widget;
    SharedData *shared_data = (SharedData *)g_data;
    GtkTextIter start, end;
    char *buffer;

    /* Get buffer contents                                                    */
    gtk_text_buffer_get_start_iter(shared_data->tiw_buffer, &start);
    gtk_text_buffer_get_end_iter(shared_data->tiw_buffer, &end);
    buffer = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(shared_data->tiw_buffer),
                                      &start,
                                      &end,
                                      FALSE);

    /* Save buffer contents to file if not empty; in empty case delete file   *
     * if it exists; if nessesary, rename button to get marked/unmarked       */
    int charcount = gtk_text_buffer_get_char_count(
            GTK_TEXT_BUFFER(shared_data->tiw_buffer));
    int index = shared_data->tiw_pressed_day_index;
    if (charcount) {
        gtk_widget_set_name(shared_data->calendar_day_buttons[index],
                            "calendar_day_button_marked");
        shared_data->calendar_dbtm[index] = 1;
        FILE *file = fopen(shared_data->abspath_to_note, "w");
        fprintf(file, "%s", buffer);
        fclose(file);
    } else {
        if (remove(shared_data->abspath_to_note)) {
            if (errno != ENOENT) {
                printf("Error deleting file with empty note. errno: %d\n",
                       errno);
                exit(1);
            }
        } else {
            gtk_widget_set_name(shared_data->calendar_day_buttons[index],
                                "calendar_day_button");
            shared_data->calendar_dbtm[index] = 0;
        }
    }
    free(shared_data->abspath_to_note);
    free(buffer); /* Data is owned by caller and thus must be freed manually  */

    /* Decrease reference counts/clean up                                     */
    g_object_unref(shared_data->tiw_buffer);
    gtk_window_destroy(GTK_WINDOW(shared_data->tiw_window));
}

/* Callback: Open text input window for notes                                 */
static void open_window_for_notes(GtkWidget *widget, gpointer g_data) {

    (void)widget;
    SharedData *shared_data = (SharedData *)g_data;

    /* --- Define widgets for notes window and initialize them -------------- */
    GtkWidget *notes_window;
    GtkWidget *notes_vbox, *notes_hbox;
    GtkWidget *notes_header_label, *notes_quit_button, *notes_header;
    GtkWidget *notes_margin_left, *notes_margin_right;
    GtkWidget *notes_margin_top, *notes_margin_bottom;
    GtkTextBuffer *notes_buffer;
    GtkWidget *notes_notepad;

    notes_window          = gtk_window_new();
    notes_vbox            = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    notes_hbox            = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    notes_header_label    = gtk_label_new(NULL);
    notes_quit_button     = gtk_button_new_with_label("X");
    notes_header          = gtk_frame_new(NULL);
    notes_margin_left     = gtk_frame_new(NULL);
    notes_margin_right    = gtk_frame_new(NULL);
    notes_margin_top      = gtk_frame_new(NULL);
    notes_margin_bottom   = gtk_frame_new(NULL);
    notes_buffer          = gtk_text_buffer_new(NULL);
    notes_notepad         = gtk_text_view_new_with_buffer(notes_buffer);

    /* Reuse function from text input window to initialize widgets            */
    window_widgets_initialize(notes_window,
                              calendar_notes_window_width,
                              calendar_notes_window_height,
                              notes_header_label,
                              notes_quit_button,
                              notes_header,
                              notes_margin_left,
                              notes_margin_right,
                              notes_margin_top,
                              notes_margin_bottom,
                              notes_notepad);
    /* ---------------------------------------------------------------------- */

    /* Draw window to input notes                                             */
    create_window_for_notes(shared_data->abspath_to_notes_file,
                            notes_vbox,
                            notes_hbox,
                            notes_header_label,
                            notes_quit_button,
                            notes_header,
                            notes_margin_left,
                            notes_margin_right,
                            notes_margin_top,
                            notes_margin_bottom,
                            notes_buffer,
                            notes_notepad);

    /* Connect signals                                                        */
    shared_data->notes_window = notes_window;
    shared_data->notes_buffer = notes_buffer;
    g_signal_connect(notes_quit_button,
                     "clicked",
                     G_CALLBACK(send_destroy_signal_to_window),
                     notes_window);
    g_signal_connect(notes_window,
                     "destroy",
                     G_CALLBACK(save_and_quit_notes),
                     shared_data);

    /* Present text input window *notes_window* with title for window manager */
    gtk_window_set_modal(GTK_WINDOW(notes_window), TRUE); /* Disable          *
                                                           * interaction with *
                                                           * parent window    */
    gtk_window_set_title(GTK_WINDOW(notes_window), name_for_window_manager);
    gtk_window_set_child(GTK_WINDOW(notes_window), notes_vbox);
    gtk_window_present(GTK_WINDOW(notes_window));
}

/* Callback: Save text to file and quit notes window                          */
static void save_and_quit_notes(GtkWidget *widget, gpointer g_data) {

    (void)widget;
    SharedData *shared_data = (SharedData *)g_data;
    GtkTextIter start, end;
    char *buffer;

    /* Get buffer contents                                                    */
    gtk_text_buffer_get_start_iter(shared_data->notes_buffer, &start);
    gtk_text_buffer_get_end_iter(shared_data->notes_buffer, &end);
    buffer = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(
                                          shared_data->notes_buffer),
                                      &start,
                                      &end,
                                      FALSE);

    /* Save buffer contents to file                                           */
    FILE *file = fopen(shared_data->abspath_to_notes_file, "w");
    fprintf(file, "%s", buffer);
    free(buffer); /* Data is owned by caller and thus must be freed manually  */
    fclose(file);

    /* Decrease reference counts/clean up                                     */
    g_object_unref(shared_data->notes_buffer);
    gtk_window_destroy(GTK_WINDOW(shared_data->notes_window));
}
