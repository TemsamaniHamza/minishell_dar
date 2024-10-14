/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htemsama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 20:34:51 by htemsama          #+#    #+#             */
/*   Updated: 2023/11/19 20:34:53 by htemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*bullst;

	if (!lst || !del)
		return ;
	while (*lst != NULL)
	{
		bullst = *lst;
		*lst = (*lst)->next;
		del(bullst->content);
		free(bullst);
	}
	*lst = NULL;
}
