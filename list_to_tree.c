#include "minishell.h"

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