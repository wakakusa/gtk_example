#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include <vte/vte.h>

int main (int argc, char *argv[])
{
   GtkWidget *window;
   GtkWidget *scrollview;
   char** argva = NULL;   
   GError* Err = NULL;
   GtkWidget* term;

#ifdef ENABLE_NLS
   bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
   bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
   textdomain (GETTEXT_PACKAGE);
#endif
   
   gtk_init (&argc, &argv);

   window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title (GTK_WINDOW (window), "My Title");
   gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER_ALWAYS);
   gtk_window_set_default_size (GTK_WINDOW (window), 900, 600);

   scrollview = gtk_scrolled_window_new( NULL, NULL );

   gtk_container_add(GTK_CONTAINER (window), scrollview);

   term = vte_terminal_new();
   g_shell_parse_argv("/bin/bash", NULL, &argva, NULL);
   vte_terminal_fork_command_full(VTE_TERMINAL(term), 0, NULL, argva, NULL, 0, NULL, NULL, NULL, &Err);
   g_strfreev(argva);

   gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrollview), GTK_WIDGET (term));

   g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

   gtk_widget_show_all (window);

   gtk_main ();

   return 0;
}
 
