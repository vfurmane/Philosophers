/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 11:28:46 by vfurmane          #+#    #+#             */
/*   Updated: 2021/10/20 10:26:10 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
**	Make a philo try to take forks.
**	@param {t_philo*} philo - The simulated philo.
**	@returns {int} Return 1 on success, 
**	or 0 on death.
*/
int	philo_wants_to_eat(t_philo *philo)
{
	if (philo_take_fork(philo, philo->left_fork) < 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	if (philo_take_fork(philo, philo->right_fork) < 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	philo_start_eating(philo);
	return (1);
}

/*
**	Unlock the mutex (forks) and start sleeping.
**	@param {t_philo*} philo - The simulated philo.
**	@returns {int} Return 1 on success, 
**	or 0 on success, 
**	or -1 on the following errors:
**	 -	The mutex (fork) could not be unlocked;
*/
int	philo_wants_to_sleep(t_philo *philo, bool drop_forks)
{
	if (drop_forks)
	{
		if (pthread_mutex_unlock(philo->left_fork) < 0)
			return (-1);
		if (pthread_mutex_unlock(philo->right_fork) < 0)
			return (-1);
	}
	if (philo_start_sleeping(philo) < 1)
		return (0);
	return (1);
}

/*
**	Check if the passed philo is dead or should die.
**	@param {t_philo*} philo - The simulated philo.
**	@returns {int} Return 1 on sucess, 
**	0 on death, 
**	or -1 on the following errors:
**	 -	The actual time could not be retrieved;
**	 -	The mutex (fork) could not be locked.
*/
bool	philo_is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->config->death_occured.mutex);
	if (philo->config->death_occured.data.boolean)
	{
		pthread_mutex_unlock(philo->config->death_occured.mutex);
		return (true);
	}
	pthread_mutex_unlock(philo->config->death_occured.mutex);
	pthread_mutex_lock(philo->last_eat_time.mutex);
	if (time_since_start(&philo->config->start_time)
		>= philo->last_eat_time.data.uint32 + philo->config->time_to_die)
	{
		pthread_mutex_unlock(philo->last_eat_time.mutex);
		return (true);
	}
	pthread_mutex_unlock(philo->last_eat_time.mutex);
	return (false);
}
