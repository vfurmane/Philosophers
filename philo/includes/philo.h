/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 21:33:40 by vfurmane          #+#    #+#             */
/*   Updated: 2021/09/08 09:24:06 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include "argparse.h"
# include "utils.h"

typedef	struct s_philo_config
{
	uint32_t		philos_no;
	uint32_t		time_to_die;
	uint32_t		time_to_eat;
	uint32_t		time_to_sleep;
	uint32_t		min_eat_no;
	pthread_mutex_t	forks_lock;
}					t_philo_config;

typedef	enum e_state
{
	PHILO_NOTHING,
	PHILO_EATING,
	PHILO_SLEEPING,
	PHILO_THINKING
}				t_state;

typedef	struct s_philo
{
	uint32_t		id;
	pthread_t		thread;
	t_state			state;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*forks_lock;
}					t_philo;

t_arg_list	*add_all_args(void);
bool		help_needed(t_arg_list *list);

void		print_usage(char *program_name);

int			simulation(t_philo_config *config);

int			philo_take_fork(uint32_t id, pthread_mutex_t *fork);
int			philo_start_eating(uint32_t id, t_state *state);
int			philo_start_sleeping(uint32_t id, t_state *state);
int			philo_start_thinking(uint32_t id, t_state *state);

#endif
