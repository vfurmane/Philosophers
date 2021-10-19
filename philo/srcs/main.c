/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 21:33:08 by vfurmane          #+#    #+#             */
/*   Updated: 2021/10/18 10:49:32 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
**	Parse the command line arguments for the simulation.
**	@param {t_philo_config*} config - The configuration of the simulation. 
**	@param {int} argc - Total number of arguments.
**	@param {char**} argv - All command line arguments.
**	@returns {int} Return 1 if everything went well, 
**	or -1 on the following errors:
**	 -	The given arguments are not positive integers.
*/
int	parse_philo_args(t_philo_config *config, int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		if (!ft_is_positive_int(argv[i++]))
		{
			printf("\033[31mThe given parameters must be "
				"positive integers...\033[0m\n");
			return (-1);
		}
	}
	config->philos_no = ft_atoi(argv[0]);
	config->time_to_die = ft_atoi(argv[1]);
	config->time_to_eat = ft_atoi(argv[2]);
	config->time_to_sleep = ft_atoi(argv[3]);
	config->min_eat_no = 0;
	config->min_eat_no_set = false;
	if (argc == 5)
	{
		config->min_eat_no = ft_atoi(argv[4]);
		config->min_eat_no_set = true;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int				arg_start;
	t_arg_list		*list;
	t_philo_config	config;

	list = add_all_args();
	if (list == NULL)
		return (1);
	arg_start = argparse(argc, argv, list);
	if (help_needed(list))
	{
		print_usage(argv[0]);
		return (0);
	}
	else if (argc - arg_start != 4 && argc - arg_start != 5)
	{
		print_usage(argv[0]);
		return (1);
	}
	if (parse_philo_args(&config, argc - arg_start, &argv[arg_start]) < 0)
		return (1);
	ap_free(list);
	if (config.min_eat_no_set && config.min_eat_no == 0)
		return (0);
	return (simulation(&config));
}
