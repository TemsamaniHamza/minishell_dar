#include "minishell.h"

void	shunting_yard(s_input **head, s_input **tok_stack, s_input **new_stack)
{
	while (*head)
	{
		if ((*head)->tok == STR)
			push(head, new_stack, 0);
		else if ((*head)->tok != LPR && (*head)->tok != RPR)
		{
			while (*tok_stack && (*tok_stack)->token_flag >= (*head)->token_flag)
				push(tok_stack, new_stack, 0);
			push(head, tok_stack, 1);
		}
		else if ((*head)->tok == LPR)
			push(head, tok_stack, 1);
		else if ((*head)->tok == RPR)
		{
			remove_top(head);
			while ((*tok_stack)->tok != LPR)
				push(tok_stack, new_stack, 0);
			remove_top(tok_stack);
		}
	}
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
	if (flg == 1)
		push_2(b_head, sep);
	else
		build_command_list(b_head, sep);
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

void	remove_top(s_input **tok_s)
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

