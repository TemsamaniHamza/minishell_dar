#include "minishell.h"

s_token	check_token(char c1, char c2)
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

    tok = check_token(str[0], str[1]);
    if(tok == OR || tok == AND || tok == PIPE || tok == RPR)
    {
        printf("synsttax ghalat file [minishell.c] line x");
        return(0);
    }
    return(1);
}

void	pop(s_input **tok_s)
{
	if (!(*tok_s)->right)
	{
		free(*tok_s);
		*tok_s = NULL;
	}
	else
	{
		*tok_s = (*tok_s)->right;
		free((*tok_s)->left);
		(*tok_s)->left = NULL;
	}
}

void	shunting_yard(s_input **head, s_input **tok_stack,
s_input **new_stack)
{
	while (*head)
	{
		if ((*head)->tok == STR)
			push(head, new_stack, 0);
		else if ((*head)->tok != LPR && (*head)->tok != RPR)
		{
			while (*tok_stack && (*tok_stack)->token_flag
				>= (*head)->token_flag)
				push(tok_stack, new_stack, 0);
			push(head, tok_stack, 1);
		}
		else if ((*head)->tok == LPR)
			push(head, tok_stack, 1);
		else if ((*head)->tok == RPR)
		{
			pop(head);
			while ((*tok_stack)->tok != LPR)
				push(tok_stack, new_stack, 0);
			pop(tok_stack);
		}
	}
}
void	push_2(s_input **top, s_input *to_add)
{
	if (!to_add)
		return ;
	else if (!*top)
		*top = to_add;
	else
	{
		(*top)->left = to_add;
		to_add->right = *top;
		*top = to_add;
	}
}
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

void	push(s_input **a_head, s_input **b_head, int flg)
{
	s_input	*sep;

	if (!a_head || !(*a_head))
		return ;
	sep = *a_head;
	*a_head = (*a_head)->right;
	sep->right = NULL;
	if (*a_head)
		(*a_head)->left = NULL;
	if (flg)
		push_2(b_head, sep);
	else
		build_command_list(b_head, sep);
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

s_input	*list_to_tree(s_input *root)
{
	if (!root)
		return (NULL);
	if (root->tok != STR)
	{
		root->right = list_to_tree(root->left);
		root->left = list_to_tree(root->left);
	}
	if (root->tok == STR)
	{
		if (root->left && root->right)
		{
			root->left->right = root->right;
			root->right->left = root->left;
			if (root->right->right)
				root->left->right = root->right->right;
		}
		root->right = NULL;
		root->left = NULL;
	}
	return (root);
}

s_input *parsing(char *rl)
{
    char *str;
    s_input *head;

    str = ft_strtrim(rl, " \t\n\v\f\r");
    free(rl);
    if(!str || !check_beggining_of_str(str))
        return (free(str), NULL);
    head = my_Tokenizer(str);
	if(!head)
		return (NULL);
	head = re_order_command(&head);
	while (head->right)
		head = head->right;
	head = list_to_tree(head);
	return (head);
}
int	check_true(s_token tok)
{
	if (tok == STR || tok == IN || tok == OUT || tok == APPEND || tok == HEREDOC)
		return (1);
	else
		return (0);
}

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
/***** hadi gha l print dyal tree *********/
const char *token_to_string(s_token tok) {
    switch (tok) {
        case IN:      return "<";
        case OUT:     return ">";
        case HEREDOC: return "<<";
        case APPEND:  return ">>";
        case AND:     return "&&";
        case PIPE:    return "|";
        case OR:      return "||";
        case LPR:     return "(";
        case RPR:     return ")";
        case STR:     return "STRING"; // You may want to represent actual strings instead
        case END:     return "END";
        default:      return "UNKNOWN";
    }
}
/***** hadi gha l print dyal tree *********/

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
    }
	return 0;
}