/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 12:16:39 by vfurmane          #+#    #+#             */
/*   Updated: 2021/09/04 12:21:10 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_arg_list	*ap_lstlast(t_arg_list *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

static int	ap_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}

/*
** Add an argument to the list.
** flag contains a character or a string.
** type is SHORT_ARG or LONG_ARG (char or string in flag).
*/
t_arg_list	*ap_add_arg(t_arg_flag flag, t_arg_type type)
{
	t_arg_list			*new;
	static t_arg_list	*list;

	new = malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->flag = flag;
	new->type = type;
	new->enabled = false;
	if (list == NULL)
		list = new;
	else
		ap_lstlast(list)->next = new;
	return (list);
}

/*
** Search for a flag in the list and return its index.
** If the flag has not been found, return -1.
*/
int	ap_search_arg(t_arg_list *list, t_arg_flag flag, t_arg_type type)
{
	int	i;

	i = 0;
	while (list != NULL)
	{
		if (type == SHORT_ARG)
		{
			if (type == list->type && list->type == SHORT_ARG && list->enabled
				&& flag.chr == list->flag.chr)
				return (i);
		}
		else if (type == LONG_ARG)
		{
			if (type == list->type && type == list->type && list->enabled
				&& ap_strcmp(flag.str, list->flag.str) == 0)
				return (i);
		}
		i++;
		list = list->next;
	}
	return (-1);
}

t_arg_list	*ap_get_arg(t_arg_list *list, t_arg_flag flag,
	t_arg_type type)
{
	while (list != NULL)
	{
		if (type == SHORT_ARG)
		{
			if (type == list->type && list->type == SHORT_ARG
				&& flag.chr == list->flag.chr)
				return (list);
		}
		else if (type == LONG_ARG && list->type == LONG_ARG)
		{
			if (type == list->type && ap_strcmp(flag.str, list->flag.str) == 0)
				return (list);
		}
		list = list->next;
	}
	return (NULL);
}
