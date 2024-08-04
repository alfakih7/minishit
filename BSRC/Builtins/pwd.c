#include "../minishell.h"

void pwd_command(char **env)
{
    char *pwd = get_env_var(env, "PWD");
    char cwd[1024];
    
    if (pwd != NULL)
    {
        printf("%s\n", pwd);
    }
    else
    {
        
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            printf("%s\n", cwd);
            // Update PWD if it's not set
            set_env_var(env, "PWD", cwd);
        }
        else
        {
            perror("error in pwd");
        }
    }
}