//в приведенном ниже коде изменить только одну строку (с коментарием) чтобы напечатать "Результат: 12.0"

#include <stdio.h>

int main(){
    float x = 5.0;
    printf("x = %f, ", x);
    float y =6.0;
    printf("y = %f\n", y);
    float *xp = (&x) + 1;		//замена float *xp = &x; на float *xp = (&x) + 1;
    float *yp = &y;
    printf("Результат: %f\n", *xp + *yp);
}
