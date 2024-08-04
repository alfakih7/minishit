#include "../minishell.h"

char *ft_strcpy(char *dest , char *src){
    int i;
    i = 0;
    while(src[i]){
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

char *ft_strcat(char *dest , const char *src)
{
    char *ptr = dest;
    while(*ptr != '\0')
    {
        ptr++;
    }
    while(*src != '\0'){
        *ptr = *src;
        ptr++;
        src++;
    }
    *ptr = '\0';

    return dest;
}