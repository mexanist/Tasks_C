#define N 10


typedef struct abonent{
    char name[N];
    char last_name[N];
    char phone[N];
} DIR;


void add();
void del(const char *);
void search(const char *);
void print();
void exit_programm();
