/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:38:33 by ialdidi           #+#    #+#             */
/*   Updated: 2024/04/12 17:17:26 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

void	lst_clear(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return ;
	lst_last(lst)->next = NULL;
	while (lst)
	{
		tmp = lst->next;
		lst_delone(lst, free);
		lst = tmp;
	}
}
