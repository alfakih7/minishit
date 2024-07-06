
#include "../minishell.h"
void ft_lstclear(t_list **lst, void (*del)(void*))
{
    t_list *temp;

    if (!lst || !del)
        return;

    while (*lst)
    {
        temp = (*lst)->next;  // Store the next pointer before deletion

        // Delete the content using the provided deletion function
        if ((*lst)->content)
            del((*lst)->content);

        // Free the current node
        free(*lst);

        // Move to the next node
        *lst = temp;
    }

    *lst = NULL;  // Set the list pointer to NULL after clearing
}

// Function to destroy and free memory associated with a t_file structure
void t_file_destroy(void *file)
{
    // Declare a local copy of the t_file structure
    t_file file_cpy;

    // Check if the input file pointer is NULL, return immediately if it is
    if (!file)
        return;

    // Copy the contents of the input file pointer to the local file_cpy structure
    ft_memcpy(&file_cpy, file, sizeof(t_file));

    // Free the memory allocated for the name field within the t_file structure
    free(file_cpy.name);

    // Free the memory allocated for the original file structure
    free(file);
}
// Function to clean up and free resources used during command processing
void ms_clean(t_cmd_chunk **chunks, char **string_chunks, char *line)
{
    // Declare an integer variable for use in loops
    int i;

    // Check if the chunks array is not NULL
    if (chunks)
    {
        // Initialize the loop counter to -1
        i = -1;

        // Loop through each chunk in the chunks array until a NULL pointer is encountered
        while (chunks[++i])
        {
            // Free the memory allocated for the cmd field within the current chunk
            ft_split_destroy(chunks[i]->cmd);

            // Clear the inputs list of the current chunk, using t_file_destroy to free each element
            ft_lstclear(&(chunks[i]->inputs), t_file_destroy);

            // Clear the outputs list of the current chunk, using t_file_destroy to free each element
            ft_lstclear(&(chunks[i]->outputs), t_file_destroy);

            // Check if the in_fd of the current chunk is greater than 0, close the file descriptor if it is
            if (chunks[i]->in_fd > 0)
                close(chunks[i]->in_fd);

            // Check if the out_fd of the current chunk is greater than 1, close the file descriptor if it is
            if (chunks[i]->out_fd > 1)
                close(chunks[i]->out_fd);

            // Free the memory allocated for the current chunk
            free(chunks[i]);
        }

        // Free the memory allocated for the chunks array
        free(chunks);
    }

    // Check if the string_chunks array is not NULL, and free its memory if it is not
    if (string_chunks)
        ft_split_destroy(string_chunks);

    // Check if the line pointer is not NULL, and free its memory if it is not
    if (line)
        free(line);
}
