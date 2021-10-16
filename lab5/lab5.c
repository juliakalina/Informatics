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
    while (ptr != NULL && ptr->c != ';' && ptr->c!='.') {
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
            if (ptr == NULL||ptr->next==NULL)
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
    int a;
    while (a = Check(p, p->c)) {
        Item* ptr = p;
        Delete_Char(p, p->c);
        p = p->next;
        free(ptr);
    }
    Item* ptr = p;
    while (ptr->next != NULL && ptr->c != ';' && ptr->c != '.') {
        int a = Check(ptr, ptr->next->c);
        if (a == 1)
            Delete_Char(ptr, ptr->next->c);
        else
            ptr = ptr->next;
    }
    return p;
}
int main()
{
    setlocale(LC_ALL, "rus");
    struct timespec  stop, start;
    Item* ptr = NULL;
    while (puts("Введите строку"), getList(&ptr)) {
        correct(&ptr);
        putList("Введено", ptr);
        clock_t begin = clock();
        ptr = newString(ptr);
        correct(&ptr);
        clock_t end = clock();
        putList("Результирующая строка", ptr);
        printf("Время программы: %Lf seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
        ptr = deleteList(ptr);
    }
    return 0;
}
