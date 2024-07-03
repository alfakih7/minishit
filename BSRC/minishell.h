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

bool	check_multiple_pipes(char *line);
int update_quote_state(char current_char , int *quote_state);
char	*get_next_line(int fd);
int	check_quotes(char *command);
char	*chrskip(char *s, char c);
int	split_with_no_quotes_len(char *line, int c);
void ft_split_destroy(char **split_array);
char	**split_with_no_quotes(char *line, int c);
t_tokens	*tokens_1(char **str);
// t_tokens *split_with_no_quotes(char *line, int c);
int *ms_char_positions(char *line, int c);
size_t	get_ft_strlen(char *str);
char	*get_ft_strchr(const char *s, int c);
char	*get_ft_strjoin(char *s1, char *s2);
char	*get_ft_strdup(char *s1);
t_tokens	*ft_lstnew(void *content);
void	ft_lstadd_back(t_tokens **lst, t_tokens *new1);
int     ft_lstsize(t_tokens *lst);
//tokenization functions and some utils functions and struct
typedef struct s_inside
{
    bool quotes;   // Tracks if currently inside single quotes
    bool dquotes;  // Tracks if currently inside double quotes
} t_inside;
/**
 * 	when name is delim for heredoc, is_extra is set to true
 * 	when file is for append, is_extra is set to true
 */
typedef struct s_file
{
	char	*name;
	bool	is_extra;
}				t_file;

bool ft_is_space(char c);
char *ft_exclude_quotes(char *str);
t_file *ms_get_next_redirect(char *line_chunk, char type, int *ptr);
bool ft_is_space(char c);
char	*ft_skip_spaces(char *str);

bool	check_syntax(char *line);
#endif