/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:08:55 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/04/01 17:18:03 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static size_t	ft_wordlen(const char *s, char c)
{
	int	res;

	res = 0;
	while (s[res] && s[res] != c)
		res++;
	return (res);
}

static int	ft_word_count(char const *s, char c)
{
	int	word_count;
	int	word;
	int	i;

	word = 0;
	word_count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && word == 0)
		{
			word = 1;
			word_count++;
		}
		else if (s[i] == c)
			word = 0;
		i++;
	}
	return (word_count);
}

static char	*ft_fill_word(char const *s, char c)
{
	size_t	word_len;
	char	*word;

	word_len = ft_wordlen(s, c);
	word = malloc(sizeof(char) * (word_len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, s, word_len + 1);
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i;

	if (!s)
		return (NULL);
	split = malloc(sizeof(char *) * (ft_word_count(s, c) + 1));
	if (!split)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			split[i] = ft_fill_word(s, c);
			if (!split[i])
				return (trash_2d_char(split));
			i++;
			s += ft_wordlen(s, c);
		}
	}
	split[i] = NULL;
	return (split);
}
