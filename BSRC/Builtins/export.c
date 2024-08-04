#include "../minishell.h"


int ft_strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

// Environment manipulation functions
void print_env(char **env) {
    int i = 0;
    char *equal_position;

    while (env[i]) {
        equal_position = ft_strchr(env[i], '=');
        if (equal_position && *(equal_position + 1)) {  // Only print if there's a value after '='
            printf("%s\n", env[i]);
        }
        i++;
    }
}

void print_export(char **env) {
    int i = 0;
    char *equal_position;

    while (env[i]) {
        equal_position = ft_strchr(env[i], '=');
        if (equal_position) {
            printf("declare -x ");
            printf("%.*s", (int)(equal_position - env[i] + 1), env[i]);
            printf("\"%s\"\n", equal_position + 1);
        } else {
            printf("declare -x %s\n", env[i]);
        }
        i++;
    }
}

void sort_env(char **env) {
    int i = 0;
    int j;
    char *temp;

    while (env[i] != NULL) {
        j = i + 1;
        while (env[j] != NULL) {
            if (ft_strcmp(env[i], env[j]) > 0) {
                temp = env[i];
                env[i] = env[j];
                env[j] = temp;
            }
            j++;
        }
        i++;
    }
}


void export(char **env, const char *str) {
    int i = 0;
    int name_length = 0;
    char *equal_position;
    char *existing_equal_position;
    int existing_name_length;
    char *new_entry;

    equal_position = ft_strchr(str, '=');
    if (equal_position) {
        name_length = equal_position - str;
    } else {
        name_length = ft_strlen(str);
    }

    while (env[i] != NULL) {
        existing_equal_position = ft_strchr(env[i], '=');
        if (existing_equal_position) {
            existing_name_length = existing_equal_position - env[i];
        } else {
            existing_name_length = ft_strlen(env[i]);
        }

        if (ft_strncmp(env[i], str, name_length) == 0 && (existing_name_length == name_length)) {
            free(env[i]);  // Free the old entry
            env[i] = ft_strdup(str);
            sort_env(env);
            print_export(env);
            return;
        }
        i++;
    }

    if (i >= 100) {
        perror("Error: environment variable limit reached\n");
        return;
    }

    new_entry = ft_strdup(str);
    int j = i;
    while (j > 0 && ft_strcmp(env[j - 1], new_entry) > 0) {
        env[j] = env[j - 1];
        j--;
    }
    env[j] = new_entry;
    env[i + 1] = NULL;
    print_export(env);
}

void unset(char **env, const char *var) {
    int i = 0;
    int var_len = ft_strlen(var);

    while (env[i] != NULL) {
        if (ft_strncmp(env[i], var, var_len) == 0 && (env[i][var_len] == '=' || env[i][var_len] == '\0')) {
            // Found the variable to unset
            free(env[i]);
            // Shift all subsequent elements down
            while (env[i + 1] != NULL) {
                env[i] = env[i + 1];
                i++;
            }
            env[i] = NULL;
            return;
        }
        i++;
    }
}

// Main interface function
void env_builtin(char **env, char **args) {
    int i;

    if (ft_strcmp(args[0]) == "env") {
        print_env(env);
    } else if (ft_strcmp(args[0], "export") == 0) {
        if (args[1] == NULL) {
            sort_env(env);
            print_export(env);
        } else {
            i = 1;
            while (args[i] != NULL) {
                export(env, args[i]);
                i++;
            }
        }
    } else if (ft_strcmp(args[0], "unset") == 0) {
        if (args[1] == NULL) {
            perror("unset: not enough arguments\n");
        } else {
            i = 1;
            while (args[i] != NULL) {
                unset(env, args[i]);
                i++;
            }
        }
    } else {
        perror("Unknown command: %s\n");
    }
}

char **create_env_copy(char **env)
{
    int count = 0;
    char **new_env;
    int i;

    // Count the number of environment variables
    while (env && env[count])
        count++;

    // Allocate memory for the new environment
    new_env = malloc((count + 1) * sizeof(char *));
    if (new_env == NULL)
        return NULL;

    // Initialize loop variable
    i = 0;

    // Copy each environment variable using a while loop
    while (i < count)
    {
        new_env[i] = ft_strdup(env[i]);
        if (new_env[i] == NULL)
        {
            // If strdup fails, free all previously allocated memory
            while (i > 0)
                free(new_env[--i]);
            free(new_env);
            return NULL;
        }
        i++;
    }

    // Null-terminate the array
    new_env[count] = NULL;

    return new_env;
}
