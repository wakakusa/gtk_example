#include "MyWidgets.h"
               
/* call back function for when the button is pressed */
void on_button_clicked (GtkWidget* widget, gpointer user_data)
{
        MyWidgets               *widgets; 
        gchar                   *message;       
        GtkTextBuffer           *buffer;
        GtkTextIter             iter;
        
        /* cast the gpointer user_data into the MyWidgets structure */
        widgets = (MyWidgets *)user_data;
        
        /* build message to log appending a new line char to the end */
        message = g_strconcat (gtk_entry_get_text (GTK_ENTRY (widgets->entry)),
                               "\n", NULL);
            
        /* get the text buffer */
        buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (widgets->textview));
       
        /* get end iter */
        gtk_text_buffer_get_end_iter (buffer, &iter);
        
        /* add the message to the text buffer */
        gtk_text_buffer_insert (buffer, &iter, message, -1);
        g_free (message);
        
        /* scroll to end iter */
        gtk_text_view_scroll_to_iter (GTK_TEXT_VIEW (widgets->textview),
                                      &iter, 0.0, FALSE, 0, 0);
} 
