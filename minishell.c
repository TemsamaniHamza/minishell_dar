#include "minishell.h"

int main(int argc, char **argv, char **env)
{
    char *rl;
	(void)argc;
	(void)argv;
    (void)env;

    s_input *input;

    while(1)
    {
        rl = readline("minishell --> ");
        add_history(rl);
        input = parsing(rl);
		if(!input)
			continue;
		printf("command: %s\n", input->command);
    }
	return 0;
}