/* 5.22 Для каждой строки, состоящей из подстрок, разделенных точкой с
запятой, сформировать новую строку путем удаления из исходной строки всех
символов, которые встречаются в каждой из введенных подстрок*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include <locale.h>

typedef struct Item {
    char c;
    struct Item* next;
} Item;

int getList(Item**); //ввод строки
void putList(const char*, Item*); //вывод строки
Item* deleteList(Item*); //освобождаем память
int getList(Item** pptr)
{
    char buf[21], * str;
    Item head = { '*', NULL };
    Item* last = &head;
    int n, rc = 1;
    do {
        n = scanf("%20[^\n]", buf);
        if (n < 0) {
            deleteList(head.next);
            head.next = NULL;
            rc = 0;
            continue;
        }
        if (n > 0) {
            for (str = buf; *str != '\0'; ++str) {
                last->next = (Item*)malloc(sizeof(Item));
                last = last->next;
                last->c = *str;
            }
            last->next = NULL;
        }
        else
            scanf("%*c");
    } while (n > 0);
    *pptr = head.next;
    return rc;
}
void putList(const char* msg, Item* ptr)
{
    printf("%s: \"", msg);
    for (; ptr != NULL; ptr = ptr->next)
        printf("%c", ptr->c);
    printf("\"\n");
}

Item* deleteList(Item* ptr)
{
    Item* tmp = NULL;
    while (ptr != NULL) {
        tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
    return ptr;
}
int Check(Item* p, char k) {
    Item* ptr = p;
    while (ptr != NULL && ptr->c != ';' && ptr->c != '.') {
        ptr = ptr->next;
    }
    if (ptr == NULL)
        return 0;
    ptr = ptr->next;
    while (ptr != NULL) {
        if (ptr->c == ';' || ptr->c == '.')
            return 0;
        if (ptr->c == k) {
            while (ptr != NULL && ptr->c != ';' && ptr->c != '.') {
                ptr = ptr->next;
            }
            if (ptr == NULL || ptr->next == NULL)
                return 1;
        }
        ptr = ptr->next;
    }
    return 0;
}
void Delete_Char(Item* p, char k) {
    Item* ptr = p;
    while (ptr->next != NULL)
    {
        if (ptr->next->c == k)
        {
            Item* del = ptr->next;
            ptr->next = ptr->next->next;
            free(del);
        }
        else
            ptr = ptr->next;
    }
}

void correct(Item** p) {
    while ((*p) != NULL && ((*p)->c == '\t' || (*p)->c == ' '))
    {
        Item* ptr = *p;
        *p = ptr->next;
        free(ptr);
    }
    Item* ptr = *p;
    while (ptr != NULL)
    {
        if (ptr->c == '\t')
            ptr->c = ' ';
        if (ptr->c == ' ') {
            while (ptr->next != NULL && (ptr->next->c == ' ' || ptr->next->c == '\t')) {
                Item* a = ptr->next;
                ptr->next = a->next;
                free(a);
            }
        }
        ptr = ptr->next;
    }
}

Item* newString(Item* p)
{
    Item* ptr = p;
    int a;
    while (a = Check(p, p->c)) {
        Delete_Char(p, p->c);
        p = p->next;
        free(ptr);
        ptr = p;
    }
    while (ptr->next != NULL && ptr->c != ';' && ptr->c != '.') {
        int a = Check(ptr, ptr->next->c);
        if (a == 1)
            Delete_Char(ptr, ptr->next->c);
        else
            ptr = ptr->next;
    }
    return p;
}

Item* create_list(int len, int small_len) {
    int hp = 1;
    char sym = rand() % 26 + 97;
    Item* a = malloc(sizeof(Item));
    a->c = sym;
    a->next = NULL;
    Item* ptr = a;
    for (int i = 1; i < len; i++) {
        if (i == hp * small_len) {
            hp++;
            ptr->next = malloc(sizeof(Item));
            ptr->next->next = NULL;
            ptr->next->c = ';';
            ptr = ptr->next;
        }
        else {
            char sym = rand() % 26 + 97;
            ptr->next = malloc(sizeof(Item));
            ptr->next->next = NULL;
            ptr->next->c = sym;
            ptr = ptr->next;
        }
    }
    hp++;
    ptr->next = malloc(sizeof(Item));
    ptr->next->next = NULL;
    ptr->next->c = ';';
    ptr = ptr->next;
    return a;
}
int main()
{
    setlocale(LC_ALL, "rus");
    int len, times, flag = 0;
    clock_t all = 0;
    Item* ptr = NULL;
    printf("Введите длину строки: ");
    scanf_s("%d", &len);
    printf("Введите количество строк: ");
    scanf_s("%d", &times);
    printf("Введите максимальное количество символов подстроки: ");
    scanf_s("%d", &flag);
    for (int i = 0; i < times; i++)
    {
        Item* new_ptr = create_list(len, flag);
        correct(&new_ptr);
        putList("Введено", new_ptr);
        clock_t begin = clock();
        new_ptr = newString(new_ptr);
        clock_t end = clock();
        all += end - begin;
        putList("Результирующая строка", new_ptr);
        new_ptr = deleteList(new_ptr);
    }
    printf("Время обработки: %Lf seconds\n", (double)(all) / CLOCKS_PER_SEC);

    return 0;
}
