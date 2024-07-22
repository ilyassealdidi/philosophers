/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:33:48 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/21 05:01:39 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	think(t_philo *philo)
{
	if (is_ended(philo->_parent))
		return (0);
	print_action(philo, THINK);
	return (1);
}
