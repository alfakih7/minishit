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

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;


typedef struct s_cmd_chunk {
    t_list  *inputs;    // Linked list of input files or data
    t_list  *outputs;   // Linked list of output files or data
    char    **cmd;        // Full command associated with this chunk
    int       out_fd;     // Output file descriptor
    int       in_fd;      // Input file descriptor
}   t_cmd_chunk;

typedef struct s_file
{
    char    *name;
    bool    is_extra;
}   t_file;

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

int     update_quote_state(char current_char , int *quote_state);
char    *get_next_line(int fd);
int     check_quotes(char *command);
char    *chrskip(char *s, char c);
int     split_with_no_quotes_len(char *line, int c);
void    ft_split_destroy(char **split_array);
char **split_with_no_quotes(char *line, int c);
int     *ms_char_positions(char *line, int c);
size_t  get_ft_strlen(char *str);
char    *get_ft_strchr(const char *s, int c);
char    *get_ft_strjoin(char *s1, char *s2);
char    *get_ft_strdup(char *s1);
t_list *ft_lstnew(void *content);
void    ft_lstadd_back(t_list **lst, t_list *new);
int     ft_lstsize(t_list *lst);
bool    contains_cmd(char *line_chunk);
typedef struct s_inside
{
    bool quotes;    // Tracks if currently inside single quotes
    bool dquotes;   // Tracks if currently inside double quotes
}   t_inside;

bool    ft_is_space(char c);
char    *ft_exclude_quotes(char *str);
t_file  *ms_get_next_redirect(char *line_chunk, char type, int *ptr);
char    *ft_skip_spaces(char *str);
bool    contains_redirect(char *line_chunk, char type);
char    *ms_get_cmd(char *line_chunk);
char    **ms_get_fullcmd(char *line_piece, int *ptr);
t_cmd_chunk **ms_command_chunks_get(char **line_pieces, size_t amount);
void    t_file_destroy(void *file);
void    ft_lstclear(t_list **lst, void (*del)(void *));
void    ms_clean(t_cmd_chunk **chunks, char **string_chunks, char *line);
bool    contains_cmd(char *line_chunk);

#endif
