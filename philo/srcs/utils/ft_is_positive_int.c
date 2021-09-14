/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_positive_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 10:26:53 by vfurmane          #+#    #+#             */
/*   Updated: 2021/09/11 17:09:19 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
**	Check if the string contains a positive integer.
**	@param {const char*} str - The string to test.
**	@returns {int} Return 1 if the string contains a positive integer, 
**	0 if not.
*/
int	ft_is_positive_int(const char *str)
{
	int			i;
	int			len;
	char		*max_int;

	max_int = "2147483647";
	len = ft_strlen(str);
	if (len > 10)
		return (0);
	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		if (len == 10)
		{
			if (max_int != NULL && str[i] > max_int[i])
				return (0);
			else if (max_int != NULL && str[i] < max_int[i])
				max_int = NULL;
		}
	}
	return (1);
}
