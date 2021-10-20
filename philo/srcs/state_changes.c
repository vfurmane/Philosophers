/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_changes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 14:01:56 by vfurmane          #+#    #+#             */
/*   Updated: 2021/10/20 10:43:50 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
**	Lock the mutex (forks).
**	@param {t_philo*} philo - The simulated philo.
**	@param {pthread_mutex_t*} fork - The mutex (fork) to lock.
**	@returns {int} Return 1 on sucess, 
**	0 on death, 
**	or -1 on the following errors:
**	 -	The actual time could not be retrieved;
**	 -	The mutex (fork) could not be locked.
*/
int	philo_take_fork(t_philo *philo, pthread_mutex_t *fork)
{
	long	timestamps;

	if (philo->state.data.state == PHILO_DEAD)
		return (0);
	if (pthread_mutex_lock(fork) != 0)
		return (-1);
	timestamps = time_since_start(&philo->config->start_time);
	if (timestamps == -1)
		return (-1);
	pthread_mutex_lock(philo->state.mutex);
	if (philo_is_dead(philo))
	{
		pthread_mutex_unlock(philo->state.mutex);
		return (0);
	}
	if (simulation_continues(philo))
		printf("%ld %d has taken a fork\n", timestamps, philo->id);
	pthread_mutex_unlock(philo->state.mutex);
	return (1);
}

/*
**	Change philo's state to EATING and log it.
**	@param {t_philo*} philo - The simulated philo.
**	@returns {int} Return 1 on sucess, 
**	0 on death, 
**	or -1 on the following errors:
**	 -	The actual time could not be retrieved;
*/
int	philo_start_eating(t_philo *philo)
{
	long	timestamps;

	if (philo->state.data.state == PHILO_DEAD)
		return (0);
	timestamps = time_since_start(&philo->config->start_time);
	if (timestamps == -1)
		return (-1);
	pthread_mutex_lock(philo->last_eat_time.mutex);
	philo->last_eat_time.data.uint32 = timestamps;
	pthread_mutex_unlock(philo->last_eat_time.mutex);
	pthread_mutex_lock(philo->state.mutex);
	philo->state.data.state = PHILO_EATING;
	if (simulation_continues(philo))
	{
		if (!philo->config->death_occured.data.boolean)
			printf("%ld %d is eating\n", timestamps, philo->id);
		philo->meals_no.data.uint32++;
		pthread_mutex_lock(philo->config->meals_target.mutex);
		if (philo->meals_no.data.uint32 == philo->config->min_eat_no)
			philo->config->meals_target.data.uint32++;
		pthread_mutex_unlock(philo->config->meals_target.mutex);
	}
	pthread_mutex_unlock(philo->state.mutex);
	return (1);
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

	if (philo->state.data.state == PHILO_DEAD)
		return (0);
	timestamps = time_since_start(&philo->config->start_time);
	if (timestamps == -1)
		return (-1);
	pthread_mutex_lock(philo->state.mutex);
	philo->state.data.state = PHILO_SLEEPING;
	if (simulation_continues(philo)
		&& !philo->config->death_occured.data.boolean)
		printf("%ld %d is sleeping\n", timestamps, philo->id);
	pthread_mutex_unlock(philo->state.mutex);
	return (1);
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

	if (philo->state.data.state == PHILO_DEAD)
		return (0);
	timestamps = time_since_start(&philo->config->start_time);
	if (timestamps == -1)
		return (-1);
	pthread_mutex_lock(philo->state.mutex);
	philo->state.data.state = PHILO_THINKING;
	if (simulation_continues(philo)
		&& !philo->config->death_occured.data.boolean)
		printf("%ld %d is thinking\n", timestamps, philo->id);
	pthread_mutex_unlock(philo->state.mutex);
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

	if (philo->state.data.state == PHILO_DEAD)
		return (0);
	timestamps = time_since_start(&philo->config->start_time);
	if (timestamps == -1)
		return (-1);
	pthread_mutex_lock(philo->state.mutex);
	philo->state.data.state = PHILO_DEAD;
	pthread_mutex_lock(philo->config->death_occured.mutex);
	if (!philo->config->end_of_simulation.data.boolean)
	{
		printf("%ld %d died\n", timestamps, philo->id);
		philo->config->death_occured.data.boolean = true;
	}
	philo->config->end_of_simulation.data.boolean = true;
	pthread_mutex_unlock(philo->config->death_occured.mutex);
	pthread_mutex_unlock(philo->state.mutex);
	return (0);
}
