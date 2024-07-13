#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/SRC/libft.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

enum RedirectionType {
    REDIR_IN,         // <
    REDIR_HEREDOC,    // <<
    REDIR_OUT,        // >
    REDIR_APPEND      // >>
};

typedef struct s_cmd
{
	char		    **content;
	struct s_files *redirect;
}	t_cmd;

typedef struct s_files
{
	int				type;
	char		    *file_name;
	struct s_files *next;
}	t_files;

typedef struct s_split_positions {
    int     *positions;      // Array to store positions of the delimiter
    int     current_index;   // Current index in the positions array
    bool    inside_quotes;   // Flag indicating if we are inside single quotes
    bool    inside_dquotes;  // Flag indicating if we are inside double quotes
}   t_split_positions;

typedef struct s_split_vars {
    char    *line;           // Original string to be split
    int     c;               // Delimiter character
    size_t  content_size;    // Number of segments expected
    int     *positions;      // Array of delimiter positions
    char    **content;       // Array to store resulting substrings
}   t_split_vars;

bool	check_multiple_pipes(char *line);
int update_quote_state(char current_char , int *quote_state);
char	*get_next_line(int fd);
int	check_quotes(char *command);
char	*chrskip(char *s, char c);
int	split_with_no_quotes_len(char *line, int c);
void ft_split_destroy(char **split_array);
// char	**split_with_no_quotes(char *line, int c);
char **split_with_no_quotes(char *line, int c);
int *ms_char_positions(char *line, int c);
size_t	get_ft_strlen(char *str);
char	*get_ft_strchr(const char *s, int c);
char	*get_ft_strjoin(char *s1, char *s2);
char	*get_ft_strdup(char *s1);
t_files	*ft_lstnew(void *content, int type);
void	ft_lstadd_back(t_files **lst, t_files *new1);
int     ft_lstsize(t_files *lst);
bool	contains_cmd(char *line_chunk);
//tokenization functions and some utils functions and struct
typedef struct s_inside
{
    bool quotes;    // Tracks if currently inside single quotes
    bool dquotes;   // Tracks if currently inside double quotes
}   t_inside;

bool    ft_is_space(char c);
char    *ft_exclude_quotes(char *str);
bool    contains_cmd(char *line_chunk);

bool	check_syntax(char *line);
t_cmd	*ft_redirection(char **env, char *line);
char	*joined_str(char *line);
char	*expansion(char **env, char *line);


typedef struct s_env_node {
    char *name;
    char *value;
    struct s_env_node *next;
} t_env_node;

#endif
