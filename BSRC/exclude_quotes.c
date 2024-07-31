#include "minishell.h"

static int	count_without_quotes(char *s)
{
    int i;
    int count;
    t_inside inside;

    count = 0;
    i = -1;
    ft_bzero(&inside, sizeof(inside));
    while (s[++i])
    {
        if (s[i] == '\'' && !inside.dquotes)
            inside.quotes = !inside.quotes;
        else if (s[i] == '\"' && !inside.quotes)
            inside.dquotes = !inside.dquotes;
        else
            count++;
    }
    return (count);
}
char	*ft_exclude_quotes(char *str)
{
    int index;          // Index for iterating through str
    int nstr_index;     // Index for populating nstr
    char *new_str;      // Pointer to store the new string without quotes
    t_inside quote_state; // Struct to manage quote states

	if (str && (ft_strchr(str, '\'') || ft_strchr(str, '\"')))
	{
		index = -1;
		nstr_index = 0;
		ft_bzero(&quote_state, sizeof(quote_state));
		new_str = malloc(count_without_quotes(str) + 1); ///need null protection ?
		while (new_str && str[++index])
		{
			if (str[index] == '\'' && !quote_state.dquotes)
				quote_state.quotes = !quote_state.quotes;
			else if (str[index] == '\"' && !quote_state.quotes)
				quote_state.dquotes = !quote_state.dquotes;
			else
				new_str[nstr_index++] = str[index];
		}
		new_str[nstr_index] = '\0';  // Null-terminate the new string
		free (str);
   		return (new_str);
	}
	return (str);
}

void	do_excluding_quotes(t_cmd *cmd)
{
	int i;
	t_files *temp;

	i = -1;
	if (!cmd)
		return ;
	while (cmd)
	{
		if (cmd->redirect)
		{
			temp = cmd->redirect;
			while (cmd->redirect)
			{
				if (cmd->redirect->file_name)
					cmd->redirect->file_name = ft_exclude_quotes(cmd->redirect->file_name);
				cmd->redirect = cmd->redirect->next;
			}
			cmd->redirect = temp;
		}
		if (cmd->content)
		{
			i = -1;
			while (cmd->content[++i])
				cmd->content[i] = ft_exclude_quotes(cmd->content[i]);
		}
		cmd = cmd->next;
	}
}
