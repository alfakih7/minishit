#include "minishell.h"

char	*ft_skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (ft_is_space(str[i]))
		i++;
	return (str + i);
}
/**
 * Checks if a character is a whitespace character (space, tab, newline, etc.).
 *
 * Parameters:
 *   char c - The character to be checked.
 *
 * Returns:
 *   bool - True if 'c' is a whitespace character, false otherwise.
 */
bool ft_is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}
/**
 * Finds the end position of a token in a string, considering quotes and delimiters.
 * Handles spaces, '>', and '<' as delimiters unless inside quotes.
 *
 * param str - The input string to be tokenized.
 * param inside - Struct tracking the state of quotes.
 * return The index marking the end of the current token.
 */

static int find_token_end_position(char *str, t_inside *inside)
{
    int i;

    i = -1;
    while (str[++i])
    {
        // If the character is a space, '>', or '<' and we are not inside quotes
        if ((ft_is_space(str[i]) || str[i] == '>' || str[i] == '<')
            && !inside->dquotes && !inside->quotes)
            return (i);
        
        // If the character is a single quote and we are not inside double quotes
        else if (str[i] == '\'' && !inside->dquotes)
            inside->quotes = !inside->quotes; // Toggle the state of inside->quotes
        
        // If the character is a double quote and we are not inside single quotes
        else if (str[i] == '\"' && !inside->quotes)
            inside->dquotes = !inside->dquotes; // Toggle the state of inside->dquotes
    }
    
    // If no delimiter is found, return the length of the string
    return (i);
}
/**
 * Parses the next redirection operation and retrieves associated file information
 * from the provided command line chunk.
 *
 * @param line_chunk The segment of command line containing redirection and file details.
 * @param type       The type of redirection ('>' or '<') to expect.
 * @param ptr        Pointer to track current position in line_chunk, updated to
 *                   point past processed components.
 * @return           A pointer to a dynamically allocated t_file structure containing
 *                   parsed redirection details, or NULL if an error occurs.
 */
t_file *ms_get_next_redirect(char *line_chunk, char type, int *ptr)
{
    int len;
    t_inside inside;
    t_file *file;
    char *temp;

    // Initialize inside struct to track quote states
    ft_bzero(&inside, sizeof(inside));

    // Allocate memory for the file structure
    file = malloc(sizeof(t_file));

    // Skip leading spaces in line_chunk
    *ptr += ft_skip_spaces(line_chunk + *ptr) - (line_chunk + *ptr);

    // Move past the redirection symbol ('>', '<')
    *ptr += 1;

    // Check if the redirection is an "extra" (like '>>' for append)
    file->is_extra = line_chunk[*ptr] == type;
    *ptr += file->is_extra;

    // Skip any spaces after the redirection symbol
    *ptr += ft_skip_spaces(line_chunk + *ptr) - (line_chunk + *ptr);

    // Determine the length of the file name or path until the next delimiter
    len = find_token_end_position((line_chunk + *ptr), &inside);

    // Handle unexpected token scenario
    if (len == 0) {
        return (ft_putendl_fd("syntax error, unexpected token", 2), free(file), NULL);
    }

    // Adjust pointer past the filename, considering quotes
    *ptr += (inside.dquotes || inside.quotes);

    // Extract the filename substring
    file->name = ft_substr((line_chunk + *ptr), 0, len);

    // Remove surrounding quotes from the filename
    temp = file->name;
    file->name = ft_exclude_quotes(file->name);

    // Move the pointer past the filename, considering quotes
    *ptr += len + (inside.dquotes || inside.quotes);

    // Free temporary variable and return the file structure
    return (free(temp), file);
}
