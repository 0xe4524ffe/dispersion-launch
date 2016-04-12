#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#define UNUSED __attribute__((__unused__))
#define DL_DEF_WIDTH 500

bool VersionPrint(UNUSED char *restrict sArg, UNUSED char *restrict sVal, UNUSED void *data, UNUSED GError **err){
	g_print("dispersion-launch 0.4.0.129\nCopyright 2012-2016 Sokolov N. P. <0xE4524FFE@gmail.com>\nBy using this software you accept FLWP EULA\nYou can find FLWP EULA at https://github.com/0xe4524ffe/FLWP-EULA if it wasn't included\n");
	exit(EXIT_SUCCESS);
	return true;
}

bool KE(GtkWidget *w, GdkEventKey *e, UNUSED void *data){
	if((e->keyval)==GDK_KEY_Return){
		if(!(system(NULL))) exit(EXIT_FAILURE);
		char *sExec=(char*)g_strconcat(gtk_entry_get_text(GTK_ENTRY(w)), " &", NULL);
		system((const char*)sExec);
		gtk_main_quit();
	}
	return false;
}

int main(int argc, char *argv[]){   
	GError *err=NULL;
	GOptionEntry aOpt[]={
		{"version", 'V', G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK, (void*)(intptr_t)VersionPrint, "Display version information and exit", NULL},
		{NULL}
	};
	GOptionContext *cOpt=g_option_context_new(" - launch application");
	g_option_context_add_main_entries(cOpt, aOpt, NULL);
	g_option_context_add_group(cOpt, gtk_get_option_group(true));
	if(!g_option_context_parse(cOpt, &argc, &argv, &err)){
		g_printerr("Option parsing failed: %s\n", err->message);
		exit(EXIT_FAILURE);
    }
    if(err) g_error_free(err);

        if(argv[1]){
                if(!system(NULL)) exit(EXIT_FAILURE);
                char *sExec=g_strconcat("gtk-launch ", argv[1], " &");
                system(sExec);
                exit(EXIT_SUCCESS);
        }

	GtkWidget *frmMain=gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title(GTK_WINDOW(frmMain), "Launch");
		gtk_window_set_resizable(GTK_WINDOW(frmMain), false);
		gtk_window_set_skip_taskbar_hint(GTK_WINDOW(frmMain), true);
		gtk_window_set_keep_above(GTK_WINDOW(frmMain), true);
		gtk_container_set_border_width(GTK_CONTAINER(frmMain), 1);
		gtk_window_set_icon_name(GTK_WINDOW(frmMain), "system-run");
	GtkWidget *txtCommand=gtk_entry_new();
		gtk_container_add(GTK_CONTAINER(frmMain), txtCommand);
		gtk_widget_set_size_request(txtCommand, DL_DEF_WIDTH, -1);

	g_signal_connect_swapped(G_OBJECT(frmMain), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(txtCommand), "key_press_event", G_CALLBACK(KE), NULL);

	gtk_widget_show_all(frmMain);
	gtk_window_set_position(GTK_WINDOW(frmMain), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_present(GTK_WINDOW(frmMain));
	gtk_widget_grab_focus(txtCommand);
	gtk_main();
	return EXIT_SUCCESS;
}
