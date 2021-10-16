/* 4.9 Найти строки, которые заканчиваютсяна трёхбуквенное слово, написанное кириллицей*/

#include <locale.h>
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h> 
#include <ctype.h>
#include <windows.h>
#include <string.h>
#include <time.h>

wchar_t** selectionSort(wchar_t** arr, int size) {  //сортировка выбором
    wchar_t** answer = (wchar_t**)calloc(size, sizeof(wchar_t*));
    for (int i = 0; i < size; i++)
        {
            answer[i] = (wchar_t*)calloc(80, sizeof(wchar_t));
            wcscpy(answer[i], arr[i]);
        }
    for (int i = 0; i < size - 1; i++) 
    {
         // устанавливаем начальное значение минимального индекса 
        int min_i = i;
        // находим индекс минимального элемента 
        for (int j = i + 1; j < size; j++) 
        {
            if (wcscmp(answer[j] , answer[min_i]) < 0)
            {
                min_i = j;
            }
        }
        // меняем значения местами 
        wchar_t* temp = (wchar_t*)calloc(80, sizeof(wchar_t));
        wcscpy(temp, answer[i]);
        wcscpy(answer[i], answer[min_i]);
        wcscpy(answer[min_i], temp);
        free(temp);
    }
    return answer;
}

wchar_t** bubbleSort(wchar_t** arr, int size){
    wchar_t** answer = (wchar_t**)calloc(size, sizeof(wchar_t*));
    for (int i = 0; i < size; i++)
        {
            answer[i] = (wchar_t*)calloc(80, sizeof(wchar_t));
            wcscpy(answer[i], arr[i]);
        }
    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++)
        {
            if (wcscmp(answer[i] , answer[j]) < 0) {
                wchar_t* temp = (wchar_t*)calloc(80, sizeof(wchar_t));
                wcscpy(temp, answer[i]);
                wcscpy(answer[i], answer[j]);
                wcscpy(answer[j], temp);
                free(temp);
            }
        }
    }
    return answer;
}

const char *MSGS[] = {"0.end","1.read", "2.readfile",  "3.sort", "4.task" ,"5.write in file" ,"6.sort cmp" ,"7.print", "8.free"};
const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);

int dialog(const char *msgs[], int n) {
    char *error;
    strcpy(error, "");
    int choice;
    do {
    puts(error);
    strcpy(error, "You're wrong. Try again!");
    for (int i = 0; i < n; ++i) {
        puts(msgs[i]);
    }
    puts("Make your choice: ");
    choice = getchar() - '0';
    while (getchar() != '\n') {}
        } while (choice < 0 || choice >= n);
    return choice;
}

int main() {
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    wchar_t** data;
    int size_ = 0;
    FILE* pFile;
    wchar_t* findThisWord;
    int c = 0;
    do {
    c = dialog(MSGS, MSGS_SIZE);
    switch(c) {
    case 0:
        break;
    case 1:
        wprintf(L"Кол-во строк:");
           scanf("%d", &size_);
           getchar();
           data = (wchar_t**)calloc(size_, sizeof(wchar_t*));
           for (int i = 0; i < size_; i++)
           { 
               wprintf(L"%d: ", i);
               data[i] = (wchar_t*)calloc(80, sizeof(wchar_t));
               fgetws(data[i], 80, stdin);
           }
        break;
    case 2:
        pFile = fopen("file.txt","r");

        size_++;
        char ch;
        while ((ch = fgetc(pFile)) != EOF)
            {
            if (ch == '\n')
            size_++;
            }
        fclose(pFile);

        data = (wchar_t**)calloc(size_, sizeof(wchar_t*));

        pFile = _wfopen(L"file.txt" , L"r");
        
        if (pFile != NULL)
        {
            
            int j = 0;
            data[0] = (wchar_t*)calloc(80, sizeof(wchar_t));
            while(fgetws(data[j], 80, pFile) != NULL) {
                j++;
                data[j] = (wchar_t*)calloc(80, sizeof(wchar_t));
            }
            fclose (pFile);
        }
        break;
    case 3:
        if (size_ != 0)
            {
                wchar_t** ans = bubbleSort(data, size_);
                for (int i = 0; i < size_; i++)
                {
                    wprintf(L"%ls \n", ans[i]);
                }
            }
        
        break;
    case 4:
        wprintf(L"Введите трёхбуквенное  слово,  написанное кириллицей:");
        findThisWord = (wchar_t*)calloc(3, sizeof(wchar_t));
        wscanf(L"%ls", findThisWord);
        getchar();
        for (int i = 0; i < size_; i++)
        {
            wchar_t* buf = (wchar_t*)calloc(3, sizeof(wchar_t));
            for (int j = wcslen(data[i]) - 4; j < wcslen(data[i])-1; j++)
            {
                buf[j - wcslen(data[i] + 4)] = data[i][j];
            }
            if (wcscmp(buf, findThisWord) == 0)
            {
                wprintf(L"%ls ", data[i]);
            }
            free(buf);
        }
        break;
    case 5:
        pFile = _wfopen(L"file.txt" , L"w");
        if (pFile)
        {
            for (int i = 0; i < size_; i++)
            {
                fwprintf(pFile,data[i]);
                fwprintf(pFile,L"\n");
            }
        }
        
        fclose(pFile);
        break;
    case 6:
        if (size_ != 0)
        {
            auto start = clock(); // начало времени
            auto ans = selectionSort(data, size_);
            auto end = clock(); // время, когда сортировка закончена
            printf("time for selectionSort: %f\n", (double)(end-start)); // end - start - это время сортировки
            start = clock();
            ans = bubbleSort(data, size_);
            end = clock();
            printf("time for bubbleSort: %f\n", (double)(end-start));
        }
    
        
        break;
    case 7:
        if (size_ != 0)
            {
                for (int i = 0; i < size_; i++)
                {
                    wprintf(L"%ls \n", data[i]);
                }
            }
        break;
    case 8:
        for (int i = 0; i < size_; i++)
        {
            free(data[i]);
        }
        free(data);
        size_ = 0;
        break;
    }
    } while (c != 0);
    return 0;
}
