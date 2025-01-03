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
 * Define signal handlers and connect signals.                                *
 *                                                                            *
 * -------------------------------------------------------------------------- */


#ifndef CSIG_H
#define CSIG_H

#include <gtk/gtk.h>
#include <errno.h>
#include "days.h"
#include "sett.h"
#include "dtiw.h"
#include "dniw.h"
#include "mcdb.h"

/* Data structure for shared data between signal handlers                     */
typedef struct _SharedData {
    char *abspath_to_year_file;
    int year;
    GtkApplication *calendar;
    GtkWidget *calendar_window;
    GtkWidget *calendar_header_label;
    GtkWidget *calendar_day_buttons[MPY*BPM];
    GtkWidget *tiw_window;
    GtkTextBuffer *tiw_buffer;
    GtkWidget *notes_window;
    GtkTextBuffer *notes_buffer;
    char *abspath_to_note;
    int tiw_pressed_day_index;
    char *abspath_to_dbtm_file;
    int *calendar_dbtm;
    char *abspath_to_notes_file;
    int calendar_today_year;
    int calendar_today_button_index;
} SharedData;

void define_handlers_connect_signals(const int,
                                     const int,
                                     char *,
                                     const int *,
                                     char *,
                                     int *,
                                     GtkApplication *,
                                     GtkWidget *,
                                     GtkWidget *,
                                     GtkWidget *,
                                     GtkWidget *,
                                     GtkWidget *,
                                     GtkWidget **,
                                     char *,
                                     GtkWidget *);

#endif
