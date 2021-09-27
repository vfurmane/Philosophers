/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 16:59:58 by vfurmane          #+#    #+#             */
/*   Updated: 2021/09/27 21:24:39 by vfurmane         ###   ########.fr       */
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
	timestamps = (time_now.tv_usec - start_time->tv_usec) / 1000;
	timestamps += (time_now.tv_sec - start_time->tv_sec) * 1000;
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
	struct timeval	time_now;

	if (gettimeofday(&time_now, NULL) < 0)
		return (0);
	return (time_now.tv_sec * 1000 + time_now.tv_usec / 1000);
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
	sleep_time = time_in_ms;
	time_before_death = time_now + philo->config->time_to_die
		+ philo->last_eat_time;
	max_time = time_now + time_in_ms;
	while (get_time_in_ms() < max_time)
	{
		usleep(sleep_time);
		if (get_time_in_ms() >= time_before_death)
			return (0);
	}
	return (1);
}
