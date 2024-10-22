#include "./headers/minishell.h"

int main()
{
    char *str = "hello world this is my life rom now on";
    char *little= "this";
    printf("%s", ft_strnstr(str,little,ft_strlen(str)));
    return(0);
}