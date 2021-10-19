/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:10:30 by vfurmane          #+#    #+#             */
/*   Updated: 2021/10/19 16:13:25 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
*/
bool	death_occured(t_philo *philos)
{
	uint32_t	i;
	uint32_t	philos_no;

	i = 0;
	philos_no = philos[i].config->philos_no;
	pthread_mutex_lock(philos[i].last_eat_time.mutex);
	while (i < philos_no)
	{
		if (philos[i].state.data.state == PHILO_DEAD
			|| philos[i].last_eat_time.data.uint32
			+ philos[i].config->time_to_die
			<= time_since_start(&philos[i].config->start_time))
		{
			pthread_mutex_unlock(philos[i].last_eat_time.mutex);
			return (true);
		}
		pthread_mutex_unlock(philos[i].last_eat_time.mutex);
		i++;
		if (i < philos_no)
			pthread_mutex_lock(philos[i].last_eat_time.mutex);
	}
	return (false);
}

bool	all_philos_have_eaten(t_philo *philos)
{
	pthread_mutex_lock(philos[0].config->meals_target.mutex);
	if (philos[0].config->meals_target.data.uint32
		>= philos[0].config->philos_no
		&& philos[0].config->min_eat_no_set)
		return (true);
	pthread_mutex_unlock(philos[0].config->meals_target.mutex);
	return (false);
}

/*
*/
void	*check_on_philos(t_philo *philos)
{
	while (!death_occured(philos) && !all_philos_have_eaten(philos))
	{
	}
	pthread_mutex_lock(philos[0].config->death_occured.mutex);
	if (death_occured(philos))
		philos[0].config->death_occured.data.boolean = true;
	else
		philos[0].config->end_of_simulation.data.boolean = true;
	pthread_mutex_unlock(philos[0].config->death_occured.mutex);
	return (NULL);
}
