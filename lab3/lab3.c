// 3.38 В строке слова, в каждом из которых от 2 до 6 латинских букв.
//Определить “соседей” в строке 
//Вывести всех “соседей” и исходную последовательность слов.
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
 
char* get_str() { 
 char buf[81] = {0}; 
 char* res = NULL; 
 int len = 0; 
 int n = 0; 
 do { 
    n = scanf("%80[^\n]", buf); 
    if (n < 0) {
    if (!res) { 
        return NULL; 
    } 
    } else if (n > 0) { 
        int chunk_len = strlen(buf); 
        int str_len = len + chunk_len; 
        res = (char*)realloc(res, str_len + 1); 
        memcpy(res + len, buf, chunk_len); 
        len = str_len; 
    } else { 
        scanf("%*c"); 
 }
 } while (n > 0); 
 
 if (len > 0) { 
 res[len] = '\0'; 
 } else { 
 res = (char*)calloc(1, sizeof(char)); 
 } 
 
 return res; 
}

void removeSpace(char* arr, int n)// удаление пробелов
{

    int space = 0;// флаг 1 указывает на пробел
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        while (k == 0 && i < n && arr[i] == ' ') {
            i++;
        }
 
    
        if (arr[i] == ' ')
        {
            if (!space)
            {
                arr[k++] = arr[i];
                space = 1;
            }
        }
        else {
            arr[k++] = arr[i];
            space = 0;
        }
    }
 
    arr[k] = '\0';
}
void removeTabs(char* arr, int n)// замена табов на пробел
{
    for (size_t i = 0; i < n; i++)
    {
       if (arr[i] == '\t')
       {
           arr[i] = ' ';
       }
       
    }
}
int str_cut(char *str, int begin, int len)// выбор соседнего слова и вырезание его из строки
{
    int l = strlen(str);

    if (len < 0) len = l - begin;
    if (begin + len > l) len = l - begin;
    memmove(str + begin, str + begin + len, l - len + 1);
    return len;
}

void get_first_word(char* str, char* next_word){
    int i = 0;
     while (str[i] != ' ')
        {
            next_word[i] = str[i];
            i++;
        }
}

void get_right_word(char* str, char* next_word){
    int i = 0;
     while (str[i] != ' ')
        {
            i++;
        }
        i++;
    int j = i;
    while (i < strlen(str) && str[i] != ' ')
    {
        next_word[i-j] = str[i];
        i++;
    }

}
void delete_firt_word(char* string_copy){
    int i = 0;
    while (string_copy[i] != ' ')
    {
        i++;
    }
    str_cut(string_copy, 0, i+1);
}
char* get_neighbors(char* str){ // нахождение слов-соседей
    char* string_copy = (char*)calloc(strlen(str), sizeof(char));
    strcpy(string_copy, str);
    char* left_word = (char*)calloc(6, sizeof(char));
    char* right_word = (char*)calloc(6, sizeof(char));
    char* answer = (char*)calloc(strlen(str), sizeof(char));
    while (strchr(string_copy, ' ') != NULL)
    {
        get_first_word(string_copy, left_word);
        delete_firt_word(string_copy);
        if (strchr(string_copy, ' ') != NULL)
        {
            get_right_word(string_copy, right_word);
        }
        else{
            break;
        }
        if (strcmp(right_word, left_word) == 0)
        {
           strcat(answer, left_word);
            strcat(answer, " ");
        }
        
    }
    free(right_word);
    free(left_word);
    free(string_copy);
    return answer;
}

int main() {
    char* s = NULL;
    do {
        clock_t begin = clock();
        printf("Введите строку:\n");
        s = get_str();
        removeTabs(s,strlen(s));
        removeSpace(s, strlen(s));
        char* answer;
        answer = get_neighbors(s);
        if (strcmp(answer, "") == 0)
        {
            printf("Нет соседей\n");
        }else
        {
            printf("Соседи: %s\n", answer);
        }
        printf("Строка без лишних пробелов: %s\n", s);
        free(answer);
        free(s);
        clock_t end = clock();
        printf("Время выполнения программы: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
    } while (s);
    return 0; 
}
