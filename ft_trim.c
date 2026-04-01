/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:25:07 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/04/01 17:18:53 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	c_in_set(char c, char const *set)
{
	size_t	j;

	j = 0;
	while (set[j])
	{
		if (c == set[j])
			return (1);
		j++;
	}
	return (0);
}

char	*ft_trim(char const *s1, char const *set)
{
	size_t	len;
	char	*start;
	char	*trim;
	size_t	i;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	len = ft_strlen(s1);
	i = 0;
	while (s1[i] && c_in_set(s1[i], set))
		i++;
	start = (char *)&s1[i];
	i = len - 1;
	while (i > 0 && c_in_set(s1[i], set))
		i--;
	len = ((&s1[i] - start) + 1);
	if (!*start)
		len = 0;
	trim = malloc(sizeof(char) * (len + 1));
	if (!trim)
		return (NULL);
	ft_strlcpy(trim, start, (len + 1));
	return (trim);
}
