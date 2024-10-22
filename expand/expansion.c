#include "../headers/minishell.h"

int ft_isspace(char c)
{
    if(c < 32)
        return(0);
    return (1);
}
void expand_printf(char *output)
{
    int i = 0;
    while(output[i] != '\0')
    {
            printf("%c", output[i]);
            if(ft_isspace(output[i+1]) == 0)
                i++;
        i++;
    }
    printf("\n");
}
void ft_expansion(s_input *input, s_global *global)
{
    int j = ft_strlen(input->command);
    int i = 0;
    char *output;
    while(global->env[i])
    {
        if(ft_strncmp(&input->command[1], global->env[i], j-1) == 0)
        {
            output = ft_strnstr(global->env[i], &input->command[1], j);
            expand_printf(&output[j]);
            // printf("%s\n", &output[j]);
            return;
        }
        i++;
    }
    return;
}