/*ヘッダーの読み込み順番でエラーが発生するため、注意すること*/
#include "headers.h"
#include "UserInterfaceFile.h"
#include "rscript_editor_window_structures.h"

/* For testing propose use the local (not installed) ui file */
/* #define UI_FILE PACKAGE_DATA_DIR"/sample/ui/sample.ui" */
/* gladeでuiファイルを新規作成する場合、可視性が「いいえ」になっていることを確認すること*/

int main(int argc, char *argv[])
{
  /* Gtkの初期化*/
  gtk_init(&argc,&argv); 
  
  
  create_rscript_editor(&RSCRIPTEDITOR1,UserInterfaceFile3,"RscriptEditor");
  /* windowの表示 */
  gtk_widget_show_all((RSCRIPTEDITOR1.window1)); 
 
  
  /* イベントループ開始 */
  gtk_main(); 
 
  return 0;
}

