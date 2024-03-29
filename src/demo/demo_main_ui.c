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
** Description: Control functions to create and display each type of chart.
**
** Author:	Anthony Buckley
**
** History
**	21-Aug-2019	Initial code
**
*/



/* Defines */
#define MAIN_UI


/* Includes */
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>
#include <errno.h>
#include <gtk/gtk.h>  
#include <demo.h>


/* Prototypes */

void main_ui(ChartData *, Ui *);
void create_main_view(Ui *);
void chart_btns(Ui *);
void set_panel_btn(GtkWidget *, char *, GtkWidget *, int, int, int, int);
void show_panel(GtkWidget *, Ui *); 
void pie_panel(Ui *);
void bar_panel(Ui *);
void line_panel(Ui *);
void OnPieChart(GtkWidget*, gpointer);
void OnBarChart(GtkWidget*, gpointer);
void OnLineGraph(GtkWidget*, gpointer);
void OnQuit(GtkWidget*, gpointer);

extern void set_css();
extern gboolean OnPieExpose(GtkWidget *, cairo_t *, gpointer);


void create_label(GtkWidget **, char *, char *, GtkWidget *, int, int, int, int);
void create_label2(GtkWidget **, char *, char *, GtkWidget *);
void create_entry(GtkWidget **, char *, GtkWidget *, int, int);
void create_radio(GtkWidget **, GtkWidget *, char *, char *, GtkWidget *, int, char *, char *);
void create_cbox(GtkWidget **, char *, const char *[], int, int, GtkWidget *, int, int);

extern void log_msg(char*, char*, char*, GtkWidget*);


/* Globals */

static const char *debug_hdr = "DEBUG-demo_main_ui.c ";


/* Create the user interface and set the CallBacks */

void main_ui(ChartData *c_data, Ui *ui)
{  
    /* Set up the UI window */
    ui->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);  
    g_object_set_data (G_OBJECT (ui->window), "ui", ui);
    g_object_set_data (G_OBJECT (ui->window), "test_data", c_data);
    gtk_window_set_title(GTK_WINDOW(ui->window), TITLE);
    gtk_window_set_position(GTK_WINDOW(ui->window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(ui->window), 300, 390);
    gtk_container_set_border_width(GTK_CONTAINER(ui->window), 2);

    /* Main view */
    ui->mbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    gtk_widget_set_halign(GTK_WIDGET (ui->mbox), GTK_ALIGN_START);

    /* CONTROL PANEL */
    create_main_view(ui);

    /* INFORMATION AREA AT BOTTOM OF WINDOW */
    ui->status_info = gtk_label_new(NULL);
    gtk_widget_set_name (GTK_WIDGET (ui->status_info), "status");
    gtk_widget_set_margin_top(GTK_WIDGET (ui->status_info), 5);
    gtk_label_set_text(GTK_LABEL (ui->status_info), " ");
    gtk_widget_set_halign(GTK_WIDGET (ui->status_info), GTK_ALIGN_START);

    /* Combine everything onto the window */
    gtk_box_pack_start (GTK_BOX (ui->mbox), ui->ctrl_box, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (ui->mbox), ui->status_info, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(ui->window), ui->mbox);  

    /* Exit when window closed */
    g_signal_connect(ui->window, "destroy", G_CALLBACK(OnQuit), ui->window);  

    /* Show window */
    set_css();
    gtk_widget_show_all(ui->window);

    return;
}


/* Main view */

void create_main_view(Ui *ui)
{  
    /* New container for main view */
    ui->ctrl_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);

    /* Button panel */
    chart_btns(ui);

    /* Stack widget to attach the different panels to */
    ui->panel_stk = gtk_stack_new();
    gtk_stack_set_homogeneous(GTK_STACK (ui->panel_stk), TRUE);
    gtk_stack_set_transition_type (GTK_STACK (ui->panel_stk), GTK_STACK_TRANSITION_TYPE_NONE); 

    /* Chart panels */
    pie_panel(ui);
    bar_panel(ui);
    line_panel(ui);

    /* Combine everything onto the main view */
    gtk_box_pack_start (GTK_BOX (ui->ctrl_box), ui->btn_panel, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (ui->ctrl_box), ui->panel_stk, TRUE, TRUE, 0);

    return;
}


/* Chart button (menu) panel */

