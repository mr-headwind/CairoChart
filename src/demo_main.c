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
**  	Main application control for CairoChart - a Cairo charting toolkit
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
extern void free_line_chart(LineGraph *);


/* Globals */

static const char *debug_hdr = "DEBUG-demo_main.c ";
static const double *pie_test[] = { 150.0, 523.0, 75.0, 350.0, 10.0 };
static const double *bar_test[][3] = { { 5.0, 25.0, 15.0 }, { 15.0, 25.0, 43.0 } };
static const double *line_test[][10] = {
					( 0.0, 0.0 }, 
					( 1.0, 5.0 }, 
					{ 2.0, 2.0 },
					{ 3.0, 25.0 },
					{ 4.0, 30.0 },
					{ 5.0, 12.0 },
					{ 6.0, 0.0 },
					{ 7.0, 18.0 },
					{ 8.0, 23.0 },
					{ 9.0, 29.0 },
					{ 10.0, 15.0 }
				       };


/* Main program control */

int main(int argc, char *argv[])
{  
    Ui m_ui;
    ChartData chart_data;

    /* Initial work */
    initialise(&ChartData, &m_ui);

    /* Initialise Gtk */
    gtk_init(&argc, &argv);  

    main_ui(&ChartData, &m_ui);

    gtk_main();  

    final(&m_ui);

    exit(0);
}  


/* Initial work */

void initialise(ChartData *c_data, Ui *m_ui)
{
    /* Set variables */
    memset(m_ui, 0, sizeof (Ui));
    c_data->pie_data = pie_test;
    c_data->bar_data = bar_test;
    c_data->line_data = line_test;

    return;
}


/* Final work */

void final(Ui *m_ui)
{
    /* Clean up */
    if (m_ui->pie_chart != NULL)
	free_pie_chart(m_ui->pie_chart);

    if (m_ui->bar_chart != NULL)
	free_bar_chart(m_ui->bar_chart);

    if (m_ui->line_chart != NULL)
	free_bar_chart(m_ui->line_graph);

    return;
}
