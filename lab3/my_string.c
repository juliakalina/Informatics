#pragma once
size_t my_strlen(const char *str)
{
        const char *s;

        for (s = str; *s; ++s);
        return (s - str);
}
void my_memcpy(void *dest, void *src, size_t n) 
{ 
   char *csrc = (char *)src; 
   char *cdest = (char *)dest; 

   for (int i=0; i<n; i++) 
       cdest[i] = csrc[i]; 
} 
void * my_memmove(void* dest, const void* src, int n)
{
    char *pDest = (char *)dest;
    const char *pSrc =( const char*)src;
    char *tmp  = (char *)malloc(sizeof(char ) * n);
    if(NULL == tmp)
    {
        return NULL;
    }
    else
    {
        int i = 0;
        for(i =0; i < n ; ++i)
        {
            *(tmp + i) = *(pSrc + i);
        }
        for(i =0 ; i < n ; ++i)
        {
            *(pDest + i) = *(tmp + i);
        }
        free(tmp);
    }
    return dest;
}
char* my_strcpy(char* destination, const char* source)
{
    if (destination == NULL)
        return NULL;
 
    char *ptr = destination;
 
    while (*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }
 
    *destination = '\0';
 
    return ptr;
}
char* my_strchr(const char *s, int c)
{
    while (*s != (char)c)
        if (!*s++)
            return 0;
    return (char *)s;
}
int my_strcmp(const char string1[], const char string2[] )
{
    int i = 0;
    int flag = 0;    
    while (flag == 0)
    {
        if (string1[i] > string2[i])
        {
            flag = 1;
        }
        else if (string1[i] < string2[i])
        {
            flag = -1;
        }

        if (string1[i] == '\0')
        {
            break;
        }

        i++;
    }
    return flag;
}
char* my_strcat(char *dest, const char *src)
{
    char *rdest = dest;

    while (*dest)
      dest++;
    while (*dest++ = *src++);
    return rdest;
}
