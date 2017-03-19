#include "window.h"
#include "defines.h"

G_MODULE_EXPORT void add_strings1(GtkWidget *widget, gpointer data)
{
  StructWindowWidget *struct_widget=&MainWindow;
  gtk_text_buffer_insert_at_cursor(struct_widget->textbuf,"Hello\n",-1);  
}


G_MODULE_EXPORT void cb_file_set(  GtkFileChooserButton *fc,  GtkTextView *textview)
{
  gchar *file;
  gchar *buf;
  gsize size;
  StructWindowWidget *struct_widget=&MainWindow;

  file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fc)); 

  /*テキストファイルを読み込み、テキストビューに表示*/
  if (g_file_get_contents(file,&buf,&size,NULL)) {
    gtk_text_buffer_set_text(struct_widget->textbuf,buf,size);
    g_free(buf);
  }
}