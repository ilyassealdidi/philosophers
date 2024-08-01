/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 01:21:47 by ialdidi           #+#    #+#             */
/*   Updated: 2024/08/01 08:21:03 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

/**
 * Creates a new thread.
 *
 * @param thread   A pointer to the t_thread structure to be initialized.
 * @param routine  A pointer to the function that will be executed by the new
 * thread.
 * @param arg      An argument to be passed to the function.
 *
 * @return         1 if the thread is successfully created and initialized,
 * 0 otherwise.
 */
int	create_thread(t_thread *thread, void *(*routine)(void *), void *arg)
{
	if (pthread_create(&thread->thread, NULL, routine, arg) != 0)
		return (print_error(THREAD_CREATE_ERROR), 0);
	thread->is_initialized = true;
	return (1);
}

/**
 * Joins a thread.
 *
 * This function waits for the specified thread to terminate and cleans up
 * any resources associated with it.
 *
 * @param thread The thread to join.
 */
void	join_thread(t_thread *thread)
{
	if (thread->is_initialized)
		pthread_join(thread->thread, NULL);
	thread->is_initialized = false;
}

/**
 * Detaches a thread.
 *
 * This function detaches the specified thread. If the thread is already
 * initialized, it will be detached using the pthread_detach function.
 *
 * @param thread The thread to detach.
 */
void	detach_thread(t_thread *thread)
{
	if (thread->is_initialized)
		pthread_detach(thread->thread);
	thread->is_initialized = false;
}
