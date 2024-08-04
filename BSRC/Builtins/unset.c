#include "../minishell.h"

// void unset(char **env , char *str){
//     int i ;
//     int x;
//     int num;
//     int name_length;
//     i = 0;
//     x = 0;
//     num = 0;
//     name_length = 0;
//     while(env[num] != NULL)
//         num++;
//     // env = malloc(sizeof (char *)* num);
//     while(i != num){
//         char *equal_position= ft_strchr(env[i], '=');
//         if(equal_position == NULL){
//             i++;
//         }else{
//             name_length = equal_position - env[i];
//             if(ft_strncmp(env[i], str , name_length) == 0 && str[name_length] == '\0'){

//                 env[i] = NULL;

//                 x = i;
//                 i++;

//                 while(i < num){
//                     env[x++] = env[i++];
//                 }
//                 env[x] = NULL;
//                 return;
//             }
//             i++;
//         }
//     }
//     perror("error variable not found");
// }

// int main(int ac, char **av, char **env) {

//     unset(env, "MallocNanoZone");

//     int i = 0;
//     while (env[i] != NULL) {
//         printf("%s\n", env[i]);
//         i++;
//     }

//     return 0;
// }