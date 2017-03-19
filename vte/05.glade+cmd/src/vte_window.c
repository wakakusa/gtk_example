#include "headers.h"
#include "defines.h"
#include "vte_window_structures.h"

int create_vte_window(StructVTEWidget *Struct_Widget,char UI_FILE[256])
{
  
  Struct_Widget->argva =NULL;
  Struct_Widget->Err=NULL;


#ifdef ENABLE_NLS
   bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
   bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
   textdomain (GETTEXT_PACKAGE);
#endif
   
  GtkBuilder *builder;
  GError* error = NULL;
  
  /* GtkBuilder作成 */
  builder = gtk_builder_new(); 
  
  /* UI_FILEの読み込み*/
  if (!gtk_builder_add_from_file (builder, UI_FILE, &error))
  {
	g_warning ("Couldn't load builder file: %s", error->message);
	g_error_free (error);
//	return 1;
  }

 
  /* windowのオブジェクト取得 */
  (Struct_Widget->window1) = GTK_WIDGET( gtk_builder_get_object(builder, "VTE_MainWindow")); 
  /*複数のウィジェットを操作する場合、構造体に格納にすること。
   * 格納先にあわせて、GTK_LABELやGTK_ENTRYなどGTK_～を変更すること。
   *不明な場合はGTK_WIDGETでも可能。ただしエラーは出力される。*/
      (Struct_Widget->terminal1) =  VTE_TERMINAL(gtk_builder_get_object(builder, "terminal1"));  
//  (Struct_Widget->terminal1) = GTK_WIDGET(gtk_builder_get_object(builder, "terminal1"));  
//  (Struct_Widget->button1)   = GTK_BUTTON(gtk_builder_get_object(builder, "mount"));
//  (Struct_Widget->button3)   = GTK_BUTTON(gtk_builder_get_object(builder, "mount2"));
//  (Struct_Widget->button2)   = GTK_BUTTON(gtk_builder_get_object(builder, "quit"));  
  
  /* UI_FILEのシグナルハンドラの設定  This is important */
  gtk_builder_connect_signals (builder, &Struct_Widget); 

   g_object_unref( G_OBJECT( builder ) );
   
   g_shell_parse_argv("/bin/bash", NULL, &Struct_Widget->argva, NULL);
   vte_terminal_fork_command_full(
				  VTE_TERMINAL(Struct_Widget->terminal1),
				  0,
				  NULL,Struct_Widget->argva,
				  NULL, 
				  0, 
				  NULL, 
				  NULL, 
				  NULL, 
				  &Struct_Widget->Err
				 );
   g_strfreev(Struct_Widget->argva);
  
   return 0;
}
 
