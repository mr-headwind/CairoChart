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
**      structure of calls and layout required to create charts. The demo application provides executable
**      functionality to better demonstrate possibilities. Both are provided as a guide only, the overall 
**	Application structure and layout will vary by application and is at the discretion of developers.
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
    ** Include chart widgets as required 
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

void get_pie_data(&pie_data, &pie_arr_sz);


extern PieChart * pie_chart_setup(char *, const GdkRGBA *, int, int, int, double **, int, Ui *);

/*
** User code to free charts as required 
*/
void free_pie_chart(PieChart *);
void free_bar_chart(BarChart *);
void free_line_graph(LineGraph *);


/* Globals */


/* Main program control */

int main(int argc, char *argv[])
{  
    Ui ui;
    double *pie_data_arr;
    int pie_arr_sz.

    /* Initial work */
    initialise(&ui);

    /* Initialise Gtk */
    gtk_init(&argc, &argv);  

    /* Create user interface */
    main_ui(&ui);



    /* User code - Assemble pie chart data */
    get_pie_data(&pie_data_arr, &pie_arr_sz);


    /*
    **  The location of chart creation (object) function calls will be very much application dependent.
    **  The code shown below only portrays the function calls and arguments to provide.
    **  For a more specific and realistic approach, see the provided demonstration code.
    **  Note that these calls do not do any drawing. Only chart structures (pseudo objects).
    **  Drawing only occurs once the main loop has started.
    */

    /* Create pie chart - see function code for argument details */
    ui->pie_chart = pie_chart_setup("Title", 
    				    &DARK_BLUE, text_sz, 
    				    legend_opt, label_opt, 
    				    &pie_data_arr, pie_arr_sz,
    				    &ui);




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
** Collect data for the pie chart. Application dependent, but ultimatelly must end up with a pointer to an 
** array of doubles and the number of entries.
*/

void get_pie_data(double **pie_data, int *arr_sz)
{  
    /* User code */

    //*pie_data = malloc(entries * sizeof(double));

    return;
}
