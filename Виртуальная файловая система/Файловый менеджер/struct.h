/* структура окна менеджера */
struct test{
        WINDOW *wnd; /* указатель на окно */
        int Y_wnd;   /* позиция курсора в окне по координате Y */
        int X_wnd;   /* позиция курсора в окне по координате X */
	int h_line;  /* длина курсора */
        int n_dir;   /* количество файлов и каталогов в директории */ 
        int i_dir;   /* номер структуры dirent */   
        struct dirent **deep;
        char *path;  /* хранится путь до текущего каталога */
    };

