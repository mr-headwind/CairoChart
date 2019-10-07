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

PieChart * pie_chart_create(char *, double, int, const GdkRGBA *, int, int);


/* Globals */

static const char *debug_hdr = "DEBUG-cairo_chart_gtk.c ";



// Drawing container for a new pie chart
//	The ui struct (typedef) passed must an entry 

GtkWidget * pie_chart_create(Ui *m_ui)
{
    /* Create a container grid */
    m_ui->pie_cntr = gtk_grid_new();
    gtk_widget_set_name(m_ui->pie_cntr, "pie_panel");
    gtk_grid_set_row_spacing(GTK_GRID (m_ui->pie_cntr), 2);
    gtk_grid_set_column_spacing(GTK_GRID (m_ui->pie_cntr), 2);
    gtk_container_set_border_width (GTK_CONTAINER (m_ui->pie_cntr), 2);
    gtk_widget_set_margin_top (m_ui->pie_cntr, 2);
    gtk_widget_set_margin_left (m_ui->pie_cntr, 15);

    /* Create drawing area for line graph */
    m_ui->pie_chart_area = gtk_drawing_area_new();
    gtk_widget_set_name ( m_ui->pie_chart_area, "draw_pie");
    gtk_widget_set_margin_top (m_ui->pie_chart_area, 1);
    gtk_widget_set_size_request (m_ui->pie_chart_area, 250, 160);
    gtk_widget_set_halign (m_ui->pie_chart_area, GTK_ALIGN_CENTER);
    gtk_widget_set_valign (m_ui->pie_chart_area, GTK_ALIGN_CENTER);
    gtk_grid_attach(GTK_GRID (m_ui->pie_cntr), m_ui->pie_chart_area, 0, 0, 1, 1);

    g_signal_connect (m_ui->pie_chart_area, "draw", G_CALLBACK (OnPieExpose), m_ui);

    return pc;
}
