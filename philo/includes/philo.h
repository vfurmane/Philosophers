/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 21:33:40 by vfurmane          #+#    #+#             */
/*   Updated: 2021/10/07 15:16:12 by vfurmane         ###   ########.fr       */
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

typedef struct s_mutex_data
{
	pthread_mutex_t	*mutex;
	void			*data;
}				t_mutex_data;

typedef struct s_philo_config
{
	uint32_t		philos_no;
	uint32_t		time_to_die;
	uint32_t		time_to_eat;
	uint32_t		time_to_sleep;
	uint32_t		min_eat_no;
	t_mutex_data	death_occured;
	struct timeval	start_time;
	pthread_mutex_t	forks_lock;
	pthread_mutex_t	death_lock;
}					t_philo_config;

typedef enum e_state
{
	PHILO_NOTHING,
	PHILO_EATING,
	PHILO_SLEEPING,
	PHILO_THINKING,
	PHILO_DEAD
}				t_state;

typedef struct s_philo
{
	uint32_t		id;
	pthread_t		thread;
	t_mutex_data	state;
	t_mutex_data	last_eat_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_philo_config	*config;
}					t_philo;

t_arg_list	*add_all_args(void);
bool		help_needed(t_arg_list *list);

bool		death_occured(t_philo *philos);
void		*check_on_philos(t_philo *philos);

int			philo_wants_to_eat(t_philo *philo);
int			philo_wants_to_sleep(t_philo *philo, bool drop_forks);
bool		philo_is_dead(t_philo *philo);

void		print_usage(char *program_name);

t_philo		*config_simulation(t_philo_config *config);
int			config_philo(t_philo_config *config, t_philo *philo);
int			share_forks(uint32_t philos_no, t_philo *philos, uint32_t i);
t_philo		*setup_simulation(t_philo_config *config);

int			simulation(t_philo_config *config);

int			philo_take_fork(t_philo *philo, pthread_mutex_t *fork);
int			philo_start_eating(t_philo *philo);
int			philo_start_sleeping(t_philo *philo);
int			philo_start_thinking(t_philo *philo);
int			philo_dies(t_philo *philo);

int			teardown_simulation(t_philo_config *config, t_philo *philos);

long		time_since_start(struct timeval *start_time);
int			wait_time(t_philo *philo, unsigned int time_in_ms);

#endif
