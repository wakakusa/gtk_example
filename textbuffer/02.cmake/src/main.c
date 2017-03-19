/*http://www.gtkforums.com/viewtopic.php?t=1307
Example logging to a GtkTextView and automatically scrolling to the newly 
inserted text.

Written for www.gtkforums.com by Micah Carrick

Compile using:
cc -Wall -g main.c -o example -export-dynamic `pkg-config --cflags --libs gtk+-2.0` 
*/

#include "MyWidgets.h"

int main (int argc, char *argv[])
{
       
        GtkWidget               *window;
        GtkBuilder              *builder;
        MyWidgets               *widgets;
        PangoFontDescription    *font_desc;
        GError                  *err = NULL;
        
        /* allocate space for widgets struct */
        widgets = g_slice_new (MyWidgets);
       
        /* initialize the GTK+ library */
        gtk_init (&argc, &argv);

        /*  Build UI from xml description */
        builder = gtk_builder_new ();
        gtk_builder_add_from_file (builder, "./glade/ui.glade", &err);
        
        if (err)
        {
            /* There was an error building the interface */
            g_error (err->message);
            g_error_free (err);
            g_slice_free (MyWidgets, widgets);
            return 1;
        }
        
        /* get widgets from GladeXML object */
        window = GTK_WIDGET (gtk_builder_get_object (builder, "window"));
        widgets->entry = GTK_WIDGET (gtk_builder_get_object (builder, "entry"));
        widgets->textview = GTK_WIDGET (gtk_builder_get_object (builder, 
                                                                "textview"));
       
        /* connect callback functions passing MyWidgets struct as user_dada */
        gtk_builder_connect_signals (builder, widgets);
        
        /* free memory used by builder object and XML */
        g_object_unref (G_OBJECT (builder));      
             
        /* use a fixed width font on the text view so the output looks proper */
        font_desc = pango_font_description_from_string ("monospace 10");
        gtk_widget_modify_font (widgets->textview, font_desc);     
        pango_font_description_free (font_desc);     
             
        /* show the main window */
        gtk_widget_show (window);

        gtk_main ();
       
        /* free space for widget struct */
        g_slice_free (MyWidgets, widgets);
        
        return 0;     
}