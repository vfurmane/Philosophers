/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 11:13:35 by vfurmane          #+#    #+#             */
/*   Updated: 2021/09/11 17:11:41 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
**	Check if the character contains a digit.
**	@param {int} chr - The character to test.
**	@returns {int} Return 1 if the character contains a digit, 
**	or 0 if not.
*/
int	ft_isdigit(int chr)
{
	return (chr >= '0' && chr <= '9');
}
