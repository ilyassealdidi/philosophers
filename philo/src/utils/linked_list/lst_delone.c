/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_delone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:39:22 by ialdidi           #+#    #+#             */
/*   Updated: 2024/05/15 08:20:23 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

void	lst_delone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
