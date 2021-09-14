/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 14:00:14 by vfurmane          #+#    #+#             */
/*   Updated: 2021/09/13 10:25:22 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
**	The routine executed in the thread.
**	@param {t_philo*} philo - The simulated philosopher.
**	@returns {void*} Return nothing.
*/
void	*simulate_philo_life(t_philo *philo)
{
	while (true)
	{
		if (philo->state == PHILO_NOTHING
			|| philo->state == PHILO_THINKING)
			philo_wants_to_eat(philo);
		else if (philo->state == PHILO_EATING)
		{
			philo_wants_to_sleep(philo);
		}
		else if (philo->state == PHILO_SLEEPING)
			philo_start_thinking(philo);
	}
	pthread_exit(NULL);
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
**	@param {t_philo_config*} config - Th configuration of the simulation.
**	@returns {t_philo*} Return an array of philos on success, 
**	or NULL on the following errors:
**	 -	The time of day could not be retrieved;
**	 -	The mutex (forks_lock) could not be initialized;
**	 -	The allocation of philos array has failed;
**	 -	The distribution of forks has failed;
*/
static t_philo	*setup_simulation(t_philo_config *config)
{
	uint32_t	i;
	t_philo		*philos;

	if (gettimeofday(&config->start_time, NULL) < 0)
		return (NULL);
	if (pthread_mutex_init(&config->forks_lock, NULL) != 0)
		return (NULL);
	philos = malloc(config->philos_no * sizeof (*philos));
	if (philos == NULL)
		return (NULL);
	i = 0;
	while (i < config->philos_no)
	{
		philos[i].id = i + 1;
		philos[i].state = PHILO_NOTHING;
		philos[i].start_time = &config->start_time;
		philos[i].forks_lock = &config->forks_lock;
		if (share_forks(config->philos_no, philos, i) < 0)
			return (NULL);
		i++;
	}
	return (philos);
}

static int	teardown_simulation(t_philo_config *config, t_philo *philos)
{
	uint32_t	i;

	i = 0;
	while (i < config->philos_no)
	{
		pthread_join(philos[i].thread, NULL);
		if (pthread_mutex_destroy(philos[i].left_fork) != 0)
			return (-1);
		if (pthread_mutex_destroy(philos[i].right_fork) != 0)
			return (-1);
		i++;
	}
	pthread_mutex_destroy(&config->forks_lock);
	free(philos);
	return (0);
}

/*
**	Start the simulation.
**	@param {t_philo_config*} config - Th configuration of the simulation.
**	@returns {int} Return 0 on success, 
**	or 1 on the following errors:
**	 -	The simulation setup has failed;
**	 -	The thread creation has failed;
**	 -	The simulation teardown has failed;
*/
int	simulation(t_philo_config *config)
{
	uint32_t	i;
	t_philo		*philos;

	philos = setup_simulation(config);
	if (philos == NULL)
		return (1);
	i = 0;
	while (i < config->philos_no)
	{
		if (pthread_create(&philos[i].thread, NULL,
			(void *(*)(void *))simulate_philo_life, &philos[i]) != 0)
			return (1);
		i++;
	}
	if (teardown_simulation(config, philos) < 0)
		return (1);
	return (0);
}
