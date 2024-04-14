/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:34:51 by ialdidi           #+#    #+#             */
/*   Updated: 2024/04/14 12:16:43 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*previous;
	struct s_list	*next;
}	t_list;

t_list	*lst_last(t_list *lst);
t_list	*lst_new(void *content);
int		lst_size(t_list *lst);
void	lst_addback(t_list **lst, t_list *new);
void	lst_addfront(t_list **lst, t_list *new);
void	lst_delone(t_list *lst, void (*del)(void *));
void	lst_clear(t_list *lst);
void	lst_iter(t_list *lst, void (*f)(void *));

#endif
