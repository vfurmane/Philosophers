/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_changes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 14:01:56 by vfurmane          #+#    #+#             */
/*   Updated: 2021/09/07 16:33:29 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_take_fork(uint32_t id, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork); /* return error */
	printf("%-20ld %-10d has taken a fork\n", 0l, id);
	return (0);
}
