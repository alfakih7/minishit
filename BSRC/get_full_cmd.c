#include "minishell.h"

// This function removes quotes from each string in the given array of strings.
// It uses the ft_exclude_quotes function to remove the quotes and frees the old strings.
static void remove_quotes(char **arr)
{
    int   i;       // Index variable for iterating through the array
    char  *temp;   // Temporary pointer to hold the original string

    i = -1;
    // Loop through each string in the array until the end (null pointer) is reached
    while (arr[++i])
    {
        temp = arr[i];                  // Save the current string in temp
        arr[i] = ft_exclude_quotes(arr[i]); // Remove quotes from the string and assign the new string back to the array
        free(temp);                     // Free the memory of the original string
    }
}


// This function updates the state of single and double quotes within the t_inside struct.
// It toggles the quotes state based on the input character 'c'.
static int tick_inside_vars(t_inside *inside, char c)
{
    // If the character is a single quote and we are not inside double quotes
    if (c == '\'' && !inside->dquotes)
    {
        // Toggle the single quotes state
        inside->quotes = !inside->quotes;
    }
    // If the character is a double quote and we are not inside single quotes
    else if (c == '\"' && !inside->quotes)
    {
        // Toggle the double quotes state
        inside->dquotes = !inside->dquotes;
    }
    // Always return 1 indicating successful execution
    return (1);
}

// This function checks if a given character signifies the end of a token.
// The character is considered an end if it is not inside single or double quotes,
// and it is either a null character, '>', or '<'.
static bool is_end(char c, t_inside *inside)
{
    // Check if we are not inside double quotes and not inside single quotes
    if (!inside->dquotes && !inside->quotes)
    {
        // Check if the character is a null character, '>', or '<'
        if (c == 0 || c == '>' || c == '<')
        {
            // Return true indicating it is the end of a token
            return (true);
        }
    }
    // Return false indicating it is not the end of a token
    return (false);
}
// This function extracts a command from the given line piece starting at the position
// pointed to by ptr, processes it to remove quotes, and returns the command split into an array of strings.
char **ms_get_fullcmd(char *line_piece, int *ptr)
{
    char        **cmds;         // Array of strings to hold the parsed command
    char        *temp;          // Temporary string to hold a substring of the command
    int         cmds_length;    // Length of the command string to be extracted
    t_inside    inside;         // Struct to keep track of quote states

    // If the input line_piece is null or the character at the pointer position is null, return 0
    if (!line_piece || !line_piece[*ptr])
        return (0);

    cmds_length = 0;            // Initialize the command length to 0
    ft_bzero(&inside, sizeof(t_inside)); // Zero out the inside struct to initialize it

    // Loop to determine the length of the command by checking each character
    // The loop continues until it finds an end character or encounters spaces outside of quotes
    while (!is_end((line_piece + *ptr)[cmds_length], &inside)
        && *ft_skip_spaces((line_piece + *ptr)))
        cmds_length += tick_inside_vars(&inside, (line_piece + *ptr)[cmds_length]);

    // If no command is found or the length of the command is 0, return NULL
    if (!ms_contains_cmd((line_piece + *ptr)) || cmds_length == 0)
        return (NULL);

    // Extract the substring from line_piece starting at *ptr with length cmds_length
    temp = ft_substr((line_piece + *ptr), 0, cmds_length);

    // Split the extracted substring into an array of strings, removing quotes
    cmds = split_with_no_quotes(temp, ' ');

    // If the split fails, free the temporary string and return NULL
    if (!cmds)
        return (free(temp), NULL);

    // Update the pointer position by adding the length of the processed command
    (*ptr) += cmds_length;

    // Free the temporary string, remove quotes from the command array, and return the command array
    return (free(temp), remove_quotes(cmds), cmds);
}
