typedef struct {
   GtkWidget *window1;
   GtkWidget *scrollview;
   GtkTextView *textview1;
   gchar *file1;
   GtkTextBuffer *textbuf1;
   gchar *buf1;
   gsize size1;
}StructRSCRIPTEDITORWidget;

/*構造体変数名を宣言*/
  StructRSCRIPTEDITORWidget RSCRIPTEDITOR1;


typedef struct {
   GtkWidget *window1;
   gchar *file1;
   GtkTextBuffer *textbuf1;
   gchar *buf1;
   gsize size1;
}StructRSCRIPTEDITOR_OPENSAVE_Widget;  

/*構造体変数名を宣言*/
 StructRSCRIPTEDITOR_OPENSAVE_Widget RSCRIPT_OpenSave;
