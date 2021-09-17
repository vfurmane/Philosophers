/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_changes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 14:01:56 by vfurmane          #+#    #+#             */
/*   Updated: 2021/09/08 16:44:29 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
**	Compute the time since the start of the simulation.
**	@param {struct timeval *} start_time - The time of the simulation starting.
**	@returns {long} Return the time since the start of the simulation, 
**	or -1 on the following errors:
**	 -	The time actual time could not be retrieved;
*/
static long	time_since_start(struct timeval *start_time)
{
	long			timestamps;
	struct timeval	time_now;

	if (gettimeofday(&time_now, NULL) < 0)
		return (-1);
	timestamps = (time_now.tv_usec - start_time->tv_usec) / 1000;
	timestamps += (time_now.tv_sec - start_time->tv_sec) * 1000;
	return (timestamps);
}

/*
**	Lock the mutex (forks).
**	@param {t_philo*} philo - The simulated philo.
**	@param {pthread_mutex_t*} fork - The mutex (fork) to lock.
**	@returns {int} Return 0 on sucess, 
**	or -1 on the following errors:
**	 -	The actual time could not be retrieved;
**	 -	The mutex (fork) could not be locked.
*/
int	philo_take_fork(t_philo *philo, t_fork *fork)
{
	long	timestamps;

	timestamps = time_since_start(philo->start_time);
	if (timestamps == -1)
		return (-1);
	if (pthread_mutex_lock(&fork->lock) != 0)
		return (-1);
	fork->is_locked = true;
	printf("%-20ld %-10d has taken a fork\n", timestamps, philo->id);
	return (0);
}

/*
**	Change philo's state to EATING and log it.
**	@param {t_philo*} philo - The simulated philo.
**	@returns {int} Return 0 on success, 
**	or -1 on the following errors:
**	 -	The actual time could not be retrieved;
*/
int	philo_start_eating(t_philo *philo)
{
	long	timestamps;

	timestamps = time_since_start(philo->start_time);
	if (timestamps == -1)
		return (-1);
	philo->state = PHILO_EATING;
	printf("%-20ld %-10d is eating\n", timestamps, philo->id);
	return (0);
}

/*
**	Change philo's state to THINKING and log it.
**	@param {t_philo*} philo - The simulated philo.
**	@returns {int} Return 0 on success, 
**	or -1 on the following errors:
**	 -	The actual time could not be retrieved;
*/
int	philo_start_sleeping(t_philo *philo)
{
	long	timestamps;

	timestamps = time_since_start(philo->start_time);
	if (timestamps == -1)
		return (-1);
	philo->state = PHILO_SLEEPING;
	printf("%-20ld %-10d is sleeping\n", timestamps, philo->id);
	return (0);
}

/*
**	Change philo's state to THINKING and log it.
**	@param {t_philo*} philo - The simulated philo.
**	@returns {int} Return 0 on success, 
**	or -1 on the following errors:
**	 -	The actual time could not be retrieved;
*/
int	philo_start_thinking(t_philo *philo)
{
	long	timestamps;

	timestamps = time_since_start(philo->start_time);
	if (timestamps == -1)
		return (-1);
	philo->state = PHILO_THINKING;
	printf("%-20ld %-10d is thinking\n", timestamps, philo->id);
	return (0);
}
