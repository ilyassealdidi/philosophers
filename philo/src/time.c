/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:23:23 by ialdidi           #+#    #+#             */
/*   Updated: 2024/05/02 08:52:24 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	sleeper(long time)
{
	long	start;

	start = get_current_time();
	while (get_current_time() - start < time)
		usleep(500);
}
