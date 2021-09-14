/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 09:23:10 by vfurmane          #+#    #+#             */
/*   Updated: 2021/09/11 17:36:04 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argparse.h"

/*
**	Enable a flag if it has been found in argv.
**	@param {t_arg_list*} list - The list of arguments returned by ap_add_arg.
**	@param {t_arg_flag} flag - The flag that is being searched.
**	@param {t_arg_type} type - The type of the flag that is being searched.
*/
void	check_flag_presence(t_arg_list *list, t_arg_flag flag, t_arg_type type)
{
	t_arg_list	*arg;

	arg = ap_get_arg(list, flag, type);
	if (arg != NULL)
		arg->enabled = true;
}

/*
**	Parse all arguments passed on the command line.
**	Stop reading when encounter -- (double hyphens), 
**	or an argument that doesn't start with a hyphen.
**	@param {int} argc - Total number of arguments.
**	@param {char**} argv - All command line arguments.
**	@param {t_arg_list*} list - The list of arguments returned by ap_add_arg.
**	@returns {int} position of the first ignored argument on success.
*/
int	argparse(int argc, char **argv, t_arg_list *list)
{
	int			i;
	int			j;
	t_arg_flag	flag;

	i = 1;
	while (i < argc && argv[i][0] == '-' &&
		(argv[i][1] != '-' || argv[i][2] != '\0'))
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
				flag.chr = argv[i][j++];
				check_flag_presence(list, flag, SHORT_ARG);
			}
		}
		i++;
	}
	return (i);
}

/*
**	Free the arguments list.
**	@param {t_arg_list*} list - The list to be freed.
*/
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
