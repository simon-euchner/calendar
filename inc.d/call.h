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
 * Create calendar layout and append it to the vbox.                          *
 *                                                                            *
 * -------------------------------------------------------------------------- */


#ifndef CALL_H
#define CALL_H

#include <gtk/gtk.h>
#include "defi.h"
#include "sett.h"

void create_calendar_layout(int **,
                            GtkWidget *,
                            GtkWidget *,
                            GtkWidget *,
                            GtkWidget *,
                            GtkWidget *,
                            GtkWidget *,
                            GtkWidget *,
                            GtkWidget **,
                            GtkWidget **,
                            GtkWidget *,
                            GtkWidget *,
                            GtkWidget *,
                            GtkWidget *,
                            GtkWidget *,
                            GtkWidget *,
                            GtkWidget *,
                            GtkWidget *,
                            GtkWidget **,
                            GtkWidget **,
                            GtkWidget *);

#endif
