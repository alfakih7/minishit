#include "minishell.h"
// This function extracts a command from the given line chunk, ignoring leading spaces,
// and stopping at special characters '>' or '<'. It returns the extracted command as a new string.
char *ms_get_cmd(char *line_chunk)
{
    char    *cmd;       // Pointer to hold the extracted command
    char    *line;      // Pointer to the line chunk after skipping leading spaces
    int     len;        // Length of the command to be extracted
    int     i;          // Index variable for iteration

    // If the input line_chunk is null, return NULL
    if (!line_chunk)
        return (NULL);

    // Skip leading spaces in the line_chunk and get the pointer to the first non-space character
    line = ft_skip_spaces(line_chunk);

    // If the resulting line is null or empty, return NULL
    if (!line || !*line)
        return (NULL);

    len = 0; // Initialize the length of the command to 0

    // Loop to determine the length of the command until a '>' or '<' character is encountered
    while (line[len] && line[len] != '>' && line[len] != '<')
        len++;

    // Allocate memory for the command string, including space for the null terminator
    cmd = malloc(len + 1);
    if (!cmd)
        return (NULL); // If memory allocation fails, return NULL

    i = -1; // Initialize the index variable

    // Copy characters from the line to the command string
    while (++i < len)
        cmd[i] = line[i];

    cmd[i] = 0; // Null-terminate the command string

    return (cmd); // Return the extracted command
}
