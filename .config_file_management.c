/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_file_management.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 17:13:21 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/04/01 17:17:38 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

char *parse_txt_config(char *line)
{
	char *output;
	char *split_comment;
	char *split_str;

	split_comment = split(line, '#');
	split_str = split(split_comment[0], '=');
	if (len(split_str) != 2)
	{
		trash_2d_char(split_comment);
		trash_2d_char(split_str);
		return NULL;
	}
	free(split_str);
	return split_comment;
}

t_input_args *parse_args_inputs(int argc, char *argv[])
{
	t_input_args *output;
	char *in_config;
    int i;

	output = (t_input_args *)malloc(sizeof(t_input_args));

    i = 1;
    while (argv[i])
	{
		in_config = parse_txt_config(argv[i]);
		if (!in_config)
		{
			printf("In argument %i is formatted incorrectly\n", i);
			printf("Got:\t%s", argv[i]);
			printf("\nExpected:\tNAME=<VALUE> # Optional Comment\n");
			ft_out(output, 1);
		}
		route_config(output, in_config);
	}
	return output;
}
