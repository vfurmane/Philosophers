/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:10:30 by vfurmane          #+#    #+#             */
/*   Updated: 2021/10/07 15:10:43 by vfurmane         ###   ########.fr       */
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
		if (*(t_state *)philos[i].state.data == PHILO_DEAD
			|| *(uint32_t *)philos[i].last_eat_time.data
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

/*
*/
void	*check_on_philos(t_philo *philos)
{
	uint32_t	i;

	while (!death_occured(philos))
	{
	}
	pthread_mutex_lock(philos[0].config->death_occured.mutex);
	*(int *)philos[0].config->death_occured.data = 1;
	pthread_mutex_unlock(philos[0].config->death_occured.mutex);
	i = 0;
	while (i < philos[0].config->philos_no)
	{
		pthread_mutex_unlock(philos[i].left_fork);
		i++;
	}
	return (NULL);
}
