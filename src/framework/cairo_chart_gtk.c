/*
**  Copyright (C) 2019 Anthony Buckley
** 
**  This file is part of CairoChart.
** 
**  CairoChart is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**  
**  CairoChart is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**  
**  You should have received a copy of the GNU General Public License
**  along with CairoChart.  If not, see <http://www.gnu.org/licenses/>.
*/


/*
** Description: GTK widgets for drawing Cairo charts
**
** Author:	Anthony Buckley
**
** History
**	07-Oct-2019	Initial code
**
*/


/* Includes */

#include <gtk/gtk.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


/* Defines */


/* Types */


/* Prototypes */

GtkWidget * cfw_gtk_pie_chart(void *, int, int);
GtkWidget * cfw_gtk_bar_chart(void *, int, int);
GtkWidget * cfw_gtk_line_graph(void *, int, int);


/* Globals */

static const char *debug_hdr = "DEBUG-cairo_chart_gtk.c ";



/* 
**    Drawing container for a new pie chart
**    Parameters:
**	. ui struct (typedef) for availability in callback function
**	. if a size request is desired, enter width and height otherwise NULL
*/

GtkWidget * cfw_gtk_pie_chart(void *ui, int sz_width, int sz_height)
{
    GtkWidget *pie_chart_area;

    pie_chart_area = gtk_drawing_area_new();
    gtk_widget_set_name (pie_chart_area, "pie_chart_area");
    gtk_widget_set_margin_top (pie_chart_area, 1);
    gtk_widget_set_halign (pie_chart_area, GTK_ALIGN_CENTER);
    gtk_widget_set_valign (pie_chart_area, GTK_ALIGN_CENTER);

    if (sz_width != NULL && sz_height != NULL)
	gtk_widget_set_size_request (pie_chart_area, sz_width, sz_height);

    g_signal_connect (pie_chart_area, "draw", G_CALLBACK (OnPieExpose), ui);

    return pie_chart_area;
}


/* 
**    Drawing container for a new bar chart
**    Parameters:
**	. ui struct (typedef) for availability in callback function
**	. if a size request is desired, enter width and height otherwise NULL
*/

GtkWidget * cfw_gtk_bar_chart(void *ui, int sz_width, int sz_height)
{
    GtkWidget *bar_chart_area;

    bar_chart_area = gtk_drawing_area_new();
    gtk_widget_set_name (bar_chart_area, "bar_chart_area");
    gtk_widget_set_margin_top (bar_chart_area, 1);
    gtk_widget_set_halign (bar_chart_area, GTK_ALIGN_CENTER);
    gtk_widget_set_valign (bar_chart_area, GTK_ALIGN_CENTER);

    if (sz_width != NULL && sz_height != NULL)
	gtk_widget_set_size_request (bar_chart_area, sz_width, sz_height);

    g_signal_connect (bar_chart_area, "draw", G_CALLBACK (OnBarExpose), ui);

    return bar_chart_area;
}


/* 
**    Drawing container for a new line graph
**    Parameters:
**	. ui struct (typedef) for availability in callback function
**	. if a size request is desired, enter width and height otherwise NULL
*/

GtkWidget * cfw_gtk_line_graph(void *ui, int sz_width, int sz_height)
{
    GtkWidget *line_graph_area;

    line_graph_area = gtk_drawing_area_new();
    gtk_widget_set_name (line_graph_area, "line_graph_area");
    gtk_widget_set_margin_top (line_graph_area, 1);
    gtk_widget_set_halign (line_graph_area, GTK_ALIGN_CENTER);
    gtk_widget_set_valign (line_graph_area, GTK_ALIGN_CENTER);

    if (sz_width != NULL && sz_height != NULL)
	gtk_widget_set_size_request (line_graph_area, sz_width, sz_height);

    g_signal_connect (line_graph_area, "draw", G_CALLBACK (OnLineGraphExpose), ui);

    return line_graph_area;
}
