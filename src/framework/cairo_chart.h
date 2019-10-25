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
** Description:	Main program include file
**
** Author:	Anthony Buckley
**
** History
**	21-Oct-2019	Initial
**
*/


/* Includes */

#include <glib.h>
#include <cairo/cairo.h>


/* Defines */

#ifndef CAIRO_CHART_HDR
#define CAIRO_CHART_HDR
#endif


#ifndef CFW_OPTS
#define CFW_OPTS

#define CFW_CLR_LIGHT 1
#define CFW_CLR_MID 2
#define CFW_CLR_FULL 3

#define CFW_TXT_DEF 12

#define CFW_DARK_BLUE 1
#define CFW_DARK_RED 20
#define CFW_BLACK 30
#define CFW_WHITE 40
#endif


/* Chart Text */

typedef struct _chart_text
{
    char *txt;
    const GdkRGBA *colour;
    int sz;
    cairo_text_extents_t ext;
} CText;


/* Axis */

typedef struct _axis
{
    CText *unit;
    CText *step_mk;
    double low_val;
    double high_val;
    double step;
    double low_step;
    double high_step;
    int prec;
    double x1, y1, x2, y2;
} Axis;


/* Pie List */

typedef struct _pie_list
{
    GList *pie_data_list;
    int pie_list_sz;
    double pie_total_value;
} PieDataList;


/* Pie chart data */

typedef struct _pie_list_ent
{
    char * ent_txt;
    double ent_value;
} PieListEntry;


/* Pie Chart control details */

typedef struct _pie_chart
{
    CText *title;
    double total_value;
    int oth_txt_sz;
    int legend;
    int show_label;
    int slice_colour_tone;
    GList *pie_slices;
} PieChart;


/* Chart slice details */

typedef struct _pie_slice
{
    CText *desc;
    CText *perc_txt;
    double slice_value;
    const GdkRGBA *colour;
} PieSlice;


/* Bar Chart control details */

typedef struct _bar_chart
{
    CText *title;
    int lbl_opt;
    double chart_min_val;
    double chart_max_val;
    Axis *x_axis;
    Axis *y_axis;
    GList *bars;
} BarChart;


/* Individual Bar details */

typedef struct _bar
{
    double abs_val;
    double min_val;
    double max_val;
    GList *bar_segments;
} Bar;


/* Bar Chart segment details */

typedef struct _bar_segment
{
    CText *desc;
    CText *perc_txt;
    const GdkRGBA *colour;
    double segment_value;
} BarSegment;


/* Line Graph main details */

typedef struct _line_graph
{
    CText *title;
    Axis *x_axis;
    Axis *y_axis;
    GList *points;
    const GdkRGBA *line_colour;
} LineGraph;


/* Individual line graph points */

typedef struct _point
{
    double x_val;
    double y_val;
} Point;