void chart_btns(Ui *ui)
{  
    int i, j;

    /* Create grid to contain function buttons */
    ui->btn_panel = gtk_grid_new();
    gtk_widget_set_name(ui->btn_panel, "btn_panel");
    gtk_grid_set_row_spacing(GTK_GRID (ui->btn_panel), 2);
    gtk_grid_set_column_spacing(GTK_GRID (ui->btn_panel), 2);
    gtk_container_set_border_width (GTK_CONTAINER (ui->btn_panel), 2);
    gtk_widget_set_hexpand (ui->btn_panel, TRUE);
    gtk_widget_set_vexpand (ui->btn_panel, TRUE);

    /* Create buttons */
    i = j = 0;
    ui->pie_btn = gtk_button_new_with_label("Pie Chart");  
    set_panel_btn(ui->pie_btn, "pie_btn",  ui->btn_panel, i, j, 1, 1);

    i++;
    ui->bar_btn = gtk_button_new_with_label("Bar Chart");  
    set_panel_btn(ui->bar_btn, "bar_btn",  ui->btn_panel, i, j, 1, 1);

    i++;
    ui->line_btn = gtk_button_new_with_label("Line Graph");  
    set_panel_btn(ui->line_btn, "line_btn",  ui->btn_panel, i, j, 1, 1);

    i = 0;
    j++;
    ui->close_btn = gtk_button_new_with_label("Close");  
    set_panel_btn(ui->close_btn, "close_btn",  ui->btn_panel, i, j, 1, 1);

    /* Callbacks */
    g_signal_connect (ui->pie_btn, "clicked", G_CALLBACK (OnPieChart), ui);
    g_signal_connect (ui->bar_btn, "clicked", G_CALLBACK (OnBarChart), ui);
    g_signal_connect (ui->line_btn, "clicked", G_CALLBACK (OnLineGraph), ui);
    g_signal_connect (ui->close_btn, "clicked", G_CALLBACK (OnQuit), ui->window);

    return;
}


/* Set a panel button in the grid */

void set_panel_btn(GtkWidget *btn, char *nm, GtkWidget *cntr,
		   int col, int row, int c_spn, int r_spn) 
{

    gtk_widget_set_name(btn, nm);
    gtk_widget_set_vexpand (btn, TRUE);
    gtk_widget_set_hexpand (btn, TRUE);
    gtk_grid_attach(GTK_GRID (cntr), btn, col, row, c_spn, r_spn);

    return;
}


/* Maintain which panel is visible */

void show_panel(GtkWidget *cntr, Ui *ui) 
{
    if (cntr == ui->curr_panel)
    	return;

    gtk_stack_set_visible_child (GTK_STACK (ui->panel_stk), cntr);

    ui->curr_panel = cntr;

    return;
}


/* Display a pie chart */

void pie_panel(Ui *ui) 
{
    /* Create main container grid */
    ui->pie_cntr = gtk_grid_new();
    gtk_widget_set_name(ui->pie_cntr, "pie_panel");
    gtk_grid_set_row_spacing(GTK_GRID (ui->pie_cntr), 2);
    gtk_grid_set_column_spacing(GTK_GRID (ui->pie_cntr), 2);
    gtk_container_set_border_width (GTK_CONTAINER (ui->pie_cntr), 2);
    gtk_widget_set_margin_top (ui->pie_cntr, 2);
    gtk_widget_set_margin_left (ui->pie_cntr, 15);


    /*
    ** Framework call to create drawing area for pie chart
    */
    ui->pie_chart_area = cfw_gtk_pie_chart((void *) ui, 250, 160);


    /* Attach containers */
    gtk_grid_attach(GTK_GRID (ui->pie_cntr), ui->pie_chart_area, 0, 0, 1, 1);
    gtk_stack_add_named (GTK_STACK (ui->panel_stk), ui->pie_cntr, "pie_panel");

    return;
}


/* Display a bar chart */

void bar_panel(Ui *ui) 
{
    /* Create main container grid */
    ui->bar_cntr = gtk_grid_new();
    gtk_widget_set_name(ui->bar_cntr, "bar_panel");
    gtk_grid_set_row_spacing(GTK_GRID (ui->bar_cntr), 2);
    gtk_grid_set_column_spacing(GTK_GRID (ui->bar_cntr), 2);
    gtk_container_set_border_width (GTK_CONTAINER (ui->bar_cntr), 2);
    gtk_widget_set_margin_top (ui->bar_cntr, 2);
    gtk_widget_set_margin_left (ui->bar_cntr, 15);


    /*
    ** Framework call to create drawing area for bar chart
    */
    ui->bar_chart_area = cfw_gtk_bar_chart((void *) ui, 250, 160);


    /* Attach containers */
    gtk_grid_attach(GTK_GRID (ui->bar_cntr), ui->bar_chart_area, 0, 0, 1, 1);
    gtk_stack_add_named (GTK_STACK (ui->panel_stk), ui->bar_cntr, "bar_panel");

    return;
}


/* Display a line graph */

void line_panel(Ui *ui) 
{
    /* Create main container grid */
    ui->line_cntr = gtk_grid_new();
    gtk_widget_set_name(ui->line_cntr, "line_panel");
    gtk_grid_set_row_spacing(GTK_GRID (ui->line_cntr), 2);
    gtk_grid_set_column_spacing(GTK_GRID (ui->line_cntr), 2);
    gtk_container_set_border_width (GTK_CONTAINER (ui->line_cntr), 2);
    gtk_widget_set_margin_top (ui->line_cntr, 2);
    gtk_widget_set_margin_left (ui->line_cntr, 15);


    /*
    ** Framework call to create drawing area for line graph
    */
    ui->line_graph_area = cfw_gtk_line_graph((void *) ui, 250, 160);


    /* Attach containers */
    gtk_grid_attach(GTK_GRID (ui->line_cntr), ui->line_graph_area, 0, 0, 1, 1);
    gtk_stack_add_named (GTK_STACK (ui->panel_stk), ui->line_cntr, "line_panel");

    return;
}


