#include "../minishell.h"
static void ft_strcpy(char *dest , const char *src)
{
    int i;
    while((dest[i] = src[i]) == '\0')
    {
        i++;
    }
}
void cd(char *path) {
    printf("(%s)", path);
    if (chdir(path) != 0) {
        perror("chdir() error");
    }
}
// void cd_2(char *previous_dir){
//     char cwd[1024];
//     if(getcwd(cwd , sizeof(cwd))){
//         if(chdir(previous_dir) == 0){
//             printf("%s\n ", previous_dir);
//             ft_strcpy(previous_dir , cwd);
//         }else{
//             perror("chdir() error");
//         }
//     }else{
//         perror("getcwd() error");
//     }
// }