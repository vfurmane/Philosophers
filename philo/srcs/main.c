/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 21:33:08 by vfurmane          #+#    #+#             */
/*   Updated: 2021/09/06 13:30:21 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_philo_args(t_philo_config *config, int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc)
		if (!ft_is_positive_int(argv[i++]))
			return (-1);
	config->philos_no = ft_atoi(argv[0]);
	config->time_to_die = ft_atoi(argv[1]);
	config->time_to_eat = ft_atoi(argv[2]);
	config->time_to_sleep = ft_atoi(argv[3]);
	if (argc == 5)
		config->min_eat_no = ft_atoi(argv[4]);
	return (1);
}

void	*nothing(void *param)
{
	(void)param;
	pthread_exit(0);
}

int	simulation(t_philo_config *config)
{
	uint32_t	i;
	t_philo		*philos;

	philos = malloc(config->philos_no * sizeof (*philos));
	i = 0;
	while (i < config->philos_no)
	{
		pthread_create(&philos[i].thread, NULL, nothing, NULL);
		i++;
	}
	i = 0;
	while (i < config->philos_no)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	free(philos);
	return (0);
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
	return (simulation(&config));
}
