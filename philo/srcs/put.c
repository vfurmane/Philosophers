/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 22:56:51 by vfurmane          #+#    #+#             */
/*   Updated: 2021/09/11 17:03:26 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
**	Print an usage message.
**	@param {char*} program_name - The name of the program.
*/
void	print_usage(char *program_name)
{
	printf("Usage: %s [-h] ", program_name);
	printf("No_of_philos ");
	printf("time_to_die ");
	printf("time_to_eat ");
	printf("time_to_sleep ");
	printf("[No_of_times_each_philo_must_eat]\n\n");
	printf("  -h, --help\tdisplay this help and exit\n");
}
