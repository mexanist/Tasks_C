#define KEY_ENTR 10 /* клавиша enter */
#define D_DIR 4     /* тип файла содержится в структуре dirent в поле d_type 4 - каталог */

/* признак включения левого или правого окна */
#define ON 1        
#define OFF 0       

#include <ncurses.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <limits.h>
#include <sys/param.h>
#include <stdio.h>
#include <string.h>

/* l_wnd: left_window 
 * r_wnd: right_window
 * a_wnd: actual_window
 * l_new_path: left_new_path
 * r_new_path: right_new_path
 * MAXPATHLEN = 4096
 * MAXPATHLEN максимальная длина строки содержащая путь к файлу
 * константа определна в <sys/param.h> <limits.h >
 */
struct test* l_wnd;
struct test* r_wnd;
struct test* a_wnd;
char l_new_path[MAXPATHLEN] = {'.'};
char r_new_path[MAXPATHLEN] = {'.'};
char * err;

void sig_winch(int);
void window_out(struct test*);
void path_build(char *, char *);
void free_mem(void);
void window_ini(void);
