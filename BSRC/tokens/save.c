/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:41:42 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/12 16:41:44 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// static char **array_dup(char **envp)
// {
// 	char **my_env;
// 	int i;

// 	i = 0;
// 	if (!envp && !*envp)
// 		return (NULL);
// 	while (envp[i])
// 		i++;
// 	my_env = malloc(sizeof(char *) * (i + 1));
// 	if (!my_env)
// 		return (NULL);
// 	i = -1;
// 	while (envp[++i])
// 		my_env[i] = ft_strdup(envp[i]);
// 	my_env[i] = NULL;
// 	return (my_env);
// }

//////askjdh >kasdh $PATH "akskdjh$PWD" $kasjdh $ $

static long	envcmp(char *str, char **my_env)
{
	int	i;
	long	n;

	// str++;
	n = 0;
	i = 0;
	while (my_env[n])
	{
		i = 0;
		while (str[i] == my_env[n][i])
		{
			if (my_env[n][i] == '=')
				return (n);
			i++;
		}
		if (my_env[n][i] == '=')
			return (n);
		n++;
	}
	return (9999999999999); //// check $$$$
}

// static char	*replace(char *str, char **my_env)
// {
// 	int	i;
// 	long	the_num;
// 	char	*repl;
// 	char	*str_after;

// 	i = 0;
// 	while (str[i] != '$')
// 		i++;
// 	if (!str[++i])
// 	{
// 		return (str);
// 	}
// 	the_num = envcmp(str, my_env);
// 	i = 0;
// 	while (str[i] != '$')
// 		i++;
// 	repl = malloc(i + 1);
// 	i = -1;
// 	while (str[++i] != '$')
// 		repl[i] = str[i];
// 	repl[i++] = '\0';
// 	if (the_num != 9999999999999)
// 		repl = ft_strjoin(repl, getenv(my_env[the_num]));
// 	else
// 	{
// 		repl = ft_strjoin(repl, NULL);
// 	}
// 	while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '\"' && str[i] != '$')
// 		i++;
// 	if (str[i])
// 		repl = ft_strjoin(repl, &str[i]);
// 	return (repl);
// }

// char	*expansion(char **env, char *line)
// {
// 	char	**my_env;
// 	long long	i;
// 	int			size;

// 	i = -1;
// 	size = 0;
// 	while (line[++i])
// 	{
// 		if (line[i] == '$')
// 			size++;
// 	}
// 	if (!line)
// 		return (NULL);
// 	my_env = array_dup(env);
// 	i = -1;
// 	if (ft_strchr(line, '$'))
// 	{
// 		while (++i < size)
// 			line = replace(line, my_env);
// 	}
// 	return (line);
// }
