/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:21:01 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/14 04:30:37 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	main(int ac, char *av[])
{
	t_object	obj;

	if (ac < 5 || ac > 6)
		return (printf(FORMAT_ERROR), EXIT_FAILURE);
	obj = (t_object){0};
	if (settings_init(&obj.settings, av + 1) == 0)
	{
		printf("Invalid Input\n");
		return (EXIT_FAILURE);
	}
	if (obj.settings.num_of_meals == 0)
		return (EXIT_SUCCESS);
	if (pthread_mutex_init(&obj.obj_lock, NULL) != 0)
		return (EXIT_FAILURE);
	if (philos_init(&obj) == 0)
		return (EXIT_FAILURE);
	monitoring(&obj);
	return (EXIT_SUCCESS);
}
