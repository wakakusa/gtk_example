#include <string.h>
#include <stdio.h>

#include "console.h"

#define TITLE "console"
#define WIDTH 320
#define HEIGHT 240

static Console *console;


static void callback(Console *console, const char *command)
{
	console_write(console, command);
	console_write(console, "\n");
}


int main(int argc, char *argv[])
{
	GtkWidget *window;

	gtk_set_locale();

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), TITLE);
	gtk_window_resize(GTK_WINDOW(window), WIDTH, HEIGHT);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	console = console_new();
	gtk_container_add(GTK_CONTAINER(window), CONSOLE_WIDGET(console));

	console_set_callback(console, callback);

	console_write(console, "console start\n");
	console_start(console);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}

