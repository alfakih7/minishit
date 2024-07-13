/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almohame <almohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 04:14:10 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/07/13 15:04:32 by almohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//function to skip a character
char	*chrskip(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != 0 && s[i] == c)
		i++;
	return (s + i);
}
//function to trim a character from a string, from the start and the end

static void	char_trim(char **line, int c)
{
	char	*set;

	set = malloc(2);
	set[0] = c;
	set[1] = 0;
	*line = ft_strtrim(*line, set);
	free(set);
	if (!*line)
		exit(EXIT_FAILURE);
}
//function to count the delimetre outside the quotes ans skip it if its inside

int	split_with_no_quotes_len(char *line, int c)
{
	int		i;
	int		len;
	bool	inside_quotes;
	bool	inside_dquotes;

	char_trim(&line, c);
	inside_quotes = false;
	inside_dquotes = false;
	i = -1;
	len = 0;
	while (line[++i])
	{
		if (line[i] == c && !inside_quotes && !inside_dquotes)
		{
			len++;
			while (line[i + 1] == c)
				i++;
		}
		else if (line[i] == '\'' && !inside_dquotes)
			inside_quotes = !inside_quotes;
		else if (line[i] == '\"' && !inside_quotes)
			inside_dquotes = !inside_dquotes;
	}
	return (free(line), len);
}
/**
 * This function identifies and returns the positions of a specified delimiter character 'c'
 * within a given string 'line', while ignoring delimiters that are enclosed within single or 
 * double quotes. It allocates and returns an array of integers where each element is an index 
 * in the string 'line' where the delimiter 'c' occurs, excluding those inside quoted sections.
 * The array is terminated with a -1 to indicate the end.
 *
 * The function is useful for parsing strings where delimiters should not be considered
 * if they appear within quoted text. For example, in CSV parsing or similar scenarios
 * where quoted fields may contain delimiter characters that should be ignored.
 *
 * Parameters:
 *   char *line - The input string to be parsed.
 *   int c - The delimiter character whose positions are to be identified.
 *
 * Returns:
 *   int* - An array of integers representing the positions of the delimiter in the string,
 *          excluding those inside quotes. The last element of the array is -1.
 */
int *ms_char_positions(char *line, int c)
{
    t_split_positions vars;
    int i;

    // Initialize vars structure to zero
    ft_bzero(&vars, sizeof(t_split_positions));
    
    // Allocate memory for positions array
    vars.positions = malloc(sizeof(int) * (split_with_no_quotes_len(line, c) + 2));
    
    i = -1;
    while (line[++i])
    {
        // Check if current character is the delimiter and not inside quotes
        if (line[i] == c && !vars.inside_dquotes && !vars.inside_quotes)
        {
            // Record the position and increment the current index
            vars.positions[vars.current_index++] = i;
            
            // Skip consecutive delimiters
            while (line[i + 1] == c)
                i++;
        }
        // Toggle the inside_dquotes flag if double quote is encountered
        else if (line[i] == '\"' && !vars.inside_quotes)
            vars.inside_dquotes = !vars.inside_dquotes;
        
        // Toggle the inside_quotes flag if single quote is encountered
        else if (line[i] == '\'' && !vars.inside_dquotes)
            vars.inside_quotes = !vars.inside_quotes;
    }
    
    // Mark the end of positions array with -1
    vars.positions[vars.current_index] = -1;

    // Return the positions array
    return vars.positions;
}
