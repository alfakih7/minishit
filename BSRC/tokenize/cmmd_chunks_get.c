
#include "../minishell.h"
/*
 * Initializes an array of t_cmd_chunk pointers.
 * Allocates memory for 'amount' number of t_cmd_chunk pointers and initializes each chunk.
 * Also initializes inputs and outputs linked lists for each chunk.
 * Returns the initialized array of t_cmd_chunk pointers.
 */
static t_cmd_chunk **chunk_init(size_t amount)
{
    t_cmd_chunk **chunks;
    size_t i;

    // Allocate memory for array of t_cmd_chunk pointers
    chunks = malloc(sizeof(t_cmd_chunk *) * (amount + 1));

    // Initialize each t_cmd_chunk and its associated lists
    i = 0;
    while (i < amount)
    {
        chunks[i] = ft_calloc(1, sizeof(t_cmd_chunk));
        if (!chunks[i])
            exit(EXIT_FAILURE);
        
        // Initialize inputs and outputs lists
        chunks[i]->inputs = ft_lstnew(NULL);
        chunks[i]->outputs = ft_lstnew(NULL);
        
        i++;
    }

    // Set the last element of the array to NULL to indicate the end
    chunks[i] = NULL;

    return chunks;
}

/*
 * Determines the type of token at the beginning of the line.
 * Checks for '<' (input redirection), '>' (output redirection), or '2' (command).
 * Returns the corresponding token type as an integer.
 */
static int token_type(char *line)
{
    if (contains_redirect(line, '<'))
        return '<';
    if (contains_redirect(line, '>'))
        return '>';
    if (contains_cmd(line))
        return 2;

    // Return -1 for unrecognized token
    return -1;
}
/*
 * Checks if a command chunk is empty or in an erroneous state.
 * Trims leading and trailing spaces from 'line', then checks if the command, inputs, and outputs lists are empty.
 * Frees the trimmed 'line' and returns true if the command chunk is empty; otherwise, returns false.
 */
static bool is_err(t_cmd_chunk **chunks, int reach, char *line)
{
    char *nline;

    // Trim leading and trailing spaces from 'line'
    nline = ft_strtrim(line, " ");

    // Check if the command, inputs, and outputs lists are empty
    if (!chunks[reach]->cmd && !chunks[reach]->inputs->content
        && !chunks[reach]->outputs->content)
        return free(nline), true;

    // Free trimmed 'line' and return false if the command chunk is not empty
    return free(nline), false;
}
/*
 * Adds a new node (new_node) to the end of a specified list (inputs or outputs) in a command chunk (chunk).
 * Checks if new_node is NULL; if so, returns false indicating failure.
 * Otherwise, adds new_node to the specified list and adjusts the list if the added node's content is NULL.
 * Returns true upon successful addition.
 */
static bool	add_back(t_cmd_chunk *chunk, char type, t_file *new_node)
{
	t_list	*temp;
	t_list	**lst;

	if (!new_node)
		return (false);
	lst = NULL;
	if (type == '>')
		lst = &(chunk->outputs);
	else if (type == '<')
		lst = &(chunk->inputs);
	ft_lstadd_back(lst, ft_lstnew(new_node));
	if ((*lst)->content == NULL)
	{
		temp = (*lst);
		(*lst) = (*lst)->next;
		free(temp);
	}
	return (true);
}

/*
 * Parses an array of command pieces (line_pieces) into structured command chunks (t_cmd_chunk).
 * Initializes an array of t_cmd_chunk pointers using chunk_init.
 * Iterates through each command piece, determines its type using token_type, and processes it accordingly.
 * Handles errors using is_err and adds input/output redirections using add_back.
 * Returns the initialized array of t_cmd_chunk pointers upon successful parsing; otherwise, cleans up and returns NULL.
 */
t_cmd_chunk **ms_command_chunks_get(char **line_pieces, size_t amount)
{
    t_cmd_chunk **chunks;
    int i;
    int token;
    int ptr;

    // Initialize array of t_cmd_chunk pointers
    chunks = chunk_init(amount);

    // Iterate through each command piece
    i = -1;
    while (++i < (int)amount)
    {
        ptr = 0;
        // Process each character in the current command piece
        while (line_pieces[i][ptr] && *ft_skip_spaces(&line_pieces[i][ptr]))
        {
            // Determine token type of the current position
            token = token_type(&line_pieces[i][ptr]);

            // Handle error condition or parse command and redirections
            if (token == -1 && is_err(chunks, i, &line_pieces[i][ptr]))
                return (ms_clean(chunks, NULL, NULL), NULL);
            else if (token == 2)
                chunks[i]->cmd = ms_get_fullcmd(line_pieces[i], &ptr);
            else if (token == '<' || token == '>')
                // t_file * new_node = ms_get_next_redirect(line_pieces[i], token, &ptr);
                if (!add_back(chunks[i], token,
                        ms_get_next_redirect(line_pieces[i], token, &ptr)))
                    return (ms_clean(chunks, NULL, NULL), NULL);
        }
    }

    // Return the initialized array of t_cmd_chunk pointers
    return chunks;
}
