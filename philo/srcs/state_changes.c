/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_changes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 14:01:56 by vfurmane          #+#    #+#             */
/*   Updated: 2021/09/08 09:23:44 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_take_fork(uint32_t id, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork); /* return error */
	printf("%-20ld %-10d has taken a fork\n", 0l, id);
	return (0);
}

int	philo_start_eating(uint32_t id, t_state *state)
{
	*state = PHILO_EATING;
	printf("%-20ld %-10d is eating\n", 0l, id);
	return (0);
}

int	philo_start_sleeping(uint32_t id, t_state *state)
{
	*state = PHILO_SLEEPING;
	printf("%-20ld %-10d is sleeping\n", 0l, id);
	return (0);
}

int	philo_start_thinking(uint32_t id, t_state *state)
{
	*state = PHILO_THINKING;
	printf("%-20ld %-10d is thinking\n", 0l, id);
	return (0);
}
