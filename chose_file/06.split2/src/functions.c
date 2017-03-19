#include "window.h"
#include "Rscript_editor_structures.h"
#include "defines.h"

G_MODULE_EXPORT void add_strings1(GtkWidget *widget, gpointer data)
{
  //StructWindowWidget *struct_widget=&RScript1;
  //gtk_text_buffer_insert_at_cursor(struct_widget->textbuf,"Hello\n",-1); 
//  gtk_text_buffer_insert_at_cursor(RScript1.textbuf,"Hello\n",-1); 
}


G_MODULE_EXPORT void cb_file_set(  GtkFileChooserButton *fc,  GtkTextView *textview)
{
/*  gchar *file;
  gchar *buf;
  gsize size;
  //StructWindowWidget *struct_widget=&RScript1;

  file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fc)); 

  /*テキストファイルを読み込み、テキストビューに表示*/
/*  if (g_file_get_contents(file,&buf,&size,NULL)) {
//    gtk_text_buffer_set_text(struct_widget->textbuf,buf,size);
        gtk_text_buffer_set_text(RScript1.textbuf,buf,size);
    g_free(buf);
  }
*/}


G_MODULE_EXPORT void open_editor(  GtkWidget *widget, gpointer data)
{
   create_window(&RScript1,UserInterfaceFile2,"RscriptEditor");
  /* windowの表示 */
  gtk_widget_show_all((RScript1.window1)); 
}