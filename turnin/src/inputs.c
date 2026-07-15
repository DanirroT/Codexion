/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 17:01:36 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/06/26 18:50:12 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	ft_num_count_strict(char *args[], int num_count,
	t_programming_room *room)
{
	int			in_num;
	t_mult_ind	ind;

	ind.i = -1;
	while (args[++ind.i])
	{
		in_num = 0;
		ind.j = -1;
		while (args[ind.i][++ind.j])
		{
			if (!(ft_isspace(args[ind.i][ind.j])
				|| ft_isdigit(args[ind.i][ind.j])) && num_count < 7)
				return (printf("Error: Invalid character in input."),
					ft_out(room, NULL, -1));
			if (!ft_isspace(args[ind.i][ind.j]) && in_num == 0)
			{
				in_num = 1;
				num_count++;
			}
			if (ft_isspace(args[ind.i][ind.j]))
				in_num = 0;
		}
	}
	return (num_count);
}

static void	check_inputs(t_input_args *inputs, t_programming_room *room)
{
	int	print;

	print = 0;
	if (inputs->number_of_coders <= 0)
		print = printf("Error: number_of_coders must be greater than 0.");
	if (inputs->time_to_burnout <= 0)
		print = printf("Error: time_to_burnout must be greater than 0.");
	if (inputs->time_to_compile <= 0)
		print = printf("Error: time_to_compile must be greater than 0.");
	if (inputs->time_to_debug <= 0)
		print = printf("Error: time_to_debug must be greater than 0.");
	if (inputs->time_to_refactor <= 0)
		print = printf("Error: time_to_refactor must be greater than 0.");
	if (inputs->number_of_compiles_required <= 0)
		print = printf("Error: number_of_compiles_required "
				"must be greater than 0.");
	if (inputs->dongle_cooldown <= 0)
		print = printf("Error: dongle_cooldown must be greater than 0.");
	if (inputs->scheduler != FIFO && inputs->scheduler != EDF)
		print = printf("Error: Invalid scheduler. Must be "
				"'fifo' (0) or 'edf' (1).");
	if (print)
		ft_out(room, inputs, -1);
}

static int	*split_args(char *args[], t_programming_room *room)
{
	int	i;
	int	*output;

	output = malloc((size_t)(8 * sizeof(int)));
	if (!output || args[1][0] == '\0')
		return (trash(output), NULL);
	i = 0;
	while (args[i] && i < 7)
	{
		output[i] = check_do_atoi_strict_pos(args, i, output, room);
		i++;
	}
	if (strcmp(args[i], "fifo") == 0)
		output[i] = FIFO;
	else if (strcmp(args[i], "edf") == 0)
		output[i] = EDF;
	else
	{
		printf("Error: Invalid scheduler. Must be 'fifo' or 'edf'.");
		ft_out(room, output, -1);
	}
	return (output);
}

/*
int	*split_args(char *args[], int size)
{
	t_mult_ind	ind;
	int			*output;
	char		**temp;

	output = malloc((size_t)(size * sizeof(int)));
	if (!output || args[1][0] == '\0')
		return (trash(output), NULL);
	ind.i = -1;
	ind.k = 0;
	while (++ind.i >= 0 && args[ind.i] && ind.i < size - 2)
	{
		ind.j = -1;
		temp = ft_split_space(args[ind.i]);
		if (!temp)
			return (trash(output), NULL);
		while (temp[++ind.j])
			output[ind.k++] = check_do_atoi_strict_pos(temp, ind.j, output);
		trash_2d_char(temp);
	}
	ind.i++;
	if (strcmp(args[ind.i], "fifo") == 0)
		output[ind.k] = FIFO;
	else if (strcmp(args[ind.i], "edf") == 0)
		output[ind.k] = EDF;
	else
		return (ft_out(room, output, -1, -1,
			"Error: Invalid scheduler. Must be 'fifo' or 'edf'."));
	return (output);
}
*/

static t_input_args	*termin_to_room(t_programming_room *room, int *temp)
{
	t_input_args	*inputs;

	inputs = malloc((size_t)(sizeof(t_input_args)));
	if (!inputs)
		return (NULL);
	inputs->number_of_coders = temp[0];
	inputs->time_to_burnout = temp[1];
	inputs->time_to_compile = temp[2];
	inputs->time_to_debug = temp[3];
	inputs->time_to_refactor = temp[4];
	inputs->number_of_compiles_required = temp[5];
	inputs->dongle_cooldown = temp[6];
	inputs->scheduler = temp[7];
	check_inputs(inputs, room);
	return (inputs);
}

void	parse_args_inputs(char *argv[], t_programming_room *room)
{
	int	*temp;
	int	argc;

	argc = ft_num_count_strict(&argv[1], 0, room);
	if (argc != 8)
	{
		printf("Incorrect argument input.\nUsage: ./Codexion number_of_coders "
			"time_to_burnout time_to_compile time_to_debug time_to_refactor "
			"number_of_compiles_required dongle_cooldown scheduler\n");
		ft_out(room, NULL, -2);
	}
	temp = split_args(&argv[1], room);
	if (!temp)
	{
		printf("Error processing arguments. Please check your input format.");
		ft_out(room, NULL, -2);
	}
	room->inputs = termin_to_room(room, temp);
	if (!room->inputs)
		ft_out(room, NULL, -2);
	free(temp);
}
