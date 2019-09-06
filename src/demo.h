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
** Description:	Demo Main program include file
**
** Author:	Anthony Buckley
**
** History
**	26-Aug-2019	Initial
**
*/




/* Defines */

#ifndef DEMO_HDR
#define DEMO_HDR
#endif

#ifndef TITLE
#define TITLE "Cairo Chart"
#endif



/* Includes */

#include <cairo_chart.h>


/* Structure to contain demo main interface items */

typedef struct _demo_ui
{
    /* Main view widgets */
    GtkWidget *window;
    GtkWidget *status_info;  
    GtkWidget *mbox;  
    GtkWidget *close_btn;

    /* Main Frame widgets */
    GtkWidget *ctrl_box;
    GtkWidget *btn_panel;
    GtkWidget *panel_stk;

    /* Button panel widgets */
    GtkWidget *pie_btn;
    GtkWidget *bar_btn;
    GtkWidget *line_btn;

    /* Chart panels */
    GtkWidget *pie_cntr;
    GtkWidget *bar_cntr;
    GtkWidget *line_cntr;

    /* Widgets - pie chart */
    PieChart *pie_chart;

    /* Widgets - bar chart */
    BarChart *bar_chart;

    /* Widgets - line graph */
    LineGraph *line_graph;

    /* Callback Handlers */
    int close_hndlr_id;

    /* Misc */
} Ui;


/* Structure for test data */

typedef struct _chart_data
{
    double *pie_data[5];
    double *bar_data[2][3];
    double *line_data[2][10];
} ChartData;
