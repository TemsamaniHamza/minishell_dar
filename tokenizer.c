#include "minishell.h"

s_input	*my_Tokenizer(char *str)
{
	s_input	*head;
	int     par;
	int     i;

	par = 0;
	i = 0;
	head = NULL;

	while (str[i])
	{
		if (!token_1(&head, str, &i, &par))
			return (free(str), NULL); // free head
	}
    free(str);
    str = NULL;
	return (head);
}

int token_1(s_input **head, char *s, int *i, int *par)
{
	s_token tok;
	s_input *node;

	tok = check_token(s[*i], s[(*i) + 1]);
	if(check_true(tok) == 0)
	{
		if(check_token_syntax(s, i, tok, par) == 0)
			return (0);
		node = node_creation_cmd(NULL,NULL,tok,check_pre(tok));
	}
	else
		node = token_2(s,tok,i);
	if(!node)
		return(0);
	if(node->tok == LPR)
	{
		if(check_left(head) == 0)
			free(node);
		return (0);
	}
	build_command_list(head,node);
	return(1);
}

s_input	*token_2(char *s, s_token tok, int *i)
{
	int save;
	char *str;
	s_redir *redir;

	save = *i;
	redir = NULL;
	while(check_true(tok) == 1)
	{
		if (tok != STR)
		{
			if(build_redir_list(&redir,node_creat_redir(prep_cmd(s, &save, 0, tok), tok)) == 0)
				return(0);
		}
		else
			save++;
		tok = check_token(s[save], s[save + 1]);
	}
	save = str_len(s, *i, 1);
	if(save<0)
		return (NULL);
	str = ft_substr(s, *i, save);
	if(!str)
		return (NULL);
	incre(s, i);
	return (node_creation_cmd(str,redir,STR, 0));
}

int	check_left(s_input **head)
{
	if (!head || !*head)
		return (1);
	while (*head && (*head)->right)
		*head = (*head)->right;
	if ((*head)->tok == STR)
	{
		printf("bash: syntax error near unexpected token `('\n");
		return (0);
	}
	return (1);
}