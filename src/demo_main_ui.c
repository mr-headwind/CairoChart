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
** Description: Contrl functions to create and display each type of chart.
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
#include <libgen.h>  
#include <gtk/gtk.h>  
#include <gdk/gdkkeysyms.h>  
#include <pthread.h>
#include <main.h>
#include <isp.h>
#include <defs.h>


/* Prototypes */

void main_ui(ChartData *, Ui *);
void create_main_view(Ui *);
void chart_btns(MainUi *);
void pie_panel(MainUi *);
void bar_panel(MainUi *);
void line_panel(MainUi *);
void OnPieChart(GtkWidget*, gpointer);
void OnBarChart(GtkWidget*, gpointer);
void OnlineGraph(GtkWidget*, gpointer);
void OnQuit(GtkWidget*, gpointer);

extern void set_css();


void set_panel_btn(GtkWidget *, char *, GtkWidget *, int, int, int, int);
void create_label(GtkWidget **, char *, char *, GtkWidget *, int, int, int, int);
void create_label2(GtkWidget **, char *, char *, GtkWidget *);
void create_entry(GtkWidget **, char *, GtkWidget *, int, int);
void create_radio(GtkWidget **, GtkWidget *, char *, char *, GtkWidget *, int, char *, char *);
void create_cbox(GtkWidget **, char *, const char *[], int, int, GtkWidget *, int, int);
void show_panel(GtkWidget *, MainUi *); 
GtkWidget * debug_cntr(GtkWidget *);

extern void log_msg(char*, char*, char*, GtkWidget*);
extern int version_req_chk(IspData *, MainUi *);


/* Globals */

static const char *debug_hdr = "DEBUG-demo_main_ui.c ";


/* Create the user interface and set the CallBacks */

void main_ui(ChartData *c_data, MainUi *m_ui)
{  
    /* Set up the UI window */
    m_ui->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);  
    g_object_set_data (G_OBJECT (m_ui->window), "ui", m_ui);
    gtk_window_set_title(GTK_WINDOW(m_ui->window), TITLE);
    gtk_window_set_position(GTK_WINDOW(m_ui->window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(m_ui->window), 300, 390);
    gtk_container_set_border_width(GTK_CONTAINER(m_ui->window), 2);

    /* Main view */
    m_ui->mbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    gtk_widget_set_halign(GTK_WIDGET (m_ui->mbox), GTK_ALIGN_START);

    /* CONTROL PANEL */
    create_main_view(m_ui);

    /* INFORMATION AREA AT BOTTOM OF WINDOW */
    m_ui->status_info = gtk_label_new(NULL);
    gtk_widget_set_name (GTK_WIDGET (m_ui->status_info), "status");
    gtk_widget_set_margin_top(GTK_WIDGET (m_ui->status_info), 5);
    gtk_label_set_text(GTK_LABEL (m_ui->status_info), " ");
    gtk_widget_set_halign(GTK_WIDGET (m_ui->status_info), GTK_ALIGN_START);

    /* Combine everything onto the window */
    gtk_box_pack_start (GTK_BOX (m_ui->mbox), m_ui->ctrl_box, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (m_ui->mbox), m_ui->status_info, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(m_ui->window), m_ui->mbox);  

    /* Exit when window closed */
    g_signal_connect(m_ui->window, "destroy", G_CALLBACK(OnQuit), m_ui->window);  

    /* Show window */
    set_css();
    gtk_widget_show_all(m_ui->window);

    return;
}


/* Main view */

void create_main_view(Ui *m_ui)
{  
    /* New container for main view */
    m_ui->ctrl_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);

    /* Button panel */
    chart_btns(m_ui);

    /* Stack widget to attach the different panels to */
    m_ui->panel_stk = gtk_stack_new();
    gtk_stack_set_homogeneous(GTK_STACK (m_ui->panel_stk), TRUE);
    gtk_stack_set_transition_type (GTK_STACK (m_ui->panel_stk), GTK_STACK_TRANSITION_TYPE_NONE); 

    /* Chart panels */
    pie_panel(m_ui);
    bar_panel(m_ui);
    line_panel(m_ui);

    /* Combine everything onto the main view */
    gtk_box_pack_start (GTK_BOX (m_ui->ctrl_box), m_ui->btn_panel, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (m_ui->ctrl_box), m_ui->panel_stk, TRUE, TRUE, 0);

    return;
}


