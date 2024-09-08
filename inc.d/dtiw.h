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
 * Definition of functions allowing to draw the complete text input window.   *
 *                                                                            *
 * -------------------------------------------------------------------------- */


#ifndef DTIW_H
#define DTIW_H

#include <gtk/gtk.h>
#include "defi.h"
#include "sett.h"

void tiw_widgets_initialize(GtkWidget *,
                            GtkWidget *,
                            GtkWidget *,
                            GtkWidget *,
                            GtkWidget *,
                            GtkWidget *,
                            GtkWidget *,
                            GtkWidget *,
                            GtkWidget *);

char *create_text_input_window(int,
                               const char *,
                               const int,
                               const char *,
                               const int,
                               const char *,
                               GtkWidget *,
                               GtkWidget *,
                               GtkWidget *,
                               GtkWidget *,
                               GtkWidget *,
                               GtkWidget *,
                               GtkWidget *,
                               GtkWidget *,
                               GtkWidget *,
                               GtkTextBuffer*,
                               GtkWidget *);

#endif