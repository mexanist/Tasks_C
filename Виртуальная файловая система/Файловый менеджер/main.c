#include "main.h"
#include "struct.h"

int main(){
	int ch_key, switcher;
	initscr();
	signal(SIGWINCH, sig_winch);
	window_ini();
/* стартовая инициализация обоих окон */
	window_out(r_wnd);
	wchgat(r_wnd -> wnd, r_wnd -> h_line, A_NORMAL, 1, NULL);
	window_out(l_wnd);
	wrefresh(r_wnd -> wnd);                                               
	wrefresh(l_wnd -> wnd);         									
	a_wnd = l_wnd;
	switcher = OFF;
	while((ch_key = wgetch(a_wnd -> wnd)) != KEY_F(4)){
/* переключает курсор между окнами клавишей TAB, a_wnd указывает на активное окно */
		if(ch_key == '\t' && switcher == ON){
			a_wnd = l_wnd;
			wchgat(r_wnd -> wnd, r_wnd -> h_line, A_NORMAL, 1, NULL);
			wnoutrefresh(r_wnd -> wnd);
			mvwchgat(l_wnd -> wnd, l_wnd -> Y_wnd, l_wnd -> X_wnd, l_wnd -> h_line, A_BOLD, 3, NULL); 
			doupdate();
			switcher = OFF;
		} else if(ch_key == '\t' && switcher == OFF){
			a_wnd = r_wnd;
			wchgat(l_wnd -> wnd, l_wnd -> h_line, A_NORMAL, 1, NULL);
			wnoutrefresh(l_wnd -> wnd);
			wnoutrefresh(r_wnd -> wnd);
			mvwchgat(r_wnd -> wnd, r_wnd -> Y_wnd, r_wnd -> X_wnd, r_wnd -> h_line, A_BOLD, 3, NULL);
			doupdate();
			switcher = ON;
		} 
/* перемещение курсора в пределах окна */
		if (ch_key == KEY_UP && a_wnd -> i_dir > 1){
			wchgat(a_wnd -> wnd, a_wnd -> h_line, A_NORMAL, 1, NULL);
			a_wnd -> i_dir--;
/* пролистывание окна вниз, для этого используется поле i_dir структуры test 
 * используется как перемещение по структурам dirent
 */
			if(1 == a_wnd -> Y_wnd){
				wclear(a_wnd -> wnd);
                box(a_wnd -> wnd, 0, 0);
/* устанавливает смещение указателя на структуру dirent
 * смещение происходит в сторону уменьшения, что позваляет заново вывести
 * содержимое пролистанного окна
 */
                a_wnd -> i_dir = (a_wnd -> i_dir) - (LINES - 8);/* 21 */ 
                window_out(a_wnd);
			} else {
				mvwchgat(a_wnd -> wnd, --a_wnd -> Y_wnd, a_wnd -> X_wnd, a_wnd -> h_line, A_BOLD, 3, NULL);
			}
		} 
/* пролистывание окна вверх, так же используется i_dir */
		if (ch_key == KEY_DOWN && a_wnd -> i_dir < a_wnd -> n_dir - 1){
			wchgat(a_wnd -> wnd, a_wnd -> h_line, A_NORMAL, 1, NULL);
			a_wnd -> i_dir++;
/* устанавливает смещение указателя на структуру dirent
 * смещение происходит в сторону увелечения, что позволяет заново выводить ту часть
 * содержимого структуры dirent, которая не уместилась на экране */
            if(a_wnd -> Y_wnd == (LINES - 7)){
            	wclear(a_wnd -> wnd);
				box(a_wnd -> wnd, 0, 0);
				window_out(a_wnd);
			} else {
				mvwchgat(a_wnd -> wnd, ++a_wnd -> Y_wnd, a_wnd -> X_wnd, a_wnd -> h_line, A_BOLD, 3, NULL);
			}
		}
/* при нажатии enter считывается имя d_name, смещение i_dir указывает на выбранное имя,
 * если выбранное имя является каталога, то вызывается функция path_build освобождается
 * память от предыдущей структуры dirent и вызывается функция scandir заполняя соответствующие 
 * поля структуры test, далее вывод на экран с помощью wundow_out
 * в цикле условие игнорирует имя если оно является именем файла, а не каталога 
 */
		if (ch_key == KEY_ENTR && ((a_wnd -> deep[a_wnd -> i_dir] -> d_type) == D_DIR)){
			path_build(a_wnd -> path, (a_wnd -> deep[a_wnd -> i_dir]) -> d_name);
			while(a_wnd -> n_dir--){
				free(a_wnd -> deep[a_wnd -> n_dir]);
			}
			free(a_wnd -> deep);
            wclear(a_wnd -> wnd);
			box(a_wnd -> wnd, 0, 0);
			a_wnd -> i_dir = 1;
			a_wnd -> n_dir = scandir(a_wnd -> path, &(a_wnd -> deep), NULL, alphasort);
			if(a_wnd -> n_dir == -1){
        		err = strerror(errno);
        		delwin(l_wnd -> wnd);
        		delwin(r_wnd -> wnd);
        		endwin();
        		free(l_wnd);
        		free(r_wnd);
        		printf("%s\n", err);
        		exit(EXIT_FAILURE);
    		}
            window_out(a_wnd);
         }
	}
	free_mem();
}
