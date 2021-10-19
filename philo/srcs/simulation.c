/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 14:00:14 by vfurmane          #+#    #+#             */
/*   Updated: 2021/10/19 15:29:25 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
**	Make philo start eating or sleeping.
**	@param {t_philo *} philo - The simulated philo.
**	@returns {int} Return 1 on success, 
**	or 0 on death.
*/
int	start_philo_life(t_philo *philo)
{
	if (philo->id % 2 == 1)
		return (philo_wants_to_eat(philo));
	else if (philo->id % 2 == 0)
		return (philo_wants_to_sleep(philo, false));
	return (1);
}

/*
**	Route philo to the right state. 
**	@param {t_philo *} philo - The simulated philo.
**	@returns {int} Return 1 on success, 
**	or 0 on death.
*/
int	route_philo_life(t_philo *philo)
{
	if (philo->state.data.state == PHILO_NOTHING)
	{
		if (start_philo_life(philo) < 1)
			return (0);
	}
	else if (philo->state.data.state == PHILO_THINKING)
	{
		if (philo_wants_to_eat(philo) < 1)
			return (0);
	}
	else if (philo->state.data.state == PHILO_EATING)
	{
		if (wait_time(philo, philo->config->time_to_eat) < 1)
			return (0);
		if (philo_wants_to_sleep(philo, true) < 1)
			return (0);
	}
	else if (philo->state.data.state == PHILO_SLEEPING)
	{
		if (wait_time(philo, philo->config->time_to_sleep) < 1)
			return (0);
		philo_start_thinking(philo);
	}
	return (1);
}

bool	simulation_continues(t_philo *philo)
{
	bool	ret;

	pthread_mutex_lock(philo->config->death_occured.mutex);
	pthread_mutex_lock(philo->config->end_of_simulation.mutex);
	ret = time_since_start(&philo->config->start_time)
		- philo->last_eat_time.data.uint32 < philo->config->time_to_die
		&& !philo->config->death_occured.data.boolean
		&& !philo->config->end_of_simulation.data.boolean;
	pthread_mutex_unlock(philo->config->end_of_simulation.mutex);
	pthread_mutex_unlock(philo->config->death_occured.mutex);
	return (ret);
}

/*
**	The routine executed in the thread.
**	@param {t_philo*} philo - The simulated philosopher.
**	@returns {void*} Return nothing.
*/
void	*simulate_philo_life(t_philo *philo)
{
	while (simulation_continues(philo))
	{
		if (route_philo_life(philo) < 1)
			break ;
	}
	if (philo->state.data.state == PHILO_EATING)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	philo_dies(philo);
	return (NULL);
}

/*
**	Start the simulation.
**	@param {t_philo_config*} config - The configuration of the simulation.
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
	pthread_t	check_thread;

	philos = setup_simulation(config);
	if (philos == NULL)
		return (1);
	i = 0;
	while (i < config->philos_no)
	{
		if (pthread_create(&philos[i].thread, NULL,
				(void *(*)(void *))simulate_philo_life, &philos[i]) != 0)
			return (1);
		i += 2;
		if (i >= config->philos_no && i % 2 == 0)
			i = 1;
	}
	if (pthread_create(&check_thread, NULL,
			(void *(*)(void *))check_on_philos, philos) != 0)
		return (1);
	if (pthread_join(check_thread, NULL) != 0)
		return (1);
	if (teardown_simulation(config, philos) < 0)
		return (1);
	return (config->death_occured.data.boolean);
}
