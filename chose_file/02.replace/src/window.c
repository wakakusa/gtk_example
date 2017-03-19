#include "headers.h"
#include "defines.h"
#include "window.h"


/*メニュー・ボタンだけのパレットを作成*/
void create_window(StructWindowWidget *struct_widget,char UI_FILE[256],char Window_name[512])
{
  GtkBuilder *builder;
  GError* error = NULL;

  /* GtkBuilder作成 */
  builder = gtk_builder_new(); 
  
  /* UI_FILEの読み込み*/
  if (!gtk_builder_add_from_file (builder, UI_FILE, &error))
  {
	g_warning ("Couldn't load builder file: %s", error->message);
	g_error_free (error);
  }

  /* windowのオブジェクト取得 */
  (struct_widget->window1) = GTK_WIDGET( gtk_builder_get_object(builder, Window_name)); 
  /*複数のウィジェットを操作する場合、構造体に格納にすること。
   * 格納先にあわせて、GTK_LABELやGTK_ENTRYなどGTK_～を変更すること。
   *不明な場合はGTK_WIDGETでも可能。ただしエラーは出力される。*/
//  (struct_widget->Button1) = GTK_ENTRY(gtk_builder_get_object(builder, "button1"));

  /* UI_FILEのシグナルハンドラの設定  This is important */
  gtk_builder_connect_signals (builder, &struct_widget); 

   g_object_unref( G_OBJECT( builder ) );
}

 
G_MODULE_EXPORT void cb_file_set(  GtkFileChooserButton *fc,  GtkTextView *textview)
{
  gchar *file;
  GtkTextBuffer *textbuf;
  gchar *buf;
  gsize size;

  file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fc));

  
  textbuf = gtk_text_view_get_buffer(textview);
  /*テキストファイルを読み込み、テキストビューに表示*/
  if (g_file_get_contents(file,&buf,&size,NULL)) {
//    g_print("file = %s\n",file);
//    g_print("buf = %s , size = %d \n",buf,size);  
    gtk_text_buffer_set_text(textbuf,buf,size);
    g_free(buf);
  }
}