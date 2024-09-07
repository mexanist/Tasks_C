/* Функция потока, поток принимает указатель на окно в котором будет
 * выводиться сообщения всех участников чата */
#define TRUE 1
#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include <mqueue.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>

extern mqd_t que_chat;
/* Ночевидное использование ncurses в потоках */
int work_out(WINDOW *win, void *arg) {
	char *str = (char *) arg;
	wprintw(win, "%s", str);
	wrefresh(win);
}
 
void *thread_out(void* arg) {
	WINDOW *frame_out = (WINDOW *) arg;
	mqd_t chat_rd;
	ssize_t num_read;
	char buf[1024];
	while (TRUE) {
		num_read = mq_receive(que_chat, buf, 1024, NULL);
		buf[num_read] = '\0';
/* Вызываем функцию библиотеки ncurses которая выводит сообзение на экран */
		use_window(frame_out, work_out, buf);
	}
}

