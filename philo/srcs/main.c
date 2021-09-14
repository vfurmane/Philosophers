/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 21:33:08 by vfurmane          #+#    #+#             */
/*   Updated: 2021/09/04 12:23:06 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_arg_list	*list;

	list = add_all_args();
	if (list == NULL)
		return (1);
	argparse(argc, argv, list);
	if (help_needed(list))
	{
		print_usage(argv[0]);
		return (0);
	}
	ap_free(list);
	return (0);
}
