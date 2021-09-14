/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 21:33:40 by vfurmane          #+#    #+#             */
/*   Updated: 2021/09/06 13:34:37 by vfurmane         ###   ########.fr       */
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
	uint32_t	philos_no;
	uint32_t	time_to_die;
	uint32_t	time_to_eat;
	uint32_t	time_to_sleep;
	uint32_t	min_eat_no;
}				t_philo_config;

typedef	enum e_state
{
	PHILO_EATING,
	PHILO_SLEEPING,
	PHILO_THINKING
}				t_state;

typedef	struct s_philo
{
	pthread_t	thread;
	t_state		state;
}				t_philo;

t_arg_list	*add_all_args(void);
bool		help_needed(t_arg_list *list);

void		print_usage(char *program_name);

#endif
