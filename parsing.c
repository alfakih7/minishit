#include "minishell.h"

int main()
{
    char **cmd;
    char *str;

    while(42)
    {
        printf("minishell > \n");
        str = get_next_line(0);
        check_quotes(str);
        cmd = split_with_no_quotes(str, '|');
        printf("%s", cmd[3]);
        // if (ft_strchr(str, '\"'))
        //     return (1);
    }
    return (0);
}