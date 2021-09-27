/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_changes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 14:01:56 by vfurmane          #+#    #+#             */
/*   Updated: 2021/09/27 12:08:59 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

	if (philo->state == PHILO_DEAD)
		return (0);
	timestamps = time_since_start(&philo->config->start_time);
	if (timestamps == -1)
		return (-1);
	if (pthread_mutex_lock(&fork->lock) != 0)
		return (-1);
	fork->is_locked = true;
	pthread_mutex_lock(&philo->config->death_lock);
	if (!philo->config->death_occured)
		printf("%ld %d has taken a fork\n", timestamps, philo->id);
	pthread_mutex_unlock(&philo->config->death_lock);
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

	if (philo->state == PHILO_DEAD)
		return (0);
	timestamps = time_since_start(&philo->config->start_time);
	if (timestamps == -1)
		return (-1);
	philo->state = PHILO_EATING;
	philo->last_eat_time = timestamps;
	pthread_mutex_lock(&philo->config->death_lock);
	if (!philo->config->death_occured)
		printf("%ld %d is eating\n", timestamps, philo->id);
	pthread_mutex_unlock(&philo->config->death_lock);
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

	if (philo->state == PHILO_DEAD)
		return (0);
	timestamps = time_since_start(&philo->config->start_time);
	if (timestamps == -1)
		return (-1);
	philo->state = PHILO_SLEEPING;
	pthread_mutex_lock(&philo->config->death_lock);
	if (!philo->config->death_occured)
		printf("%ld %d is sleeping\n", timestamps, philo->id);
	pthread_mutex_unlock(&philo->config->death_lock);
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

	if (philo->state == PHILO_DEAD)
		return (0);
	timestamps = time_since_start(&philo->config->start_time);
	if (timestamps == -1)
		return (-1);
	philo->state = PHILO_THINKING;
	pthread_mutex_lock(&philo->config->death_lock);
	if (!philo->config->death_occured)
		printf("%ld %d is thinking\n", timestamps, philo->id);
	pthread_mutex_unlock(&philo->config->death_lock);
	return (0);
}

/*
**	Change philo's state to DEAD and log it.
**	@param {t_philo*} philo - The simulated philo.
**	@returns {int} Return 0 on success, 
**	or -1 on the following errors:
**	 -	The actual time could not be retrieved;
*/
int	philo_dies(t_philo *philo)
{
	long	timestamps;

	if (philo->state == PHILO_DEAD)
		return (0);
	timestamps = time_since_start(&philo->config->start_time);
	if (timestamps == -1)
		return (-1);
	philo->state = PHILO_DEAD;
	pthread_mutex_lock(&philo->config->death_lock);
	if (!philo->config->death_occured)
		printf("%ld %d died\n", timestamps, philo->id);
	philo->config->death_occured = true;
	pthread_mutex_unlock(&philo->config->death_lock);
	return (0);
}
