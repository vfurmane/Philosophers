/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 21:33:40 by vfurmane          #+#    #+#             */
/*   Updated: 2021/09/15 13:53:23 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include "argparse.h"
# include "utils.h"

typedef struct s_philo_config
{
	uint32_t		philos_no;
	uint32_t		time_to_die;
	uint32_t		time_to_eat;
	uint32_t		time_to_sleep;
	uint32_t		min_eat_no;
	struct timeval	start_time;
	pthread_mutex_t	forks_lock;
}					t_philo_config;

typedef enum e_state
{
	PHILO_NOTHING,
	PHILO_EATING,
	PHILO_SLEEPING,
	PHILO_THINKING
}				t_state;

typedef struct s_fork
{
	bool			is_locked;
	pthread_mutex_t	lock;
}					t_fork;

typedef struct s_philo
{
	uint32_t		id;
	pthread_t		thread;
	t_state			state;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_philo_config	*config;
}					t_philo;

t_arg_list	*add_all_args(void);
bool		help_needed(t_arg_list *list);

void		philo_wants_to_eat(t_philo *philo);
void		philo_wants_to_sleep(t_philo *philo);

void		print_usage(char *program_name);

int			simulation(t_philo_config *config);

int			philo_take_fork(t_philo *philo, t_fork *fork);
int			philo_start_eating(t_philo *philo);
int			philo_start_sleeping(t_philo *philo);
int			philo_start_thinking(t_philo *philo);

long		time_since_start(struct timeval *start_time);
void		wait_time(unsigned int time_in_ms, unsigned int time_before_death);

#endif
