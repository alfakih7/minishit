#include "minishell.h"

static char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

t_env_node *create_env_node(const char *env){
    t_env_node *new_node;
    char *delimiter_position;
    int name_length;
    int value_length;

    delimiter_position = ft_strchr(env , '=');
    if(delimiter_position == NULL){
        return NULL;
    }
    new_node = (t_env_node *)malloc(sizeof(t_env_node));
    if(new_node == NULL)
        return NULL;
    name_length = delimiter_position - env;
    value_length = ft_strlen(env) - name_length + 1;

    new_node->name = (char *)malloc(name_length + 1);
    if(new_node->name == NULL){
        free(new_node);
        return NULL;
    }
    ft_strncpy(new_node->value , delimiter_position + 1 , value_length);
    new_node->value[value_length] = '\0';

    return new_node;

}
