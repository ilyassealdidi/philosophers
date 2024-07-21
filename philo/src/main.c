/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:21:01 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/21 03:50:28 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	main(int ac, char *av[])
{
	t_object	obj;

	if (ac < 5 || ac > 6)
		return (print_error(FORMAT_ERROR), EXIT_FAILURE);
	obj = (t_object){0};
	if (settings_init(&obj.settings, av + 1) == 0)
		return (print_error(INVALID_INPUT), EXIT_FAILURE);
	if (obj.settings.num_of_meals == 0)
		return (EXIT_SUCCESS);
	if (pthread_mutex_init(&obj.obj_lock, NULL) != 0
		|| pthread_mutex_init(&obj.print_lock, NULL) != 0
		|| pthread_mutex_init(&obj.meals_lock, NULL) != 0)
		return (EXIT_FAILURE);
	if (philos_init(&obj) == 0)
		return (EXIT_FAILURE);
	monitoring(&obj);
	return (EXIT_SUCCESS);
}
