/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 12:23:10 by vfurmane          #+#    #+#             */
/*   Updated: 2021/09/11 17:02:33 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
**	Add the args to the argparse list (-a, --arg).
**	@returns {t_arg_list *} the full list on success, 
**	or NULL on the following errors:
**	 -	the flag has not been successfully added to the list;
*/
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

/*
**	Check if the help flag is present.
**	@param {t_arg_list*} list - The list of arguments returned by ap_add_arg.
**	@returns {bool} Wether a help flag is present or not.
*/
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
