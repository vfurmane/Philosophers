/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:07:12 by vfurmane          #+#    #+#             */
/*   Updated: 2021/10/19 16:31:14 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
*/
t_philo	*malloc_config(t_philo_config *config)
{
	t_philo	*philos;

	config->meals_target.mutex = malloc(sizeof (*config->meals_target.mutex));
	if (config->meals_target.mutex == NULL)
		return (NULL);
	config->end_of_simulation.mutex
		= malloc(sizeof (*config->end_of_simulation.mutex));
	if (config->end_of_simulation.mutex == NULL)
		return (NULL);
	config->death_occured.mutex = malloc(sizeof (*config->death_occured.mutex));
	if (config->death_occured.mutex == NULL)
		return (NULL);
	philos = malloc(config->philos_no * sizeof (*philos));
	if (philos == NULL)
		return (NULL);
	return (philos);
}

/*
**	Set config variables.
**	@param {t_philo_config *} config - The simulation configuration.
**	@returns {t_philo *} Return the philos array on success, 
**	or NULL on errors.
*/
t_philo	*config_simulation(t_philo_config *config)
{
	t_philo	*philos;

	philos = malloc_config(config);
	if (gettimeofday(&config->start_time, NULL) < 0)
		return (NULL);
	if (pthread_mutex_init(&config->forks_lock, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&config->death_lock, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(config->meals_target.mutex, NULL) != 0)
		return (NULL);
	config->meals_target.data.uint32 = 0;
	if (pthread_mutex_init(config->end_of_simulation.mutex, NULL) != 0)
		return (NULL);
	config->end_of_simulation.data.boolean = false;
	if (pthread_mutex_init(config->death_occured.mutex, NULL) != 0)
		return (NULL);
	config->death_occured.data.boolean = false;
	return (philos);
}

/*
**	Set philo variables.
**	@param {t_philo_config *} config - The simulation configuration.
**	@param {t_philo *} philo - The philo to configurate.
**	@returns {int} Return 0 on success, 
**	or -1 on the following errors:
**	 -	The allocation of the state's data fails;
**	 -	The allocation of the last eat time mutex fails;
**	 -	The initialization of the last eat time mutex fails;
**	 -	The allocation of the last eat time data fails;
*/
int	config_philo(t_philo_config *config, t_philo *philo)
{
	philo->state.mutex = &config->death_lock;
	philo->state.data.state = PHILO_NOTHING;
	philo->meals_no.mutex = malloc(sizeof (*philo->meals_no.mutex));
	if (philo->meals_no.mutex == NULL)
		return (-1);
	if (pthread_mutex_init(philo->meals_no.mutex, NULL) != 0)
		return (-1);
	philo->meals_no.data.uint32 = 0;
	philo->last_eat_time.mutex = malloc(sizeof (*philo->last_eat_time.mutex));
	if (philo->last_eat_time.mutex == NULL)
		return (-1);
	if (pthread_mutex_init(philo->last_eat_time.mutex, NULL) != 0)
		return (-1);
	philo->last_eat_time.data.uint32 = 0;
	philo->config = config;
	return (0);
}

/*
**	Share a fork between two philosophers.
**	@param {uint32_t} philos_no - Total number of philos;
**	@param {t_philo*} philos - Array of philos;
**	@param {uint32_t} i - The philo to give the fork to;
**	@returns {int} Return 0 on sucess, 
**	or -1 on the following errors:
**	 -	The allocation of the fork failed;
**	 -	The mutex (fork) could not be initialized;
*/
int	share_forks(uint32_t philos_no, t_philo *philos, uint32_t i)
{
	if (i == 0)
	{
		philos[i].left_fork = malloc(sizeof (*philos[i].left_fork));
		if (philos[i].left_fork == NULL)
			return (-1);
		if (pthread_mutex_init(philos[i].left_fork, NULL) != 0)
			return (-1);
	}
	else
		philos[i].left_fork = philos[i - 1].right_fork;
	if (i != philos_no - 1)
	{
		philos[i].right_fork = malloc(sizeof (*philos[i].right_fork));
		if (philos[i].right_fork == NULL)
			return (-1);
		if (pthread_mutex_init(philos[i].right_fork, NULL) != 0)
			return (-1);
	}
	else
		philos[i].right_fork = philos[0].left_fork;
	return (0);
}

/*
**	Setup the philosophers for the simulation.
**	@param {t_philo_config*} config - The configuration of the simulation.
**	@returns {t_philo*} Return an array of philos on success, 
**	or NULL on the following errors:
**	 -	The time of day could not be retrieved;
**	 -	The mutex (forks_lock) could not be initialized;
**	 -	The allocation of philos array has failed;
**	 -	The distribution of forks has failed;
*/
t_philo	*setup_simulation(t_philo_config *config)
{
	uint32_t	i;
	t_philo		*philos;

	philos = config_simulation(config);
	if (philos == NULL)
		return (NULL);
	i = 0;
	while (i < config->philos_no)
	{
		philos[i].id = i + 1;
		config_philo(config, &philos[i]);
		if (share_forks(config->philos_no, philos, i) < 0)
			return (NULL);
		i++;
	}
	return (philos);
}
