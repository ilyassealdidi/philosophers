/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:21:01 by ialdidi           #+#    #+#             */
/*   Updated: 2024/05/04 11:33:12 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int ac, char *av[])
{
	t_object	obj;

	if (ac < 5 || ac > 6)
		return (printf(FORMAT_ERROR), EXIT_FAILURE);
	memset(&obj, 0, sizeof(t_object));
	if (settings_init(&obj.settings, av + 1) == 0)
		return (printf("Invalid Input\n"), EXIT_FAILURE);
	if (obj.settings.num_of_meals == 0)
		return (EXIT_SUCCESS);
	if (philos_init(&obj) == 0)
		return (EXIT_FAILURE);
	monitoring(&obj);
	return (EXIT_SUCCESS);
}
