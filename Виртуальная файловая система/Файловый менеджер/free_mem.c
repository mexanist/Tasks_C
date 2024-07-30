/* функция освобождает память, сначала высвобождается память,
 * занимаемая структурой dirent, затем высвобаждается память,
 * занимаемая окнами, затем закрывается экран и высвобождается память,
 * занимаемая структурой test */

#include <ncurses.h>
#include <stdlib.h>
#include "struct.h"

extern struct test* l_wnd;
extern struct test* r_wnd;

void free_mem(){
	while(l_wnd -> n_dir--){
		free(l_wnd -> deep[l_wnd -> n_dir]);
    }
    free(l_wnd -> deep);
	while(r_wnd -> n_dir--){
        free(r_wnd -> deep[r_wnd -> n_dir]);
    }
    free(r_wnd -> deep);
	delwin(l_wnd -> wnd);
	delwin(r_wnd -> wnd);
	endwin();
	free(l_wnd);
	free(r_wnd);
}


