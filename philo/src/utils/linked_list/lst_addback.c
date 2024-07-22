/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_addback.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:38:51 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/23 00:27:15 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	lst_addback(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		(*lst)->next = new;
		(*lst)->previous = new;
	}
	else
	{
		last = lst_last(*lst);
		last->next = new;
		(*lst)->previous = new;
		new->next = *lst;
		new->previous = last;
	}
}
