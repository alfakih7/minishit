#include "minishell.h"

int main(){
    char *str;
    while(42)
    {
        printf("minishell > \n");
        str = get_next_line(0);
        check_quotes(str);
        // if (ft_strchr(str, '\"'))
        //     return (1);
    }
    return (0);
}