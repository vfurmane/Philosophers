/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 09:23:10 by vfurmane          #+#    #+#             */
/*   Updated: 2021/09/04 17:32:54 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argparse.h"

void	check_flag_presence(t_arg_list *list, t_arg_flag flag, t_arg_type type)
{
	t_arg_list	*arg;

	arg = ap_get_arg(list, flag, type);
	if (arg != NULL)
		arg->enabled = true;
}

int	argparse(int argc, char **argv, t_arg_list *list)
{
	int			i;
	int			j;
	t_arg_flag	flag;

	i = 1;
	while (i < argc && argv[i][0] == '-')
	{
		if (argv[i][1] == '-')
		{
			flag.str = &argv[i][2];
			check_flag_presence(list, flag, LONG_ARG);
		}
		else
		{
			j = 1;
			while (argv[i][j] != '\0')
			{
				flag.chr = argv[i][j];
				check_flag_presence(list, flag, SHORT_ARG);
				j++;
			}
		}
		i++;
	}
	return (i);
}

void	ap_free(t_arg_list *list)
{
	t_arg_list	*next_elm;

	while (list)
	{
		next_elm = list->next;
		free(list);
		list = next_elm;
	}
}
