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
** Application:	CairoChart
**
** Author:	Anthony Buckley
**
** Description:
**  	Main application template for using the framework. This is a guide only to highlight the
**      structure of calls and layout required to create charts. It is not compilable.
**	The demo application provides executable functionality to better demonstrate 
**	possibilities. Both are provided as a guide only, the overall application structure 
**	and layout will vary by application and is at the discretion of developers.
**
** History
**	12-Oct-2019	Initial code
**
*/


/* Includes */

#include <stdlib.h>  
#include <string.h>  
#include <gtk/gtk.h>  
#include <demo.h>
#include <cairo_chart.h>


/* Defines */


/* Types */

`
/* Structure to contain interface items */

typedef struct _ui
{
    /* User interface widgets */
    GtkWidget *window;

    /*
    **
    **	Add widgets here
    **
    */

    /*
    ** Include following chart widgets as required 
    */

    /* Widgets - pie chart */
    PieChart *pie_chart;
    GtkWidget *pie_chart_area;

    /* Widgets - bar chart */
    BarChart *bar_chart;
    GtkWidget *bar_chart_area;

    /* Widgets - line graph */
    LineGraph *line_graph;
    GtkWidget *line_graph_area;
} Ui;


/* Prototypes */

void initialise(Ui *);
void final(Ui *);
void main_ui(Ui *);

/*
** Application dependent
*/

void get_pie_data(PieDataList *);

extern PieChart * pie_chart_setup(char *, const GdkRGBA *, int, int, int, double **, int, Ui *);
extern void free_pie_chart(PieChart *);
extern void free_bar_chart(BarChart *);
extern void free_line_graph(LineGraph *);

/*
** End application dependent
*/


/* Globals */


/* Main program control */

int main(int argc, char *argv[])
{  
    Ui ui;
    PieData cfw_pie_data;

    /* Initial work */
    initialise(&ui);

    /* Initialise Gtk */
    gtk_init(&argc, &argv);  

    /* Create user interface */
    main_ui(&ui);


    /*
    ** Application dependent
    */

    /* User code - Assemble pie chart data */
    get_pie_data(&cfw_pie_data);

    /*
    **  The location of chart creation (object) function calls will be very much application dependent.
    **  The code shown below only portrays the function calls and arguments to provide.
    **  For a more specific and realistic approach, see the provided demonstration code.
    **  Note that these calls do not do any drawing. Only chart structures (pseudo objects)
    **  are created here.
    **  Drawing only occurs after the main loop has started.
    */

    /* Create pie chart - see function code for argument details */
    char title[20];
    int legend_opt, label_opt;

    strcpy(chart_title, "My Pie Chart");
    legend_opt = FALSE;
    label_opt = TRUE;

    ui->pie_chart = pie_chart_setup(chart_title, 
    				    CFW_DARK_BLUE, 
    				    CFW_TXT_DEF, 
    				    legend_opt, 
    				    label_opt, 
    				    CFW_CLR_LIGHT,
    				    &cfw_pie_data,
    				    &ui);

    /*
    ** End application dependent
    */


    /* Start main loop */
    gtk_main();  

    /* Final processing */
    final(&ui);

    exit(0);
}  


/* Initial work */

void initialise(Ui *ui)
{
    /* Set variables */
    memset(ui, 0, sizeof (Ui));

    /*
    ** Application code
    */

    return;
}


/* Final work */

void final(Ui *ui)
{
    /* Clean up as required */
    if (ui->pie_chart != NULL)
	free_pie_chart(ui->pie_chart);

    if (ui->bar_chart != NULL)
	free_bar_chart(ui->bar_chart);

    if (ui->line_graph != NULL)
	free_line_graph(ui->line_graph);

    /*
    ** Application code
    */

    return;
}


/* Create the user interface and set the CallBacks */

void main_ui(Ui *ui)
{  
    /* Set up the UI window */
    ui->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);  
    g_object_set_data (G_OBJECT (ui->window), "ui", ui);


    /*
    ** Application widgets 
    */

    /*
    ** Framework call to create Chart widgets as required
    */

    ui->pie_chart_area = cfw_gtk_pie_chart((void *) ui, NULL, NULL);		// Without size request
    ui->pie_chart_area = cfw_gtk_pie_chart((void *) ui, 250, 160);		// With size request;

    ui->bar_chart_area = cfw_gtk_bar_chart((void *) ui, NULL, NULL);		// Without size request
    ui->bar_chart_area = cfw_gtk_bar_chart((void *) ui, 250, 160);		// With size request;

    ui->line_graph_area = cfw_gtk_line_graph((void *) ui, NULL, NULL);		// Without size request
    ui->line_graph_area = cfw_gtk_line_graph((void *) ui, 250, 160);		// With size request;


    /* Exit when window closed */
    g_signal_connect(ui->window, "destroy", G_CALLBACK(OnQuit), ui->window);  

    /* Show window */
    gtk_widget_show_all(ui->window);

    return;
}


/* 
** Collect data for the pie chart. Application dependent, but ultimately must end up with a "PieData" struct.
** Build a GList of data item entries. Dont forget to free it when completed !
*/

void get_pie_data(PieData *cfw_pie_data)
{  
    /* User code - sample */
    PieListEntry *pie_data_item;
    int i;
    double total_val;

    cfw_pie_data->pie_data_list = NULL;
    total_val = 0;

    for(i = 0; i < max_items; i++)
    {
    	pie_data_item = (PieListEntry *) malloc(sizeof(PieListEntry)):
    	pie_data_item->ent_txt = &some_desc_txt;
    	pie_data_item->ent_value = some_data_val;
    	total_val += some_data_val;

    	cfw_pie_data->pie_data_list = g_list_prepend (cfw_pie_data->pie_data_list, (gpointer) pie_data_item);
    }

    cfw_pie_data->pie_data_list = g_list_reverse (cfw_pie_data->pie_data_list);

    /* Add entries for the pie chart to the list, deriving a total is optional */
    cfw_pie_list->pie_total_value = total_val;

    /* Get total number of entries */
    cfw_pie_data->pie_list_sz = g_list_length(cfw_pie_data->pie_data_list);

    return;
}
