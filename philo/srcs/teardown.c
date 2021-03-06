/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teardown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:14:54 by vfurmane          #+#    #+#             */
/*   Updated: 2021/10/20 13:34:29 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
**	Free the philosophers.
**	@param {t_philo_config*} config - The configuration of the simulation.
**	@param {t_philo*} philo - The array of philos.
**	@returns {int} Return 0 on success, 
**	or -1 on the following errors:
**	 -	The mutex (fork) could not be destroyed;
**	 -	The mutex (forks_lock) could not be destroyed;
*/
static int	free_philos(t_philo_config *config, t_philo *philos)
{
	uint32_t	i;

	i = 0;
	while (i < config->philos_no)
	{
		if (pthread_mutex_destroy(philos[i].last_eat_time.mutex) != 0)
			return (-1);
		free(philos[i].last_eat_time.mutex);
		if (pthread_mutex_destroy(philos[i].left_fork) != 0)
			return (-1);
		if (pthread_mutex_destroy(philos[i].meals_no.mutex) != 0)
			return (-1);
		free(philos[i].meals_no.mutex);
		free(philos[i].left_fork);
		i++;
	}
	return (0);
}

/*
*/
int	free_mutexes(t_philo_config *config)
{
	if (pthread_mutex_destroy(&config->forks_lock) != 0)
		return (-1);
	if (pthread_mutex_destroy(config->death_occured.mutex) != 0)
		return (-1);
	if (pthread_mutex_destroy(config->end_of_simulation.mutex) != 0)
		return (-1);
	free(config->meals_target.mutex);
	free(config->end_of_simulation.mutex);
	free(config->death_occured.mutex);
	return (0);
}

/*
**	Teardown the philosophers.
**	@param {t_philo_config*} config - The configuration of the simulation.
**	@param {t_philo*} philo - The array of philos.
**	@returns {int} Return 0 on success, 
**	or -1 on the following errors:
**	 -	The thread could not be joined;
**	 -	The mutex (fork) could not be destroyed;
**	 -	The mutex (forks_lock) could not be destroyed;
*/
int	teardown_simulation(t_philo_config *config, t_philo *philos)
{
	uint32_t	i;

	i = 0;
	while (i < config->philos_no)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
	if (free_philos(config, philos) == -1)
		return (-1);
	if (free_mutexes(config) != 0)
		return (-1);
	free(philos);
	return (0);
}
