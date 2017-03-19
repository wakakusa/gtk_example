/*
 * console
 *
 * 2010.2.20 Yuu Kasuga
 */

#ifndef CONSOLE_H
#define CONSOLE_H


#include <gtk/gtk.h>


#define CONSOLE_PROMPT_SIZE 16
#define CONSOLE_DEFAULT_PROMPT "> "
#define CONSOLE_DEFAULT_FONT "MS Gothic 9"
#define CONSOLE_COMMAND_HISTORY_SIZE 100


typedef struct Console{
	GtkWidget *scroll_window;
	GtkWidget *text_view;
	GtkTextBuffer *text_buffer;
	int start;
	char prompt[CONSOLE_PROMPT_SIZE+1];
	int command_line;
	int command_start_index;
	void (*callback)(struct Console *, const char *);
	char **command_history;
	int command_history_size;
	int command_history_max_size;
	int command_history_index;
} Console;

#define CONSOLE_WIDGET(console) console->scroll_window


typedef void (*Callback)(Console *, const char *);


Console* console_new(void);
void console_delete(Console *console);
void console_start(Console *console);
void console_set_prompt(Console *console, const char *prompt);
void console_set_callback(Console *console, Callback callback);
void console_set_font(Console *console, const char *font);
void console_write(Console *console, const char *str);


#endif /* CONSOLE_H */

