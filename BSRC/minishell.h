#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/fcntl.h>
# include <sys/wait.h>
# include "../libft/SRC/libft.h"

enum RedirectionType {
    REDIR_IN,         // <
    REDIR_HEREDOC,    // <<
    REDIR_OUT,        // >
    REDIR_APPEND      // >>
};

typedef struct s_cmd
{
	int				cmd_num;
	char		    **content;
	struct s_files *redirect;
	struct s_cmd *next;
}	t_cmd;

typedef struct s_files
{
	int				type;
	int				fd;
	int				heredoc_fd[2];
	int				last_input;
	int				last_output;
	char		    *file_name;
	struct s_files *next;
}	t_files;

typedef struct s_expand
{
	char		    *expand;
	struct s_expand *next;
}	t_expand;

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
char	*expansion(char *line, char **env);
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
t_cmd	*ft_redirection(char **env, char *line, int n);
char	*joined_str(char *line);
char	*ft_exclude_quotes(char *str);
char	*expansion(char *line, char **env);
int		ft_inside_quotes(t_inside *inside , int c);
void	expand_lstadd_back(t_expand **lst, t_expand *new1);
t_expand	*expand_lstnew(void *content);
char	*ft_getenv(char *the_env);
void	ft_free(void *one_p, char **two_p);
void	do_excluding_quotes(t_cmd *cmd);


int	ft_cmdlstsize(t_cmd *lst);
void	ft_cmdlstadd_back(t_cmd **lst, t_cmd *new1);

typedef struct s_env
{
	char	*name;
	char	*value;
	struct s_env *next;
}	t_env;


////////execute the thing

typedef struct s_fds
{
	int	fd_input;
	int	fd_output;
	int	ac;
	int	pip[2];
	int	here[2];
}	t_fds;

char	**get_path(char **env);
void	ft_free1(void *one_p, char **two_p);
void	execute(t_cmd *full_cmd, t_cmd *cmd, char **env, int *fd);
char	*get_next_line(int fd);
size_t	get_ft_strlen(char *str);
char	*get_ft_strjoin(char *s1, char *s2);
char	*get_ft_strdup(char *s1);
char	*get_ft_strchr(const char *s, int c);
// void	execute_helper(char **av, t_fds *fd, int i);
void	heredoc_decide(char **av, t_fds	*fd, char **env);
void	pipe_decide(t_cmd *cmd, char **env, int fd[2]);
// void	here_doc(char **av, t_fds *fd);
int		the_exectue(t_cmd *cmd ,char **env);
void	execute_heredoc(t_cmd *full_cmd, t_files *files, int *pip);
int		the_ultimate_dup(t_cmd *full_cmd, t_files *files, int *fd);
void	free_one_cmd(t_cmd *cmd);
void	free_cmd(t_cmd *cmd);
#endif