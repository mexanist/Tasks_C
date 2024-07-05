#define N 10
#define M 100

typedef struct abonent{
    char name[N + 1];
    char second_name[N + 1];
    char tel[N + 1];
} DIR;

void add(DIR *, int *);
void del(DIR *, char *, int);
void search(DIR *, char *, int);
void print(DIR *, int);
