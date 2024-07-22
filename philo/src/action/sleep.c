/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:33:32 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/22 09:24:05 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	bedtime(t_philo *philo)
{
	t_object	*obj;

	obj = philo->_parent;
	if (is_ended(philo->_parent))
		return (0);
	print_action(philo, SLEEP);
	sleeper(philo->_parent, philo->_parent->settings.time_to_sleep);
	return (1);
}
