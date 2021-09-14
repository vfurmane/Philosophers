/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argparse_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 12:16:39 by vfurmane          #+#    #+#             */
/*   Updated: 2021/09/11 17:00:58 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
**	Get the last element of the list.
**	@param {t_arg_list*} list - The full flags list.
**	@returns {t_arg_list *} the last element of the list,
**	or NULL on the following errors:
**	 -	the list is NULL;
*/
static t_arg_list	*ap_lstlast(t_arg_list *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

/*
**	Compare two strings.
**	@param {const char*} str1 - The first string.
**	@param {const char*} str2 - The second string.
**	@returns {int} Return an integer less than, equal to, 
**	or greater than zero if s1 (or the first n bytes thereof) is found, 
**	respectively, to be less than, to match, or be greater than s2.
*/
int	ap_strcmp(const char *str1, const char *str2)
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
**	Add an argument to the list.
**	@param {t_arg_flag} flag - The letter or string composing the flag.
**	@param {t_arg_type} type - Wether the flag is short or long.
**	@returns {t_arg_list*} the full list on success, 
**	or NULL on the following errors:
**	 -	the allocation of the new element fails;
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

/*
**	Get the argument matching the flag and the type.
**	@param {t_arg_list*} list - The list of arguments returned by ap_add_arg.
**	@param {t_arg_flag} flag - The flag that is being searched.
**	@param {t_arg_type} type - The type of the flag that is being searched.
**	@returns {t_arg_list*} Return the list element, 
**	or NULL on the following errors:
**	 -	if it has not been found.
*/
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
