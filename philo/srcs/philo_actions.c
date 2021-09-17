/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 11:28:46 by vfurmane          #+#    #+#             */
/*   Updated: 2021/09/11 11:35:00 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
**	Make a philo try to take forks.
**	@param {t_philo*} philo - The simulated philo.
**	@returns {void}
*/
void	philo_wants_to_eat(t_philo *philo)
{
	if (pthread_mutex_lock(philo->forks_lock) != 0)
		pthread_exit(NULL);
	if (philo->left_fork->is_locked == 0
		&& philo->right_fork->is_locked == 0)
	{
		if (philo_take_fork(philo, philo->left_fork) < 0)
			pthread_exit(NULL);
		if (philo_take_fork(philo, philo->right_fork) < 0)
			pthread_exit(NULL);
		philo_start_eating(philo);
	}
	else if (philo->state == PHILO_NOTHING)
		philo_start_thinking(philo);
	pthread_mutex_unlock(philo->forks_lock);
}

/*
**	Unlock the mutex (forks) and start sleeping.
**	@param {t_philo*} philo - The simulated philo.
**	@returns {void}
*/
void	philo_wants_to_sleep(t_philo *philo)
{
	if (pthread_mutex_unlock(&philo->left_fork->lock) < 0)
		pthread_exit(NULL);
	philo->left_fork->is_locked = false;
	if (pthread_mutex_unlock(&philo->right_fork->lock) < 0)
		pthread_exit(NULL);
	philo->right_fork->is_locked = false;
	philo_start_sleeping(philo);
}
