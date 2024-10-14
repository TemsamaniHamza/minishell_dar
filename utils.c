#include "minishell.h"

int	build_command_list(s_input **head, s_input *add)
{
	s_input	*trav;

	if (!head || !add)
		return (0);
	if (!*head)
		*head = add;
	else
	{
		trav = *head;
		while (trav->right)
			trav = trav->right;
		trav->right = add;
		add->left = trav;
	}
	return (1);
}

s_input	*re_order_command(s_input **head)
{
	s_input	*tok_stack;
	s_input	*new_stack;

	tok_stack = NULL;
	new_stack = NULL;
	shunting_yard(head, &tok_stack, &new_stack);
	while (tok_stack)
		push(&tok_stack, &new_stack, 0);
	return (new_stack);
}

s_input	*node_creation_cmd(char *s, s_redir *redir, s_token tok, int token_flag)
{
	s_input	*node;

	node = malloc(sizeof(s_input));
	if (!node)
		exit(1);
	node->command = s;
	node->cmd = NULL;
	node->tok = tok;
	node->token_flag = token_flag;
	node->redirections = redir;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

s_redir	*node_creat_redir(char **s, s_token tok)
{
	s_redir	*node;

	if (!s)
		return (NULL);
	node = malloc(sizeof(s_redir));
	if (!node)
		exit(1);
	node->tok = tok;
	node->file = s[0];
	node->flg = 1;
	node->left = NULL;
	node->right = NULL;
	free(s);
	s = NULL;
	return (node);
}

int build_redir_list(s_redir **head, s_redir *add)
{
	s_redir *plus;

	if(!head || !add)
		return (0);
	if (!*head)
		*head = add;
	else
	{
		plus = *head;
		while (plus->right)
			plus = plus->right;
		plus->right = add;
		add->left = plus;
	}
	return (1);
}

void	incre(char *s, int *i)
{
	ssize_t	l;

	l = str_len(s, *i, 1);
	while (l--)
    	(*i)++;
}

int	choose_str(char c, int flg)
{
	if ((flg && check_token(c, 0) == STR) || (!flg && check_token(c, 0) == STR && !check_spaces(c)))
		return (1);
	else
		return (0);
}

int str_len(char *s, int i, int flg)
{
	int l;
	int keep;

	l = 0;
	while(s[i] && choose_str(s[i], flg))
	{
		if(s[i] == 34 || s[i] == 39)
		{
			keep = check_next_quote(&s[i + 1], s[i]);
			if (keep == -1)
				return (-1);
			l += keep + 1;
			i += keep + 1;
		}
		l++;
		i++;
	}
	if (!flg)
	{
		while (check_spaces(s[i++]))
			l++;
	}
	return (l);
}

int check_next_quote(char *s, char c)
{
	int i;

	i = 0;
	while(*s)
	{
		if (*s == c)
			return(i);
		i++;
		s++;
	}
	printf("syntax error: unclosed quotes");
	return -1;
}

void check_flg(int flg, char *s, int *k)
{
	if(!flg)
		s[(*k) - 1] = 127;
}
char	*cmd_help(char *s, int l, int *k, int flg)
{
	int	i;
	int	j;
	char	*ret;

	ret = malloc(sizeof(char) * (l + 1));
	if (!ret)
		exit(1);
	i = 0;
	while (i < l)
	{
		if (s[*k] == 34 || s[*k] == 39)
		{
			j = check_next_quote(&s[(*k) + 1], s[*k]) + i + 1;
			while (i < j)
			{
				ret[i++] = s[(*k)++];
				check_flg(flg, s, k);
			}
		}
		if (s[*k] == 32)
			s[*k] = 127;
		ret[i++] = s[(*k)++];
		check_flg(flg, s, k);
	}
	return (ret[i] = 0, ret);
}
char **fill_command(char *s, int l, int *k, int flg)
{
	char *prep;
	char **freturn;

	if(l<0)
		return(NULL);
	prep = cmd_help(s, l, k, flg);
	freturn = ft_split(prep, 127);
	free(prep);
	prep = NULL;
	return (freturn);
}
char **prep_cmd(char *s, int *i, s_token tok, int flg)
{
	char **freturn;
	s[*i] = 127;
	(*i)++;
	if(tok == HEREDOC || tok == APPEND)
	{
		s[*i] = 127;
		(*i)++;
	}
	while(check_spaces(s[*i]) == 1)
		(*i)++;
	if(check_syntax(tok, &s[*i]) == 0)
		return NULL;
	freturn = fill_command(s, str_len(s, *i, flg), i, flg);
	return (freturn);
}