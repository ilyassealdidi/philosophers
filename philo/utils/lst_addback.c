/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_addback.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:38:51 by ialdidi           #+#    #+#             */
/*   Updated: 2024/04/12 17:17:26 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

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
