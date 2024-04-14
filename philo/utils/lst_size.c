/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:34:27 by ialdidi           #+#    #+#             */
/*   Updated: 2024/04/12 17:17:26 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

int	lst_size(t_list *lst)
{
	t_list	*head;
	int		length;

	if (!lst)
		return (0);
	length = 0;
	head = lst;
	while (1)
	{
		length++;
		if (lst->next == head)
			return (length);
	}
}
