#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#define DL_DEF_WIDTH 500

bool KE(GtkWidget *widget, GdkEventKey *event, __attribute__((__unused__)) void *data){
	if ((event->keyval)==GDK_KEY_Return) {
		char *sExec=NULL;
		sExec=(char*)g_strconcat(gtk_entry_get_text(GTK_ENTRY(widget)), " &", NULL);
		if (!(system(NULL))) exit(EXIT_FAILURE);
		system((const char*)sExec);
		g_free(sExec);
		gtk_main_quit();
	}
	return false;}

int main(void){
	GtkWidget *frmMain, *txtCommand;

	g_print("dispersion-launch 0.3.1.120 \n");
	g_print("Copyright 2012-2016 Sokolov N. P. <0xE4524FFE@gmail.com>\n");
	g_print("!!!By using this software you accept FLWP EULA!!! \n");
	g_print("You can find FLWP EULA at https://github.com/0xe4524ffe/FLWP-EULA.git if it wasn't included. \n");

	gtk_init(NULL, NULL);

	frmMain=gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title(GTK_WINDOW(frmMain), "Launch");
		gtk_window_set_position(GTK_WINDOW(frmMain), GTK_WIN_POS_CENTER);
		gtk_window_set_resizable(GTK_WINDOW(frmMain), false);
		gtk_window_set_skip_taskbar_hint(GTK_WINDOW(frmMain), true);
		gtk_container_set_border_width(GTK_CONTAINER(frmMain), 1);
	txtCommand=gtk_entry_new();
		gtk_container_add(GTK_CONTAINER(frmMain), txtCommand);
	gtk_widget_set_size_request(txtCommand, DL_DEF_WIDTH, -1);

	g_signal_connect_swapped(G_OBJECT(frmMain), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(txtCommand), "key_press_event", G_CALLBACK(KE), NULL);

	gtk_widget_show_all(frmMain);
	gtk_window_present(GTK_WINDOW(frmMain));
	gtk_widget_grab_focus(txtCommand);
	gtk_main();
	return EXIT_SUCCESS;}
