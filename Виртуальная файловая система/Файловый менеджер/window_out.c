/* функция выводит содирживое поля d_name структуры dirent
 * в текущее окно, используется как при запуске программы, так и
 * при переходе из каталога в каталог, и при пролистовании
 * окна в верх или в низ, именно в ней устанавливаются поля структуры test
 * содержащие координаты курсора, после вывода на экран, координаты 
 * устанавливаются в начальное положение и курсор всегда отображается в окне
 * в самом начале
 */
#include <dirent.h>
#include <ncurses.h>
#include "struct.h"

void window_out(struct test * a_wnd){
	int i_dir, wnd_LINES;
	wnd_LINES = LINES - 7;
	a_wnd -> Y_wnd = 1;
    a_wnd -> X_wnd = 1;
    i_dir = a_wnd -> i_dir;
    while(i_dir < a_wnd -> n_dir && wnd_LINES--){
		mvwaddstr(a_wnd -> wnd, a_wnd -> Y_wnd++, a_wnd -> X_wnd, (a_wnd -> deep[i_dir]) -> d_name);
		i_dir++;
	}
	a_wnd -> Y_wnd = 1;
	a_wnd -> X_wnd = 1;
    mvwchgat(a_wnd -> wnd, a_wnd -> Y_wnd, a_wnd -> X_wnd, a_wnd -> h_line, A_BOLD, 3, NULL);
}
