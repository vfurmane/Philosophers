/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argparse.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 09:24:12 by vfurmane          #+#    #+#             */
/*   Updated: 2021/09/04 17:35:45 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGPARSE_H
# define ARGPARSE_H

# include <stdbool.h>
# include <stdlib.h>

typedef union u_arg_flag
{
	char		chr;
	char		*str;
}				t_arg_flag;

typedef enum e_arg_type
{
	SHORT_ARG,
	LONG_ARG
}				t_arg_type;

typedef struct s_arg_list
{
	struct s_arg_list	*next;
	t_arg_flag			flag;
	t_arg_type			type;
	bool				enabled;
}						t_arg_list;

t_arg_list	*ap_add_arg(t_arg_flag flag, t_arg_type type);
int			ap_search_arg(t_arg_list *list, t_arg_flag flag, t_arg_type type);
t_arg_list	*ap_get_arg(t_arg_list *list, t_arg_flag flag, t_arg_type type);

void		ap_free(t_arg_list *list);
int			argparse(int argc, char **argv, t_arg_list *list);

#endif
