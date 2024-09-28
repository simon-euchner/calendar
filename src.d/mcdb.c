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
 * In this file a function is implemented, responsible for marking the        *
 * current day. Name: M(m)ark C(c)urrent D(d)ay B(b)utton                     *
 *                                                                            *
 * -------------------------------------------------------------------------- */


#include "../inc.d/mcdb.h"


/* Mark current day button with policy *policy*;                              *
 * policy 0: Do not mark current day                                          *
 * policy 1: Mark current day but do not overwrite CSS settings of button     *
 * policy 2: Mark current day and, if nessesary, overwrite CSS settings       */
void mark_today(int policy,
                int year,
                int calendar_today_year,
                GtkWidget *calendar_today_button) {
    switch (policy) {
        case 0: return;
        case 1: if (    (year == calendar_today_year)
                     && strcmp(gtk_widget_get_name(calendar_today_button),
                               "calendar_day_button_marked")               )
                    gtk_widget_set_name(calendar_today_button,
                                        "calendar_today_button");
                return;
        case 2: if (year == calendar_today_year)
                    gtk_widget_set_name(calendar_today_button,
                                        "calendar_today_button");
                return;
        default: return;
    }
}
