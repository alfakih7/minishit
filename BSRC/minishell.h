/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 07:42:44 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/06 07:42:46 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/SRC/libft.h"

typedef struct s_tokens
{
	char		    *content;
	struct s_tokens *next;
}	t_tokens;

typedef struct s_split_positions {
    int *positions;       // Array to store positions of the delimiter
    int current_index;    // Current index in the positions array
    bool inside_quotes;   // Flag indicating if we are inside single quotes
    bool inside_dquotes;  // Flag indicating if we are inside double quotes
} t_split_positions;

typedef struct s_split_vars {
    char *line;         // Original string to be split
    int c;              // Delimiter character
    size_t content_size;// Number of segments expected
    int *positions;     // Array of delimiter positions
    char **content;     // Array to store resulting substrings
} t_split_vars;

int			update_quote_state(char current_char , int *quote_state);
char		*get_next_line(int fd);
int			check_quotes(char *command);
char		*chrskip(char *s, char c);
int			split_with_no_quotes_len(char *line, int c);
void		ft_split_destroy(char **split_array);
t_tokens	*split_with_no_quotes(char *line, int c);
int			*ms_char_positions(char *line, int c);
size_t		get_ft_strlen(char *str);
char		*get_ft_strchr(const char *s, int c);
char		*get_ft_strjoin(char *s1, char *s2);
char		*get_ft_strdup(char *s1);
t_tokens	*ft_lstnew(void *content);
void		ft_lstadd_back(t_tokens **lst, t_tokens *newtoken);
int			ft_lstsize(t_tokens *lst);
void		ft_free(void *one_p, char **two_p);
char		**get_path(char **env);
void		execute(char *av, char **env);
#endif