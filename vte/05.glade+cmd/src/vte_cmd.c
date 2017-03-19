#include "headers.h"
#include "vte_window_structures.h"

G_MODULE_EXPORT void callback_mount1(GtkWidget *widget, gpointer data)
{
  vte_terminal_feed_child(VTE1.terminal1,"mount\n",-1);
}

G_MODULE_EXPORT void callback_mount2(GtkWidget *widget, gpointer data)
{
  vte_terminal_feed_child(VTE1.terminal1,"ls\n",-1);
}
