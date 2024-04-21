/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:33:48 by ialdidi           #+#    #+#             */
/*   Updated: 2024/04/21 11:37:08 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

int	think(t_philo *philo)
{
	t_object	*obj;

	obj = philo->_parent;
	if (is_ended(obj) == true)
		return (0);
	print_action(philo, THINK);
	if (obj->settings.time_to_think > 0)
		sleeper(obj->settings.time_to_think);
	return (1);
}
