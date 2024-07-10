#include "../minishell.h"

void ft_exit(int status) {
    if (status > 255)
        status = status - 256;
    exit(status);
}
