/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 20:45:47 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/04/02 20:45:53 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	ft_isitoa(int c)
{
	return (ft_isspace(c) || ft_isdigit(c)
		|| c == '+' || c == '-');
}

int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}

int	ft_isspace(int c)
{
	return ((c == ' ' || (c >= 9 && c <= 13)));
}
