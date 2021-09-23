/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 11:28:46 by vfurmane          #+#    #+#             */
/*   Updated: 2021/09/23 13:22:36 by vfurmane         ###   ########.fr       */
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
	if (pthread_mutex_lock(&philo->config->forks_lock) != 0)
		return ;
	if (philo->left_fork->is_locked == 0
		&& philo->right_fork->is_locked == 0)
	{
		if (philo_take_fork(philo, philo->left_fork) < 0)
			return ;
		if (philo_take_fork(philo, philo->right_fork) < 0)
			return ;
		philo_start_eating(philo);
	}
	else if (philo->state == PHILO_NOTHING)
		philo_start_thinking(philo);
	pthread_mutex_unlock(&philo->config->forks_lock);
}

/*
**	Unlock the mutex (forks) and start sleeping.
**	@param {t_philo*} philo - The simulated philo.
**	@returns {int} Return 0 on success, 
**	or -1 on the following errors:
**	 -	The mutex (fork) could not be unlocked;
*/
int	philo_wants_to_sleep(t_philo *philo)
{
	if (pthread_mutex_unlock(&philo->left_fork->lock) < 0)
		return (-1);
	philo->left_fork->is_locked = false;
	if (pthread_mutex_unlock(&philo->right_fork->lock) < 0)
		return (-1);
	philo->right_fork->is_locked = false;
	philo_start_sleeping(philo);
	return (0);
}
