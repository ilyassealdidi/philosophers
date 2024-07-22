/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_addfront.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:39:05 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/23 00:27:43 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	lst_addfront(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	lst_addback(lst, new);
	*lst = new;
}
