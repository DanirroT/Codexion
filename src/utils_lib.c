/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 20:45:47 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/07/15 23:14:35 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}

int	ft_isspace(int c)
{
	return ((c == ' ' || (c >= 9 && c <= 13)));
}

int	power(int base, int exp)
{
	long long	result;

	result = 1;
	while (exp-- > 0)
	{
		result *= base;
		if (result > INT_MAX)
			return (INT_MAX);
	}
	return ((int)result);
}
