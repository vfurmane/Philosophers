/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 16:59:58 by vfurmane          #+#    #+#             */
/*   Updated: 2021/10/18 09:18:38 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
**	Compute the time since the start of the simulation.
**	@param {struct timeval *} start_time - The time of the simulation starting.
**	@returns {long} Return the time since the start of the simulation, 
**	or -1 on the following errors:
**	 -	The time actual time could not be retrieved;
*/
long	time_since_start(struct timeval *start_time)
{
	long			timestamps;
	struct timeval	time_now;

	if (gettimeofday(&time_now, NULL) < 0)
		return (-1);
	timestamps = (time_now.tv_sec * 1000 + time_now.tv_usec / 1000)
		- (start_time->tv_sec * 1000 + start_time->tv_usec / 1000);
	return (timestamps);
}

/*
**	Get the actual time in ms.
**	@returns {unsigned int} Return the actual time in ms, 
**	or 0 on the following errors:
**	 -	The actual time could not be retrieved;
*/
unsigned int	get_time_in_ms(void)
{
	unsigned int	ret;
	struct timeval	time_now;

	if (gettimeofday(&time_now, NULL) < 0)
		return (0);
	ret = time_now.tv_sec * 1000 + time_now.tv_usec / 1000;
	return (ret);
}

/*
**	Wait time in ms.
**	@param {t_philo*} philo - The simulated philo.
**	@param {unsigned int} time_in_ms - The time to wait in ms.
**	before death of philo.
**	@returns {int} Return 1 on success, 
**	0 on philo death, 
**	or -1 on the following errors:
*/
int	wait_time(t_philo *philo, unsigned int time_in_ms)
{
	uint32_t	sleep_time;
	uint32_t	time_now;
	uint32_t	max_time;
	uint32_t	time_before_death;

	time_now = get_time_in_ms();
	sleep_time = 500;
	time_before_death = time_now + philo->config->time_to_die
		+ philo->last_eat_time.data.uint32;
	max_time = time_now + time_in_ms;
	pthread_mutex_lock(philo->config->death_occured.mutex);
	while (get_time_in_ms() < max_time
		&& !philo->config->death_occured.data.boolean)
	{
		pthread_mutex_unlock(philo->config->death_occured.mutex);
		usleep(sleep_time);
		if (get_time_in_ms() >= time_before_death)
			return (0);
		pthread_mutex_lock(philo->config->death_occured.mutex);
	}
	pthread_mutex_unlock(philo->config->death_occured.mutex);
	return (1);
}
