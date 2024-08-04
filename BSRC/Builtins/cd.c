#include "../minishell.h"

#define MAX_ENV_VARS 100
#define MAX_INPUT 1024

static char *ft_strjoin3(const char *s1 , const char *s2 , const char *s3)
{
    size_t len1;
    size_t len2;
    size_t len3;
    char *result;

    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    len3 = ft_strlen(s3);

    if(!s1 || !s2 || !s3)
        return NULL;
    result = (char *)malloc(len1 + len2 + len3 + 1);

    if(!result)
        return NULL;
    ft_strcpy(result , s1);
    ft_strcat(result , s2);
    ft_strcat(result , s3);

    return result;
}


//func to retriev the value of env by its name
char *get_env_var(char **env, const char *name)
{
    int i = 0;
    size_t len = ft_strlen(name);

    while (env[i])
    {
        if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
        {
            return &env[i][len + 1];
        }
        i++;
    }
    return NULL;
}

//this set the value of the env , if its already exist it update it , if no it adds a new var
void set_env_var(char **env, const char *name, const char *value)
{
    int i = 0;
    size_t len = ft_strlen(name);
    char *new_var;

    while (env[i])
    {
        if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
        {
            // Variable exists, update it
            free(env[i]);
            env[i] = ft_strjoin3(name, "=", value);
            return;
        }
        i++;
    }

    // Variable doesn't exist, add it
    new_var = ft_strjoin3(name, "=", value);
    env[i] = new_var;
    env[i + 1] = NULL;
}
//the cd implemantation including  updating env pwd and oldpwd
void cd_command(char **env, char *path)
{
    char *home_dir;
    char current_dir[1024];
    char *old_pwd;

    if (path == NULL || ft_strncmp(path, "~") == 0)
    {
        home_dir = get_env_var(env, "HOME");
        if (home_dir == NULL)
        {
            perror("cd: HOME not set\n");
            return;
        }
        path = home_dir;
    }
    else if (ft_strcmp(path, "-") == 0)
    {
        old_pwd = get_env_var(env, "OLDPWD");
        if (old_pwd == NULL)
        {
            perror("cd: OLDPWD not set\n");
            return;
        }
        path = old_pwd;
        printf("%s\n", path);  // Print the directory when using cd -
    }
    // Get the current directory before changing
    if (getcwd(current_dir, sizeof(current_dir)) == NULL)
    {
        perror("error in getcwd");
        return;
    }

    // Change directory
    if (chdir(path) != 0)
    {
        perror("cd");
        return;
    }

    // Update PWD and OLDPWD environment variables
    set_env_var(env, "OLDPWD", current_dir);

    if (getcwd(current_dir, sizeof(current_dir)) != NULL)
    {
        set_env_var(env, "PWD", current_dir);
    }
    else
    {
        perror("error in getcwd");
    }
}