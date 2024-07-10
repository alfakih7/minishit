#include "../minishell.h"
void pwd(){
    char cwd[1024];
    if(getcwd(cwd , sizeof(cwd))!= NULL)
    {
        printf("%s\n", cwd);
    }else{
        perror("error in pwd");
    }
}
// char * oldpwd(){
//     char cwd[1024];
//     getcwd(cwd , sizeof(cwd));
//     char *old_pwd = ft_srdup(cwd);
//     return(old_pwd);

// }

// the pwd use getcwd to get the path
// and the old pwd should take this path and save it whenever i use cd
// so if i use cd .. it give the cd this path as a param and enter it