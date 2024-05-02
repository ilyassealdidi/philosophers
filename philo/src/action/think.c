/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:33:48 by ialdidi           #+#    #+#             */
/*   Updated: 2024/05/02 09:22:23 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philosophers.h"

int	think(t_philo *philo)
{
	if (is_ended(philo->_parent))
		return (0);
	print_action(philo, THINK);
	return (1);
}
