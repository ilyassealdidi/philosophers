/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 01:21:47 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/23 00:39:12 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	create_thread(t_thread *thread, void *(*routine)(void *), void *arg)
{
	if (pthread_create(&thread->thread, NULL, routine, arg) != 0)
		return (print_error(THREAD_CREATE_ERROR), 0);
	thread->is_initialized = true;
	return (1);
}

void	join_thread(t_thread *thread)
{
	if (thread->is_initialized)
		pthread_join(thread->thread, NULL);
	thread->is_initialized = false;
}

void	detach_thread(t_thread *thread)
{
	if (thread->is_initialized)
		pthread_detach(thread->thread);
	thread->is_initialized = false;
}
