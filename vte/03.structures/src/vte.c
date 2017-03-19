#include "headers.h"
#include "vte_window_structures.h"

int main (int argc, char *argv[])
{

  VTE1.argva = NULL;
  VTE1.Err = NULL;

#ifdef ENABLE_NLS
   bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
   bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
   textdomain (GETTEXT_PACKAGE);
#endif
   
   gtk_init (&argc, &argv);

   VTE1.window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title (GTK_WINDOW (VTE1.window), "My Title");
   gtk_window_set_position (GTK_WINDOW (VTE1.window), GTK_WIN_POS_CENTER_ALWAYS);
   gtk_window_set_default_size (GTK_WINDOW (VTE1.window), 900, 600);

   VTE1.scrollview = gtk_scrolled_window_new( NULL, NULL );

   gtk_container_add(GTK_CONTAINER (VTE1.window), VTE1.scrollview);

   VTE1.term = vte_terminal_new();
   g_shell_parse_argv("/bin/bash", NULL, &VTE1.argva, NULL);
   vte_terminal_fork_command_full(VTE_TERMINAL(VTE1.term), 0, NULL, VTE1.argva, NULL, 0, NULL, NULL, NULL, &VTE1.Err);
   g_strfreev(VTE1.argva);

   gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (VTE1.scrollview), GTK_WIDGET (VTE1.term));

   g_signal_connect (VTE1.window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

   gtk_widget_show_all (VTE1.window);

   gtk_main ();

   return 0;
}
 
