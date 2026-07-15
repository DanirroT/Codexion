/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstreet- <nstreet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 16:22:13 by nstreet-          #+#    #+#             */
/*   Updated: 2026/04/27 13:21:37 by nstreet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/* Prints an error message and exits the program. */
void	error_exit(const char *error)
{
	printf(BOLD_RED "Error: %s\n" RST, error);
	exit(EXIT_FAILURE);
}

/* Prints a field-specific error message and exits the program. */
void	error_field(const char *field, const char *error)
{
	printf(BOLD_RED "Error: %s: %s\n" RST, field, error);
	exit(EXIT_FAILURE);
}
