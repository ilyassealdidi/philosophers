/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:33:32 by ialdidi           #+#    #+#             */
/*   Updated: 2024/04/21 11:36:46 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

int	bedtime(t_philo *philo)
{
	if (is_ended(philo->_parent) == true)
		return (0);
	print_action(philo, SLEEP);
	sleeper(philo->_parent->settings.time_to_sleep);
	return (1);
}
