#include "../headers/minishell.h"

s_global *global;   

// chatgpt function
const char* token_to_string(s_token token) {
    switch (token) {
        case IN:       return "<";
        case OUT:      return ">";
        case HEREDOC:  return "<<";
        case APPEND:   return ">>";
        case AND:      return "&&";
        case PIPE:     return "|";
        case OR:       return "||";
        case LPR:      return "(";
        case RPR:      return ")";
        case STR:      return "string";
        case END:      return "end of command";
        default:       return "unknown token";
    }

void    ft_initialize(char **env)
{
    global = malloc(sizeof(s_global)); 
    if (!global)
        return ;; 
    int i = 0;
    while(env[i])
        i++;
    global->env = malloc((i + 1) * sizeof(char *));
    if(!global->env)
        return;
    i = 0;
    while(env[i])
    {
        global->env[i] = ft_strdup(env[i]);
        i++;
    }
}

int ft_check_env(s_input *input, char **env)
{
    int i = 0;
    if(ft_strncmp(input->command,"env", 3) == 0)
    {
        while(env[i])
        {
            printf("%s\n", env[i]);
            i++;
        }
        return(0);
    }
    return (1);
}
int main(int argc, char **argv, char **env)
{
    char *rl;
	(void)argc;
	(void)argv;

    s_input *input;

    while(1)
    {
        rl = readline("minishell --> ");
        add_history(rl);
        ft_initialize(env);
        input = parsing(rl);
		if(!input)
			continue;
        ft_check_env(input, env);
        if(input->command[0] == '$')
            ft_expansion(input, global);
    }
	return 0;
}
