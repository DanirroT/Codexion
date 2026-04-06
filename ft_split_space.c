/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:08:55 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/04/06 15:13:51 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dsize)
{
	size_t	i;

	if (!src)
		return (0);
	if (dsize == 0 || !dst)
		return (strlen(src));
	i = 0;
	while (src[i] && (i < dsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (strlen(src));
}

static size_t	ft_wordlen(const char *s)
{
	int	res;

	res = 0;
	while (s[res] && !ft_isspace(s[res]))
		res++;
	return (res);
}

static int	ft_word_count(char const *s)
{
	int	word_count;
	int	word;
	int	i;

	word = 0;
	word_count = 0;
	i = 0;
	while (s[i])
	{
		if (!ft_isspace(s[i]) && word == 0)
		{
			word = 1;
			word_count++;
		}
		else if (ft_isspace(s[i]))
			word = 0;
		i++;
	}
	return (word_count);
}

static char	*ft_fill_word(char const *s)
{
	size_t	word_len;
	char	*word;

	word_len = ft_wordlen(s);
	word = malloc(sizeof(char) * (word_len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, s, word_len + 1);
	return (word);
}

char	**ft_split_space(char const *s)
{
	char	**split;
	int		i;

	if (!s)
		return (NULL);
	split = malloc(sizeof(char *) * (ft_word_count(s) + 1));
	if (!split)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (ft_isspace(*s))
			s++;
		if (*s)
		{
			split[i] = ft_fill_word(s);
			if (!split[i])
				return (trash_2d_char(split));
			i++;
			s += ft_wordlen(s);
		}
	}
	split[i] = NULL;
	return (split);
}
