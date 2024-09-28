#include "minishell.h"

s_token	check_tok(char c1, char c2)
{
	if (c1 == '|' && c2 == '|')
		return (OR);
	if (c1 == '&' && c1 == '&')
		return (AND);
	if (c1 == '<' && c2 == '<')
		return (HEREDOC);
	if (c1 == '>' && c2 == '>')
		return (APPEND);
	if (c1 == '(')
		return (LPR);
	if (c1 == ')')
		return (RPR);
	if (c1 == '|')
		return (PIPE);
	if (c1 == '>')
		return (OUT);
	if (c1 == '<')
		return (IN);
	if (!c1)
		return (END);
	return (STR);
}

int check_beggining_of_str(char *str)
{
    s_token tok;

    tok = check_tok(str[0], str[1]);
    if(tok == OR || tok == AND || tok == PIPE || tok == RPR)
    {
        printf("synsttax ghalat file minishell.c line x");
        return(0);
    }
    return(1);
}

s_input *parsing(char *rl)
{
    char *str;
    s_input *head;

    str = ft_strtrim(rl, " \t\n\v\f\r");
    free(rl);
    if(!str || !check_beggining_of_str(str))
        return (free(str), NULL);
    head = token_everythig(str);

}


s_input	*token_everythig(char *str)
{
	s_input	*head;
	int     par;
	int     i;

	par = 0;
	i = 0;
	head = NULL;
	while (str[i])
	{
		if (!choice_token(&head, str, &i, &par))
			return (_free_head(head), free(str), NULL);
	}
    free(str);
    str = NULL;
	return (head);
}


int main(int argc, char **argv, char **env)
{
    char *rl;
    s_input *input;

    while(1)
    {
        rl = readline("minishell --> ");
        if(!rl)
            break;
        add_history(rl);
        input = parsing(rl);
    }
}