/* Create standard label */

void create_label(GtkWidget **lbl, char *nm, char *txt, GtkWidget *cntr, 
		  int col, int row, int c_spn, int r_spn)
{  
    *lbl = gtk_label_new(txt);  
    gtk_widget_set_name(*lbl, nm);

    gtk_widget_set_halign(*lbl, GTK_ALIGN_START);
    gtk_widget_set_valign(*lbl, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_top (*lbl, 5);
    gtk_grid_attach(GTK_GRID (cntr), *lbl, col, row, c_spn, r_spn);

    return;
}


/* Create standard label */

void create_label2(GtkWidget **lbl, char *nm, char *txt, GtkWidget *cntr) 
{  
    *lbl = gtk_label_new(txt);  
    gtk_widget_set_name(*lbl, nm);

    gtk_widget_set_halign(*lbl, GTK_ALIGN_START);
    gtk_widget_set_valign(*lbl, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_top (*lbl, 5);
    gtk_widget_set_margin_start (*lbl, 10);
    gtk_box_pack_start (GTK_BOX (cntr), *lbl, FALSE, FALSE, 0);

    return;
}


/* Create standard entry */

void create_entry(GtkWidget **ent, char *nm, GtkWidget *cntr, int col, int row) 
{  
    *ent = gtk_entry_new();  
    gtk_widget_set_name(*ent, nm);

    gtk_widget_set_valign(GTK_WIDGET (*ent), GTK_ALIGN_CENTER);
    gtk_grid_attach(GTK_GRID (cntr), *ent, col, row, 1, 1);

    return;
}


/* Create standard radio */

void create_radio(GtkWidget **rad, GtkWidget *grp, char *txt, char *nm, GtkWidget *cntr, 
		  int active, char *obj_nm, char *obj_data_str)
{  
    if (grp == NULL)
	*rad = gtk_radio_button_new_with_label (NULL, txt);
    else
	*rad = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (grp), txt);

    gtk_widget_set_name(*rad, "rad_1");
    gtk_widget_set_halign(*rad, GTK_ALIGN_START);
    gtk_widget_set_valign(*rad, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_top (*rad, 0);
    gtk_widget_set_margin_start (*rad, 0);
    gtk_box_pack_start (GTK_BOX (cntr), *rad, FALSE, FALSE, 0);

    if (active == TRUE)
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (*rad), TRUE);

    if (obj_nm != NULL && obj_data_str != NULL)
	g_object_set_data_full (G_OBJECT (*rad), obj_nm, g_strdup (obj_data_str), (GDestroyNotify) g_free);

    return;
}


/* Create standard combobox */

void create_cbox(GtkWidget **cbox, char *nm, const char *arr[], int max, int active, 
		 GtkWidget *cntr, int col, int row)
{  
    int i;
    char s[max];

    *cbox = gtk_combo_box_text_new();  
    gtk_widget_set_name(*cbox, nm);

    for(i = 0; i < max; i++)
    {
    	sprintf(s, "%d", i);
    	gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT(*cbox), s, arr[i]);
    }

    gtk_combo_box_set_active (GTK_COMBO_BOX(*cbox), active);

    gtk_widget_set_halign(*cbox, GTK_ALIGN_START);
    gtk_widget_set_valign(*cbox, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_top (*cbox, 0);
    gtk_grid_attach(GTK_GRID (cntr), *cbox, col, row, 1, 1);

    return;
}


/* CALLBACKS */


/* Callback - Draw a Pie chart */

void OnPieChart(GtkWidget *btn, gpointer user_data)
{
    Ui *ui;
    ChartData *c_data;

    /* Get details */
    ui = (Ui *) user_data;
    c_data = g_object_get_data (G_OBJECT(ui->window), "test_data");

    /* Initiate pie chart */
    pie_chart();

    return;
}


/* Callback - Draw a Bar chart */

void OnBarChart(GtkWidget *btn, gpointer user_data)
{
    Ui *ui;
    ChartData *c_data;

    /* Get details */
    ui = (Ui *) user_data;
    c_data = g_object_get_data (G_OBJECT(ui->window), "test_data");

    /* Initiate pie chart */
    bar_chart();

    return;
}


/* Callback - Draw a Line graph */

void OnLineGraph(GtkWidget *btn, gpointer user_data)
{
    Ui *ui;
    ChartData *c_data;

    /* Get details */
    ui = (Ui *) user_data;
    c_data = g_object_get_data (G_OBJECT(ui->window), "test_data");

    /* Initiate pie chart */
    line_graph();

    return;
}


/* Callback - Quit */

void OnQuit(GtkWidget *w, gpointer user_data)
{
    GtkWidget *window;
    Ui *ui;

    /* Do some clean up */
    window = (GtkWidget *) user_data;
    ui = g_object_get_data (G_OBJECT(window), "ui");

    /* Close any open windows */

    /* Main quit */
    gtk_main_quit();

    return;
}

