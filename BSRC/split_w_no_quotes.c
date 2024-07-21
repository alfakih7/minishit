/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_w_no_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:11:07 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/20 17:41:11 by asid-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * Function: ft_split_destroy
 * --------------------------
 * Frees memory allocated for an array of strings and its contents.
 * Assumes the array is terminated by a NULL pointer.
 *
 * This function iterates through each string in the array 'split_array',
 * freeing the memory allocated for each substring and then frees the
 * memory allocated for the array itself.
 *
 * Parameters:
 *   char **split_array - Pointer to an array of strings (char *) to be freed.
 */

void ft_split_destroy(char **split_array) {
    if (split_array) {
        // Iterate through the array until NULL terminator is encountered
        for (int i = 0; split_array[i] != NULL; ++i) {
            free(split_array[i]); // Free each substring
        }
        free(split_array); // Free the array of pointers
    }
}


/**
 * Calculates the length of a substring based on 'start_pos' and the position of the next delimiter 'next_c'.
 * If 'next_c' is -1, computes the length from 'start_pos' to the end of 'line'.
 *
 * Used for parsing strings where substrings are delineated by delimiters.
 *
 * Parameters:
 *   char *line - The original string.
 *   char *start_pos - Starting position of the substring.
 *   int next_c - Position of the next delimiter after 'start_pos'. -1 if none.
 *
 * Returns:
 *   size_t - Length of the substring from 'start_pos' to 'next_c' or end of 'line'.
 */
static size_t get_length(char *line, char *start_pos, int next_c)
{
    if (next_c == -1)
        return (ft_strlen(start_pos));
    return (ft_strlen(start_pos) - ft_strlen(line + next_c));
}
/**
 * Populates an array of substrings from a given string, excluding delimiters within quotes.
 *
 * This function skips over delimiters ('vars->c') inside quotes in 'vars->line',
 * creating substrings stored in 'vars->content'. It manages memory allocation
 * and ensures proper termination of the array with NULL.
 *
 * Parameters:
 *   t_split_vars *vars - Structure containing input string, delimiter, positions, and content array.
 *
 * Returns:
 *   bool - True if successful in populating 'vars->content', false on failure.
 */


static bool fill_content(t_split_vars *vars)
{
    size_t i;
    int current_index;
    char *start_pos;

    i = 0;
    current_index = 0;
    while (i < vars->content_size)
    {
        // Find the next valid starting position after skipping delimiters
        start_pos = chrskip(vars->line + current_index, vars->c);
        
        // Check if start_pos is NULL or points to an empty string
        if (!start_pos || !*start_pos)
            return (free(vars->positions), free(vars->content), false);
        
        // Create a substring from start_pos to the delimiter position
        vars->content[i] = ft_substr(start_pos, 0, get_length(vars->line, start_pos, vars->positions[i]));
        // Check if ft_substr failed (returns NULL)
        if (!vars->content[i])
            return (free(vars->positions), ft_split_destroy(vars->content), false);
        
        // Update current_index to the next position after the current delimiter
        current_index = vars->positions[i++] + 1;
    }
    
    // Terminate the content array with NULL
    vars->content[vars->content_size] = NULL;
    
    return true;
}
/**
 * Splits a string into substrings based on a delimiter, excluding delimiters within quotes.
 *
 * This function takes a string 'line' and splits it into multiple substrings using 'c' as the delimiter.
 * It skips leading occurrences of 'c', handles quoted sections correctly, and allocates memory
 * dynamically for each substring. Returns an array of substrings or NULL on failure.
 *
 * Parameters:
 *   char *line - The input string to be split.
 *   int c - The delimiter character to split 'line'.
 *
 * Returns:
 *   char ** - An array of substrings from 'line' split by 'c', or NULL if memory allocation fails.
 */

/////// given the pipe as a token


char **split_with_no_quotes(char *line, int c)
{
    t_split_vars vars;
	char *temp;

    // Skip leading occurrences of 'c' in 'line'
    while (*line == c)
        line++;

    // Return NULL if 'line' is NULL or an empty string
    if (!line || !*line)
        return (NULL);

    // Initialize variables in 'vars' structure
    vars.c = c;
    vars.line = line;

    // Calculate the number of segments (content_size) and their positions
    vars.content_size = split_with_no_quotes_len(line, c) + 1;
    
    // If there are no delimiters, handle it by returning the original string in an array
    if (vars.content_size == 1)
    {
        vars.content = malloc(sizeof(char *) * 2); // Allocate space for one string and a NULL terminator
        if (!vars.content)
            return (NULL);
		temp = ft_strtrim(line, " ");
		if (!temp)
			return (NULL);
        vars.content[0] = ft_strdup(temp); // Duplicate the original string
		free(temp);
        vars.content[1] = NULL; // NULL terminate the array
        return vars.content;
    }

    vars.positions = ms_char_positions(line, c);
    if (!vars.positions)
        return (NULL);

    vars.content = malloc(sizeof(char *) * (vars.content_size + 1));
    if (!fill_content(&vars))
        return (NULL);

    return (free(vars.positions), (vars.content));
}
