/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 10:35:02 by vfurmane          #+#    #+#             */
/*   Updated: 2021/09/11 17:32:52 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
**	Convert a string to an integer.
**	@param {const char*} str - The string to convert.
**	@returns {int} The new integer.
*/
int	ft_atoi(const char *str)
{
	int	i;
	int	nbr;
	int	neg;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	neg = (str[i] == '-') * -2 + 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	nbr = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (nbr * neg);
}
