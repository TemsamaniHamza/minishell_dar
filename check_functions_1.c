#include "minishell.h"

s_token	check_token(char c1, char c2)
{
	if (c1 == '|' && c2 == '|')
		return (OR);
	if (c1 == '&' && c2 == '&')
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

    tok = check_token(str[0], str[1]);
    if(tok == OR || tok == AND || tok == PIPE || tok == RPR)
    {
        printf("synsttax ghalat file [minishell.c] line x");
        return(0);
    }
    return(1);
}

int	check_true(s_token tok)
{
	if (tok == STR || tok == IN || tok == OUT || tok == APPEND || tok == HEREDOC)
		return (1);
	else
		return (0);
}

int check_token_syntax(char *s, int *i, int tok, int *par)
{
	(*i)++;
	if (tok == OR || tok == AND || tok == HEREDOC || tok == APPEND)
		(*i)++;
	else if (tok == LPR)
	{
		if (!*par)
			*par = *i;
		*par = check_rpr(&s[*par], *par) + 1;
		if (!*par)
			return (0);
	}
	else if (tok == RPR && *i > *par)
	{
		printf("syntax error near unexpected token `)'\n");
		return (0);
	}
	while (check_spaces(s[*i]) == 1)
		(*i)++;
	if (check_syntax(tok, &s[*i]) == 0)
		return (0);
	return (1);
}

int	check_syntax_help(s_token tok, s_token next)
{
	if (tok == OR || tok == AND || tok == PIPE)
	{
		if (next == STR || next == IN || next == OUT
			|| next == APPEND || next == LPR)
			return (1);
	}
	if (tok == LPR)
	{
		if (next == STR || next == IN || next == OUT
			|| next == APPEND || next == LPR)
			return (1);
	}
	if (tok == RPR)
	{
		if (next == AND || next == OR || next == PIPE
			|| next == RPR || next == END)
			return (1);
	}
	if (tok == IN || tok == OUT || tok == APPEND || tok == HEREDOC)
	{
		if (next == STR)
			return (1);
	}
	return (0);
}

int	check_syntax(s_token tok, char *s)
{
	s_token	next;

	next = check_token(*s, *(s + 1));
	if (check_syntax_help(tok, next))
		return (1);
	if (next == END)
		printf("syntax error near unexpected token`newline'\n");
	else if (next == AND || next == OR || next == APPEND || next == HEREDOC)
		printf("syntax error near unexpected token`%c%c'\n", *s, *(s + 1));
	else
		printf("syntax error near unexpected token`%c'\n",*s);
	return (0);
}

int	check_spaces(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}
int	check_pre(s_token tok)
{
	if (tok == IN || tok == OUT || tok == APPEND || tok == HEREDOC)
		return (4);
	if (tok == PIPE)
		return (3);
	if (tok == OR || tok == AND)
		return (2);
	return (1);
}

int	check_rpr(char *s, int i)
{
	while (*s)
	{
		if (*s == ')')
			return (i);
		i++;
		s++;
	}
	return (-1);
}