/* Chart button (menu) panel */

void chart_btns(Ui *m_ui)
{  
    int i, j;

    /* Create grid to contain function buttons */
    m_ui->btn_panel = gtk_grid_new();
    gtk_widget_set_name(m_ui->btn_panel, "btn_panel");
    gtk_grid_set_row_spacing(GTK_GRID (m_ui->btn_panel), 2);
    gtk_grid_set_column_spacing(GTK_GRID (m_ui->btn_panel), 2);
    gtk_container_set_border_width (GTK_CONTAINER (m_ui->btn_panel), 2);
    gtk_widget_set_hexpand (m_ui->btn_panel, TRUE);
    gtk_widget_set_vexpand (m_ui->btn_panel, TRUE);

    /* Create buttons */
    i = j = 0;
    m_ui->overview_btn = gtk_button_new_with_label("Pie Chart");  
    set_panel_btn(m_ui->pie_btn, "pie_btn",  m_ui->btn_panel, i, j, 1, 1);

    i++;
    m_ui->service_btn = gtk_button_new_with_label("Bar Chart");  
    set_panel_btn(m_ui->bar_btn, "bar_btn",  m_ui->btn_panel, i, j, 1, 1);

    i++;
    m_ui->monitor_btn = gtk_button_new_with_label("Line Graph");  
    set_panel_btn(m_ui->line_btn, "line_btn",  m_ui->btn_panel, i, j, 1, 1);

    i = 0;
    j++;
    m_ui->history_btn = gtk_button_new_with_label("Close");  
    set_panel_btn(m_ui->close_btn, "close_btn",  m_ui->btn_panel, i, j, 1, 1);

    /* Callbacks */
    g_signal_connect (m_ui->pie_btn, "clicked", G_CALLBACK (OnPieChart), m_ui);
    g_signal_connect (m_ui->bar_btn, "clicked", G_CALLBACK (OnBarChart), m_ui);
    g_signal_connect (m_ui->line_btn, "clicked", G_CALLBACK (OnLineGraph), m_ui);
    g_signal_connect (m_ui->close_btn, "clicked", G_CALLBACK (OnQuit), m_ui->window);

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

void show_panel(GtkWidget *cntr, MainUi *m_ui) 
{
    if (cntr == m_ui->curr_panel)
    	return;

    gtk_stack_set_visible_child (GTK_STACK (m_ui->panel_stk), cntr);

    m_ui->curr_panel = cntr;

    return;
}


/* Display a pie chart */

void pie_panel(MainUi *m_ui) 
{

    return;
}


/* Display a bar chart */

void bar_panel(MainUi *m_ui) 
{

    return;
}


/* Display a line graph */

void line_panel(MainUi *m_ui) 
{

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


/* Debug widget container */

GtkWidget * debug_cntr(GtkWidget *cntr)
{
    const gchar *widget_name;
    GtkWidget *widget;
    GtkWidgetPath *w_path;

    if (! GTK_IS_CONTAINER(cntr))
    {
	log_msg("SYS9011", "btn children", NULL, NULL);
    	return NULL;
    }

    widget_name = gtk_widget_get_name (cntr);
    printf("%s widget structure for %s\n", debug_hdr, widget_name);

    GList *child_widgets = gtk_container_get_children(GTK_CONTAINER (cntr));
    //printf("%s \tno of children %d\n", debug_hdr, g_list_length(child_widgets));

    child_widgets = g_list_first(child_widgets);

    while (child_widgets != NULL)
    {
	widget = child_widgets->data;
	widget_name = gtk_widget_get_name (widget);
	printf("%s \tname %s\n", debug_hdr, widget_name);

	w_path = gtk_container_get_path_for_child (GTK_CONTAINER (cntr), widget);
	printf("%s \tpath %s\n", debug_hdr, gtk_widget_path_to_string (w_path));

	if (GTK_IS_CONTAINER(widget))
	    debug_cntr(widget);

	if (GTK_IS_LABEL (widget))
	    break;

	child_widgets = g_list_next(child_widgets);
    }

    g_list_free (child_widgets);

    return widget;
}
