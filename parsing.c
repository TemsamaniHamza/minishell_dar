#include "minishell.h"

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