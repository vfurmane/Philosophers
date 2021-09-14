/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_changes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 14:01:56 by vfurmane          #+#    #+#             */
/*   Updated: 2021/09/08 11:20:46 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	time_since_start(struct timeval *start_time)
{
	long			time_since_start;
	struct timeval	time_now;

	gettimeofday(&time_now, NULL); /* return */
	time_since_start = (time_now.tv_usec - start_time->tv_usec) / 1000;
	time_since_start += (time_now.tv_sec - start_time->tv_sec) * 1000;
	return (time_since_start);
}

int	philo_take_fork(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork); /* return error */
	printf("%-20ld %-10d has taken a fork\n", time_since_start(philo->start_time), philo->id);
	return (0);
}

int	philo_start_eating(t_philo *philo)
{
	philo->state = PHILO_EATING;
	printf("%-20ld %-10d is eating\n", 0l, philo->id);
	return (0);
}

int	philo_start_sleeping(t_philo *philo)
{
	philo->state = PHILO_SLEEPING;
	printf("%-20ld %-10d is sleeping\n", 0l, philo->id);
	return (0);
}

int	philo_start_thinking(t_philo *philo)
{
	philo->state = PHILO_THINKING;
	printf("%-20ld %-10d is thinking\n", 0l, philo->id);
	return (0);
}
