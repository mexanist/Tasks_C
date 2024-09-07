/* Функция создает и инициализирует экран ncurses, 
 * принимает адреса указателей окон и создает окна чата
 * frame_in - окно ввода сообщений
 * frame_out - окно вывода сообщений
 * frame_srvs - окно вывода имен пользователей (служебных сообщений) */
#include "window.h"

void window_ini(WINDOW **frame_in, WINDOW **frame_out, WINDOW **frame_srvs){
	initscr();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	curs_set(1);
	nocbreak();
	addstr("For exit type STOP");
	refresh();
	int Y_max_scr, X_max_scr;
	getmaxyx(stdscr, Y_max_scr, X_max_scr);
	*frame_in = newwin(7, COLS - 2, Y_max_scr - 8 , 1);
	if (frame_in == NULL){
		puts("frame_in create failure in window_ini");
		endwin();
		exit(EXIT_FAILURE);
	}
	*frame_out = newwin(LINES - 10, COLS/2 + 28, 1, 1);
	if (frame_out == NULL){
		puts("frame_out create failure in winwow_ini");
		delwin(*frame_in);
		endwin();
		exit(EXIT_FAILURE);
	}
	*frame_srvs = newwin(LINES - 10, COLS/2 - 31, 1, X_max_scr/2 + 30);
	if (frame_srvs == NULL){
		puts("frame_srvs create failure in window_ini");
		delwin(*frame_in);
		delwin(*frame_out);
		endwin();
		exit(EXIT_FAILURE);
	}
	keypad(*frame_in, TRUE);
	wbkgd(*frame_out, COLOR_PAIR(1));
	wbkgd(*frame_in, COLOR_PAIR(1));
	wbkgd(*frame_srvs, COLOR_PAIR(1));
	wrefresh(*frame_in);
	wrefresh(*frame_out);
	wrefresh(*frame_srvs);
}
