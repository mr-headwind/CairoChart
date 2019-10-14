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
**	A demo program to show how to use CairoChart - a Cairo charting framework toolkit.
**  	Main program control functions.
**
** History
**	21-Aug-2019	Initial code
**
*/


/* Includes */

#include <stdlib.h>  
#include <string.h>  
#include <gtk/gtk.h>  
#include <demo.h>


/* Defines */


/* Types */


/* Prototypes */

void initialise(ChartData *, Ui *);
void final(Ui *);

extern void main_ui(ChartData *, Ui *);
extern void free_pie_chart(PieChart *);
extern void free_bar_chart(BarChart *);
extern void free_line_graph(LineGraph *);


/* Globals */

static const char *debug_hdr = "DEBUG-demo_main.c ";
static const double pie_test[5] = { 150.0, 523.0, 75.0, 350.0, 10.0 };
static const double bar_test[2][3] = { { 5.0, 25.0, 15.0 }, { 15.0, 25.0, 43.0 } };
static const double line_test[10][2] = {
					{ 0.0, 0.0 }, 
					{ 1.0, 5.0 }, 
					{ 2.0, 2.0 },
					{ 3.0, 25.0 },
					{ 4.0, 30.0 },
					{ 5.0, 12.0 },
					{ 6.0, 0.0 },
					{ 7.0, 18.0 },
					{ 9.0, 29.0 },
					{ 10.0, 15.0 }
				       };


/* Main program control */

int main(int argc, char *argv[])
{  
    Ui ui;
    ChartData chart_data;

    /* Initial work */
    initialise(&chart_data, &ui);

    /* Initialise Gtk */
    gtk_init(&argc, &argv);  

    main_ui(&chart_data, &ui);

    gtk_main();  

    final(&ui);

    exit(0);
}  


/* Initial work */

void initialise(ChartData *c_data, Ui *ui)
{
    /* Set variables */
    memset(ui, 0, sizeof (Ui));
    c_data->pie_data = &pie_test;
    c_data->bar_data = &bar_test;
    c_data->line_data = &line_test;

    return;
}


/* Final work */

void final(Ui *ui)
{
    /* Clean up */
    if (ui->pie_chart != NULL)
	free_pie_chart(ui->pie_chart);

    if (ui->bar_chart != NULL)
	free_bar_chart(ui->bar_chart);

    if (ui->line_graph != NULL)
	free_line_graph(ui->line_graph);

    return;
}
