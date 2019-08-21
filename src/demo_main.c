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
#include <main.h>
#include <defs.h>


/* Defines */


/* Prototypes */

void initialise(MainUi *);
void final(MainUi *);

extern void main_ui(MainUi *);
extern void free_pie_chart(PieChart *);
extern void free_bar_chart(BarChart *);
extern void free_line_chart(LineChart *);


/* Globals */

static const char *debug_hdr = "DEBUG-demo_main.c ";


/* Main program control */

int main(int argc, char *argv[])
{  
    MainUi m_ui;

    /* Initial work */
    initialise(&m_ui);

    /* Initialise Gtk */
    gtk_init(&argc, &argv);  

    main_ui(&m_ui);

    gtk_main();  

    final(&m_ui);

    exit(0);
}  


/* Initial work */

void initialise(MainUi *m_ui)
{
    /* Set variables */
    app_msg_extra[0] = '\0';
    memset(m_ui, 0, sizeof (MainUi));

    return;
}


/* Final work */

void final(MainUi *m_ui)
{
    /* Clean up */
    if (m_ui->pie_chart != NULL)
	free_pie_chart(m_ui->pie_chart);

    if (m_ui->bar_chart != NULL)
	free_bar_chart(m_ui->bar_chart);

    if (m_ui->line_chart != NULL)
	free_bar_chart(m_ui->line_chart);

    return;
}
