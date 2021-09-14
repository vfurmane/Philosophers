/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 12:23:10 by vfurmane          #+#    #+#             */
/*   Updated: 2021/09/04 12:23:18 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_arg_list	*add_all_args(void)
{
	t_arg_flag	flag;
	t_arg_list	*list;

	flag.chr = 'h';
	list = ap_add_arg(flag, SHORT_ARG);
	if (list == NULL)
		return (NULL);
	flag.str = "help";
	list = ap_add_arg(flag, LONG_ARG);
	if (list == NULL)
		return (NULL);
	return (list);
}

bool	help_needed(t_arg_list *list)
{
	t_arg_flag	flag;

	flag.chr = 'h';
	if (ap_search_arg(list, flag, SHORT_ARG) >= 0)
		return (true);
	flag.str = "help";
	if (ap_search_arg(list, flag, LONG_ARG) >= 0)
		return (true);
	return (false);
}
