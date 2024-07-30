/* функция инициализирует левое и правое окно файлового менеджера 
 * заполняются поля структуры
 */

#include <ncurses.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <sys/param.h>
#include "struct.h"

extern struct test* l_wnd;
extern struct test* r_wnd;
extern char l_new_path[MAXPATHLEN];
extern char r_new_path[MAXPATHLEN];

void window_ini(){
	char *err;
	int Y_max_scr, X_max_scr, Y_lwnd_size, X_lwnd_size, Y_rwnd_size, X_rwnd_size;
/* вызов функции работы с цветом и установка цветовых пар 
 * отключение курсора, разрешение нажатия функцианальных клавиш 
 */
	start_color();
    init_pair(1,COLOR_WHITE,COLOR_BLUE);
    init_pair(2,COLOR_BLUE,COLOR_WHITE);
	init_pair(3,COLOR_WHITE,COLOR_CYAN);
    curs_set(0);
	keypad(stdscr, TRUE);
	refresh();
    noecho(); /* нужно чтоб TAB вел себя по человечески */
	l_wnd = malloc(sizeof(struct test));	
	r_wnd = malloc(sizeof(struct test));
	if(l_wnd == NULL || r_wnd == NULL){
		err = strerror(errno);
		endwin();
		printf("%s\n", err);
		exit(EXIT_FAILURE);
	}
/* получение максимальных координат для экрана
 * и применение их для создания левого и правого окна
 * LINES - 5: отступ одной линии сверху и четыре линии снизу
 * COLS/2 - делит экран на две равные части 
 */
    getmaxyx(stdscr, Y_max_scr, X_max_scr);
    Y_lwnd_size = 1;
    X_lwnd_size = 0;
    Y_rwnd_size = 1;
    X_rwnd_size = X_max_scr/2;
    l_wnd -> wnd = newwin(LINES - 5, COLS/2, Y_lwnd_size, X_lwnd_size);
    r_wnd -> wnd = newwin(LINES - 5, (COLS/2), Y_rwnd_size, X_rwnd_size);
	if(l_wnd -> wnd == NULL || r_wnd -> wnd == NULL){
		endwin();
		printf("No create window\n");
		exit(EXIT_FAILURE);
	}
/* включение функцианальных клавиш для обоих окон,
 * заливка заднего фона цветовой парой,
 * рисование рамки
 */
    keypad(l_wnd -> wnd, TRUE);
    keypad(r_wnd -> wnd, TRUE);
    wbkgd(r_wnd -> wnd, COLOR_PAIR(1));
    wbkgd(l_wnd -> wnd, COLOR_PAIR(1));
    box(l_wnd -> wnd, 0, 0);
    box(r_wnd -> wnd, 0, 0);

/* библиотечная функция elpath преобразует относительный путь в абсолютный 
 * для левого и правого окна, для каждого окна имеется своя строка для хранения пути
 */
	realpath(l_new_path, l_new_path);
	realpath(r_new_path, r_new_path);
	l_wnd -> path = l_new_path;
	r_wnd -> path = r_new_path;

/* библиотечная функция scandir, при запуске читатет текущий каталог, заполняется структура dirent */

	l_wnd -> n_dir = scandir(l_wnd -> path, &(l_wnd -> deep), NULL, alphasort);
	r_wnd -> n_dir = scandir(r_wnd -> path, &(r_wnd -> deep), NULL, alphasort);
	if(l_wnd -> n_dir == -1 || r_wnd -> n_dir == -1){
		err = strerror(errno);
		delwin(l_wnd -> wnd);
		delwin(r_wnd -> wnd);
		endwin();
		free(l_wnd);
		free(r_wnd);
		printf("%s\n", err);
		exit(EXIT_FAILURE);
	}

/* if i_dir = 0, then print current directory */

	l_wnd -> i_dir = 1; 
	r_wnd -> i_dir = 1; 

/* курсор */

	l_wnd -> h_line = (COLS/2) - 2;
	r_wnd -> h_line = (COLS/2) - 2;
	wrefresh(l_wnd -> wnd);
	wrefresh(r_wnd -> wnd);
  //  keypad(stdscr,TRUE);
}
