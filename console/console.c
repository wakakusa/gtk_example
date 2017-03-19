/*
 * console
 *
 * 2010.2.20 Yuu Kasuga
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gdk/gdkkeysyms.h>

#include "console.h"


static int key_printable(int keyval);
static int key_arrow(int keyval);
static gboolean key_press(GtkWidget *widget, GdkEventKey *event,
  Console *console);
static gboolean button_press(GtkWidget *widget, GdkEventButton *event,
  gpointer data);

static int editable_iter(Console *console, GtkTextIter *iter);
static int editable(Console *console);

static int can_move_left(Console *console);
static void move_left(Console *console);
static void move_right(Console *console);

static void nextline(Console *console);
static void prompt(Console *console);
static void update(Console *console);

static void delete(Console *console);
static void backspace(Console *console);
static void clear(Console *console);

static void clear_command_cursor_to_start(Console *console);
static void clear_command_cursor_to_end(Console *console);
static void clear_command(Console *console);

static char* get_command(Console *console);
static void command_proc(Console *console);

static void get_cursor_iter(Console *console, GtkTextIter *iter);
static int get_cursor_line(Console *console);
static int get_cursor_line_index(Console *console);
static void get_command_start_iter(Console *console, GtkTextIter *iter);

static void get_command_end_iter(Console *console, GtkTextIter *iter);
static int get_command_line(Console *console);

static void move_cursor_to_command_start(Console *console);
static void move_cursor_to_command_end(Console *console);
static void scroll_to_cursor(Console *console);

static void command_history_new(Console *console);
static void command_history_delete(Console *console);
static void add_command_history(Console *console, const char *command);
static void previous_command(Console *console);
static void next_command(Console *console);
static void current_command(Console *console);


Console* console_new(void)
{
	Console *console;
	GtkWidget *scroll_window;
	GtkWidget *text_view;
	GtkTextBuffer *text_buffer;

	console = malloc(sizeof(Console));

	if(console == NULL){
		fprintf(stderr, "error: memory allocation error\n");
		fprintf(stderr, "console\n");
		fprintf(stderr, "in console_new()\n");
		exit(-1);
	}

	scroll_window = gtk_scrolled_window_new(NULL, NULL);
	console->scroll_window = scroll_window;

	gtk_scrolled_window_set_policy(
	  GTK_SCROLLED_WINDOW(scroll_window),
	  GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

	gtk_scrolled_window_set_shadow_type(
	  GTK_SCROLLED_WINDOW(scroll_window), GTK_SHADOW_IN);

	text_view = gtk_text_view_new();
	console->text_view = text_view;

	gtk_widget_grab_focus(text_view);
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_CHAR);

	gtk_container_add(GTK_CONTAINER(scroll_window), text_view);

	g_signal_connect(text_view, "key-press-event",
	  G_CALLBACK(key_press), console);

	g_signal_connect(text_view, "button-press-event",
	  G_CALLBACK(button_press), NULL);

	gtk_widget_set_events(text_view, GDK_BUTTON_PRESS_MASK);

	text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
	console->text_buffer = text_buffer;

	console_set_prompt(console, CONSOLE_DEFAULT_PROMPT);
	console_set_font(console, CONSOLE_DEFAULT_FONT);

	command_history_new(console);

	console->start = 0;
	console->callback = NULL;

	return console;
}


void console_delete(Console *console)
{
	gtk_widget_destroy(CONSOLE_WIDGET(console));
	command_history_delete(console);
	free(console);
}


void console_start(Console *console)
{
	if(console->start) return;

	console->start = 1;
	prompt(console);
	update(console);
}


void console_set_prompt(Console *console, const char *prompt)
{
	strncpy(console->prompt, prompt, CONSOLE_PROMPT_SIZE);
}


void console_set_callback(Console *console, Callback callback)
{
	console->callback = callback;
}


void console_set_font(Console *console, const char *font)
{
	PangoFontDescription *desc;

	desc = pango_font_description_from_string(font);

	gtk_widget_modify_font(console->text_view, desc);
}


void console_write(Console *console, const char *str)
{
	gtk_text_buffer_insert_at_cursor(console->text_buffer, str, -1);
	update(console);
}


static int key_printable(int keyval)
{
	switch(keyval){
	case GDK_space:
	case GDK_exclam:
	case GDK_quotedbl:
	case GDK_numbersign:
	case GDK_dollar:
	case GDK_percent:
	case GDK_ampersand:
	case GDK_quoteright:
	case GDK_parenleft:
	case GDK_parenright:
	case GDK_asterisk:
	case GDK_plus:
	case GDK_comma:
	case GDK_minus:
	case GDK_period:
	case GDK_slash:
	case GDK_0:
	case GDK_1:
	case GDK_2:
	case GDK_3:
	case GDK_4:
	case GDK_5:
	case GDK_6:
	case GDK_7:
	case GDK_8:
	case GDK_9:
	case GDK_colon:
	case GDK_semicolon:
	case GDK_less:
	case GDK_equal:
	case GDK_greater:
	case GDK_question:
	case GDK_at:
	case GDK_A:
	case GDK_B:
	case GDK_C:
	case GDK_D:
	case GDK_E:
	case GDK_F:
	case GDK_G:
	case GDK_H:
	case GDK_I:
	case GDK_J:
	case GDK_K:
	case GDK_L:
	case GDK_M:
	case GDK_N:
	case GDK_O:
	case GDK_P:
	case GDK_Q:
	case GDK_R:
	case GDK_S:
	case GDK_T:
	case GDK_U:
	case GDK_V:
	case GDK_W:
	case GDK_X:
	case GDK_Y:
	case GDK_Z:
	case GDK_bracketleft:
	case GDK_backslash:
	case GDK_bracketright:
	case GDK_asciicircum:
	case GDK_underscore:
	case GDK_grave:
	case GDK_a:
	case GDK_b:
	case GDK_c:
	case GDK_d:
	case GDK_e:
	case GDK_f:
	case GDK_g:
	case GDK_h:
	case GDK_i:
	case GDK_j:
	case GDK_k:
	case GDK_l:
	case GDK_m:
	case GDK_n:
	case GDK_o:
	case GDK_p:
	case GDK_q:
	case GDK_r:
	case GDK_s:
	case GDK_t:
	case GDK_u:
	case GDK_v:
	case GDK_w:
	case GDK_x:
	case GDK_y:
	case GDK_z:
	case GDK_braceleft:
	case GDK_bar:
	case GDK_braceright:
	case GDK_asciitilde:
	case GDK_Tab:
	case GDK_Delete:
	case GDK_BackSpace:
		return 1;
		break;
	default:
		break;
	}

	return 0;
}


static int key_arrow(int keyval)
{
	switch(keyval){
	case GDK_Left:
	case GDK_Right:
	case GDK_Up:
	case GDK_Down:
		return 1;
		break;
	default:
		break;
	}

	return 0;
}


static gboolean key_press(GtkWidget *widget, GdkEventKey *event,
  Console *console)
{
	if(!console->start) return TRUE;

	if(!editable(console)){
		if(event->state & GDK_CONTROL_MASK){
			switch(event->keyval){
			case GDK_c:
				return FALSE;
				break;
			case GDK_x:
			case GDK_v:
				return TRUE;
				break;
			case GDK_b:
			case GDK_f:
			case GDK_u:
			case GDK_k:
			case GDK_d:
			case GDK_h:
				return TRUE;
				break;
			default:
				break;
			}
		}

		if(key_printable(event->keyval) || key_arrow(event->keyval)){
			move_cursor_to_command_end(console);
		}
	}

	if(key_printable(event->keyval) || key_arrow(event->keyval)){
		scroll_to_cursor(console);
	}

	if(event->state & GDK_CONTROL_MASK){
		switch(event->keyval){
		case GDK_b:
			move_left(console);
			return TRUE;
			break;
		case GDK_f:
			move_right(console);
			return TRUE;
			break;
		case GDK_p:
			previous_command(console);
			return TRUE;
			break;
		case GDK_n:
			next_command(console);
			return TRUE;
			break;
		case GDK_a:
			move_cursor_to_command_start(console);
			return TRUE;
			break;
		case GDK_e:
			move_cursor_to_command_end(console);
			return TRUE;
			break;
		case GDK_u:
			clear_command_cursor_to_start(console);
			return TRUE;
			break;
		case GDK_k:
			clear_command_cursor_to_end(console);
			return TRUE;
			break;
		case GDK_l:
			clear(console);
			return TRUE;
			break;
		case GDK_d:
			delete(console);
			break;
		case GDK_h:
			backspace(console);
			return TRUE;
			break;
		case GDK_j:
			command_proc(console);
			return TRUE;
			break;
		default:
			break;
		}
	}

	switch(event->keyval){
	case GDK_Left:
		move_left(console);
		return TRUE;
	case GDK_Up:
		previous_command(console);
		return TRUE;
		break;
	case GDK_Down:
		next_command(console);
		return TRUE;
		break;
	case GDK_Delete:
		delete(console);
		return TRUE;
		break;
	case GDK_BackSpace:
		backspace(console);
		return TRUE;
		break;
	case GDK_Return:
		command_proc(console);
		return TRUE;
		break;
	default:
		break;
	}

	return FALSE;
}


static gboolean button_press(GtkWidget *widget, GdkEventButton *event,
  gpointer data)
{
	if(event->button == 3) return TRUE;

	return FALSE;
}


static int editable_iter(Console *console, GtkTextIter *iter)
{
	if(gtk_text_iter_get_line(iter) > console->command_line){
		return 1;
	}

	if(gtk_text_iter_get_line(iter) == console->command_line &&
	   gtk_text_iter_get_line_index(iter) >= console->command_start_index){
		return 1;
	}

	return 0;
}


static int editable(Console *console)
{
	if(gtk_text_buffer_get_has_selection(console->text_buffer)){
		GtkTextIter start, end;

		gtk_text_buffer_get_selection_bounds(
		  console->text_buffer, &start, &end);

		if(editable_iter(console, &start) &&
		   editable_iter(console, &end)) return 1;
	}else{
		GtkTextIter iter;

		get_cursor_iter(console, &iter);

		if(editable_iter(console, &iter)) return 1;
	}

	return 0;
}


static int can_move_left(Console *console)
{
	if(get_cursor_line(console) > console->command_line){
		return 1;
	}

	if(get_cursor_line(console) == console->command_line &&
	   get_cursor_line_index(console) > console->command_start_index){
		return 1;
	}

	return 0;
}


static void move_left(Console *console)
{
	GtkTextIter iter;

	if(!can_move_left(console)) return;

	get_cursor_iter(console, &iter);
	gtk_text_iter_backward_char(&iter);
	gtk_text_buffer_place_cursor(console->text_buffer, &iter);
}


static void move_right(Console *console)
{
	GtkTextIter iter;

	get_cursor_iter(console, &iter);
	gtk_text_iter_forward_char(&iter);
	gtk_text_buffer_place_cursor(console->text_buffer, &iter);
}


static void nextline(Console *console)
{
	console_write(console, "\n");
}


static void prompt(Console *console)
{
	console_write(console, console->prompt);
}


static void update(Console *console)
{
	console->command_line = get_command_line(console);
	console->command_start_index = get_cursor_line_index(console);
	scroll_to_cursor(console);
}


static void delete(Console *console)
{
	if(!editable(console)) return;

	if(gtk_text_buffer_get_has_selection(console->text_buffer)){
		GtkTextIter start, end;

		gtk_text_buffer_get_selection_bounds(
		  console->text_buffer, &start, &end);

		gtk_text_buffer_delete(console->text_buffer, &start, &end);
	}else{
		GtkTextIter iter;

		get_cursor_iter(console, &iter);

		if(gtk_text_iter_is_end(&iter)) return;

		gtk_text_iter_forward_char(&iter);
		gtk_text_buffer_backspace(console->text_buffer,
		  &iter, FALSE, TRUE);
	}
}


static void backspace(Console *console)
{
	GtkTextIter iter;

	if(gtk_text_buffer_get_has_selection(console->text_buffer)){
		delete(console);
	}

	if(!can_move_left(console)) return;

	get_cursor_iter(console, &iter);
	gtk_text_buffer_backspace(console->text_buffer, &iter, FALSE, TRUE);
}


static void clear(Console *console)
{
	GtkTextIter start, end;

	if(console->command_line == 0) return;

	gtk_text_buffer_get_start_iter(console->text_buffer, &start);

	gtk_text_buffer_get_end_iter(console->text_buffer, &end);
	gtk_text_iter_set_line_index(&end, 0);

	gtk_text_buffer_delete(console->text_buffer, &start, &end);

	console->command_line = get_command_line(console);
}


static void clear_command_cursor_to_start(Console *console)
{
	GtkTextIter start, iter;

	get_command_start_iter(console, &start);
	get_cursor_iter(console, &iter);
	gtk_text_buffer_delete(console->text_buffer, &start, &iter);
}


static void clear_command_cursor_to_end(Console *console)
{
	GtkTextIter iter, end;

	get_cursor_iter(console, &iter);
	get_command_end_iter(console, &end);
	gtk_text_buffer_delete(console->text_buffer, &iter, &end);
}


static void clear_command(Console *console)
{
	GtkTextIter start, end;

	get_command_start_iter(console, &start);
	get_command_end_iter(console, &end);
	gtk_text_buffer_delete(console->text_buffer, &start, &end);
}


static char* get_command(Console *console)
{
	GtkTextIter start, end;

	get_command_start_iter(console, &start);
	get_command_end_iter(console, &end);

	return gtk_text_buffer_get_text(
	  console->text_buffer, &start, &end, FALSE);
}


static void command_proc(Console *console)
{
	char *commands;
	int commands_len;
	int num_command;
	char *command;
	int i;

	commands = get_command(console);

	num_command = 1;
	commands_len = strlen(commands);
	
	for(i = 0; i < commands_len; i++){
		if(commands[i] == '\n'){
			commands[i] = '\0';
			num_command++;
		}
	}
	
	command = commands;

	move_cursor_to_command_end(console);
	nextline(console);

	for(i = 0; i < num_command; i++){
		if(console->callback != NULL){
			console->callback(console, command);
		}

		if(strlen(command) != 0){
			add_command_history(console, command);
		}

		for(; *command != '\0'; command++){
			;
		}
		command++;
	}

	prompt(console);
	update(console);
}


static void get_cursor_iter(Console *console, GtkTextIter *iter)
{
	GtkTextMark *mark;

	mark = gtk_text_buffer_get_insert(console->text_buffer);
	gtk_text_buffer_get_iter_at_mark(console->text_buffer, iter, mark);
}


static int get_cursor_line(Console *console)
{
	GtkTextIter iter;

	get_cursor_iter(console, &iter);

	return gtk_text_iter_get_line(&iter);
}


static int get_cursor_line_index(Console *console)
{
	GtkTextIter iter;

	get_cursor_iter(console, &iter);

	return gtk_text_iter_get_line_index(&iter);
}


static void get_command_start_iter(Console *console, GtkTextIter *iter)
{
	gtk_text_buffer_get_iter_at_line_offset(
	  console->text_buffer,
	  iter,
	  console->command_line,
	  console->command_start_index
	);
}


static void get_command_end_iter(Console *console, GtkTextIter *iter)
{
	gtk_text_buffer_get_end_iter(console->text_buffer, iter);
}


static int get_command_line(Console *console)
{
	GtkTextIter iter;

	gtk_text_buffer_get_end_iter(console->text_buffer, &iter);

	return gtk_text_iter_get_line(&iter);
}


static void move_cursor_to_command_start(Console *console)
{
	GtkTextIter start;

	get_command_start_iter(console, &start);
	gtk_text_buffer_place_cursor(console->text_buffer, &start);
}


static void move_cursor_to_command_end(Console *console)
{
	GtkTextIter end;

	get_command_end_iter(console, &end);
	gtk_text_buffer_place_cursor(console->text_buffer, &end);
}


static void scroll_to_cursor(Console *console)
{
	GtkTextMark *mark;

	mark = gtk_text_buffer_get_insert(console->text_buffer);
	gtk_text_view_scroll_mark_onscreen(
	  GTK_TEXT_VIEW(console->text_view), mark);
}


static void command_history_new(Console *console)
{
	char **p;

	p = malloc(sizeof(char *)*CONSOLE_COMMAND_HISTORY_SIZE);

	if(p == NULL){
		fprintf(stderr, "error: memory allocation error\n");
		fprintf(stderr, "p\n");
		fprintf(stderr, "in console_new()\n");
		exit(-1);
	}

	console->command_history = p;

	console->command_history_size = 0;
	console->command_history_max_size = CONSOLE_COMMAND_HISTORY_SIZE;
	console->command_history_index = 0;
}


static void command_history_delete(Console *console)
{
	int i;

	for(i = 0; i < console->command_history_size; i++){
		free(console->command_history[i]);
	}

	console->command_history_size = 0;
	console->command_history_max_size = 0;
	console->command_history_index = 0;

	free(console->command_history);
	console->command_history = NULL;
}


static void add_command_history(Console *console, const char *command)
{
	int i;
	int max_size;
	char *str;

	i = console->command_history_size;
	max_size = console->command_history_max_size;

	if(i + 1 > max_size){
		char **p;

		max_size += CONSOLE_COMMAND_HISTORY_SIZE;
		p = realloc(console->command_history, sizeof(char *)*max_size);

		if(p == NULL){
			fprintf(stderr, "error: memory allocation error\n");
			fprintf(stderr, "p\n");
			fprintf(stderr, "in add_command_history()\n");
			exit(-1);
		}

		console->command_history = p;
		console->command_history_max_size = max_size;
	}


	str = strdup(command);

	if(str == NULL){
		fprintf(stderr, "error: memory allocation error\n");
		fprintf(stderr, "str\n");
		fprintf(stderr, "in add_command_history()\n");
		exit(-1);
	}

	console->command_history[i] = str;

	console->command_history_size++;
	current_command(console);
}


static void previous_command(Console *console)
{
	int i;
	char *str;

	i = console->command_history_index - 1;

	if(i < 0) return;

	str = console->command_history[i];

	clear_command(console);
	gtk_text_buffer_insert_at_cursor(
	  console->text_buffer, str, -1);

	console->command_history_index = i;
}


static void next_command(Console *console)
{
	int i;
	char *str;

	i = console->command_history_index + 1;

	if(i > console->command_history_size - 1){
		clear_command(console);
		current_command(console);
		return;
	}

	str = console->command_history[i];

	clear_command(console);
	gtk_text_buffer_insert_at_cursor(
	  console->text_buffer, str, -1);

	console->command_history_index = i;
}


static void current_command(Console *console)
{
	console->command_history_index = console->command_history_size;
}

