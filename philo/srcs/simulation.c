/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 14:00:14 by vfurmane          #+#    #+#             */
/*   Updated: 2021/09/08 11:33:12 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"

void	*simulate_philo_life(t_philo *philo)
{
	while (true)
	{
		if (philo->state == PHILO_NOTHING
			|| philo->state == PHILO_THINKING)
		{
			pthread_mutex_lock(philo->forks_lock);
			if (philo->left_fork->__data.__lock == 0
				&& philo->right_fork->__data.__lock == 0)
			{
				if (philo_take_fork(philo, philo->left_fork) < 0)
					pthread_exit(NULL);
				if (philo_take_fork(philo, philo->right_fork) < 0)
					pthread_exit(NULL);
				philo_start_eating(philo);
			}
			else if (philo->state == PHILO_NOTHING)
				philo_start_thinking(philo);
			pthread_mutex_unlock(philo->forks_lock);
		}
		else if (philo->state == PHILO_EATING)
		{
			usleep(2000000); /* ===== DELETE ===== */
			if (pthread_mutex_unlock(philo->left_fork) < 0)
				pthread_exit(NULL);
			if (pthread_mutex_unlock(philo->right_fork) < 0)
				pthread_exit(NULL);
			philo_start_sleeping(philo);
		}
		else if (philo->state == PHILO_SLEEPING)
		{
			usleep(2000000); /* ===== DELETE ===== */
			philo_start_thinking(philo);
		}
	}
	pthread_exit(NULL);
}

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

int	simulation(t_philo_config *config)
{
	uint32_t	i;
	t_philo		*philos;

	gettimeofday(&config->start_time, NULL); /* return */
	pthread_mutex_init(&config->forks_lock, NULL);
	philos = malloc(config->philos_no * sizeof (*philos));
	i = 0;
	while (i < config->philos_no)
	{
		philos[i].id = i + 1;
		philos[i].state = PHILO_NOTHING;
		philos[i].start_time = &config->start_time;
		philos[i].forks_lock = &config->forks_lock;
		if (share_forks(config->philos_no, philos, i) < 0)
			return (-1);
		i++;
	}
	i = 0;
	while (i < config->philos_no)
	{
		pthread_create(&philos[i].thread, NULL, (void*(*)(void *))simulate_philo_life, &philos[i]);
		i++;
	}
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
