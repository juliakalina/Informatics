//1.38 Дано целое число n.Найти в записи числа наибольшее количество подряд стоящих одинаковых цифр.
#include <stdio.h>
#include <math.h>
int main(){
int n;
        while (printf("Введите число: "),scanf("%d", &n))

        {
                int i=1,a,b,max=1,p;
                while (n>0)
                {
                a=n%10;
                b=n%100/10;
                        if (a==b)// сравнение двух последних цифр числа
                        {
                        i++; //подсчет количества одинаковых цифр числа
                        }
                                else
                                {
                                i=1; // возвращение счета в исходное состояние, если нет одинаковых цифр
                                }
                        if (i>max)
                        {
                        max=i; // присваивание найденного количества к max
                        p=10;
                        }
                        if (max==i)
                        {
                        p=(p*10)+a; // создание числа из повторяющихся цифр
                        }
                n=n/10;
                }
                if (max==1)
                {
                printf("Повторяющихся цифр нет\n");
                }
                        else
                        {
                        printf ("max=%d\n",max);
                        while(p>10)
                        {
                        printf("%d\n", p%10);
                        p=p/10;
                        }
                        }
        }
return 0;
}