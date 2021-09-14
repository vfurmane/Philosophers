/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 21:33:40 by vfurmane          #+#    #+#             */
/*   Updated: 2021/09/05 14:59:42 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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

t_arg_list	*add_all_args(void);
bool		help_needed(t_arg_list *list);

void		print_usage(char *program_name);

#endif
