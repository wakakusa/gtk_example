#include "headers.h"
#include "rscript_editor_window_structures.h"
#include "UserInterfaceFile.h"


G_MODULE_EXPORT void RScript_Copy(GtkWidget *widget, gpointer data)
{
  StructRSCRIPTEDITORWidget *struct_widget =&RSCRIPTEDITOR1;
  GtkTextBuffer *buffer=struct_widget->textbuf1;
  gint row, col;
  GtkTextIter start,end,iter;
  gchar *text;

//  gtk_text_buffer_get_start_iter (buffer,&start);
//  gtk_text_buffer_get_end_iter (buffer,&end);
  
  
  gtk_text_buffer_get_iter_at_mark(buffer,&iter, gtk_text_buffer_get_insert(buffer));
  row = gtk_text_iter_get_line(&iter);
  gtk_text_buffer_get_iter_at_line(buffer,&start,row);
  gtk_text_buffer_get_iter_at_line(buffer,&end,row+1);
 
  g_print("phase2\n");
  text=gtk_text_iter_get_text (&start, &end);
  g_print("word:%s",text);
  
  gint x,y,trailing;
  gtk_text_view_get_iter_at_position (buffer,&iter,&trailing,x,y);
  g_print("X=%d,Y=%d\n",x,y);
}


G_MODULE_EXPORT void RScript_Count(GtkWidget *widget, gpointer data)
{
  StructRSCRIPTEDITORWidget *struct_widget =&RSCRIPTEDITOR1;
  GtkTextBuffer *buffer=struct_widget->textbuf1;
  gint row, col;
  GtkTextIter iter;

  gtk_text_buffer_get_iter_at_mark(buffer,&iter, gtk_text_buffer_get_insert(buffer));
  row = gtk_text_iter_get_line(&iter);
  col = gtk_text_iter_get_line_offset(&iter);
  g_print("Col %d Line %d\n", col+1, row+1);
}



/**ファイルを開く**/
/*ファイル選択ダイアログを表示*/
G_MODULE_EXPORT void RScript_FileOpen_Dialog(GtkWidget *widget, gpointer data)
{
  create_rscript_OpenSave_dialog(&RSCRIPT_OpenSave,UserInterfaceFile3,"filechooserdialog_open");
  gtk_dialog_run(GTK_DIALOG(RSCRIPT_OpenSave.window1));
  gtk_widget_destroy(RSCRIPT_OpenSave.window1);
//  gtk_widget_show_all((RSCRIPT_OpenSave.window1)); 
}

/*ファイル選択ダイアログをcabcelで閉じる*/
G_MODULE_EXPORT void RScript_FileOpen_Cancel(GtkWidget *widget, gpointer data)
{
  gtk_widget_destroy((RSCRIPT_OpenSave.window1)); 
}

/*ファイルを開く*/
G_MODULE_EXPORT void RScript_FileOpen_OK (GtkWidget *widget,gpointer data  )
{
  StructRSCRIPTEDITORWidget *struct_widget =&RSCRIPTEDITOR1;
  gchar *file;
  gchar *buf;
  gsize size;
 
  file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(RSCRIPT_OpenSave.window1));
  struct_widget->textbuf1 = gtk_text_view_get_buffer(struct_widget->textview1);
 
  /*テキストファイルを読み込み、テキストビューに表示*/
  if (g_file_get_contents(file,&buf,&size,NULL)) {
    gtk_text_buffer_set_text(struct_widget->textbuf1,buf,size);
    g_free(buf);
  }
  
  gtk_widget_destroy((RSCRIPT_OpenSave.window1)); 
}

/**ファイルを保存**/
/*ファイル選択ダイアログを表示*/
G_MODULE_EXPORT void RScript_FileSave_Dialog(GtkWidget *widget, gpointer data)
{
  create_rscript_OpenSave_dialog(&RSCRIPT_OpenSave,UserInterfaceFile3,"filechooserdialog_save");
  gtk_dialog_run(GTK_DIALOG(RSCRIPT_OpenSave.window1));
  gtk_widget_destroy(RSCRIPT_OpenSave.window1);
//  gtk_widget_show_all((RSCRIPT_OpenSave.window1)); 
}

/*ファイル選択ダイアログをcabcelで閉じる*/
G_MODULE_EXPORT void RScript_FileSave_Cancel(GtkWidget *widget, gpointer data)
{
  gtk_widget_destroy((RSCRIPT_OpenSave.window1)); 
}

/*ファイルを開く*/
G_MODULE_EXPORT void RScript_FileSave_OK (GtkWidget *widget,gpointer data  )
{
  g_print( "save function start\n");
  StructRSCRIPTEDITORWidget *struct_widget =&RSCRIPTEDITOR1;
  gchar *file;
  gchar *buf;
  gsize size;
  GtkTextIter start, end;
 
  file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(RSCRIPT_OpenSave.window1));
 g_print( "file_path=%s\n", file);

  //開始行のGtkTextIterを取得（行番号は0から開始）
   gtk_text_buffer_get_start_iter(struct_widget->textbuf1, &start);
  //最終行のGtkTextIterを取得
   gtk_text_buffer_get_end_iter(struct_widget->textbuf1, &end);
  //startからendまでの行のテキストを取得（UTF8でエンコーディングされ、新しく領域を確保）
   buf = gtk_text_buffer_get_text(struct_widget->textbuf1, &start, &end, TRUE);
  //テキストを保存
   g_file_set_contents(file,buf,-1,NULL);
   g_free(buf);
  
  gtk_widget_destroy((RSCRIPT_OpenSave.window1)); 
}

