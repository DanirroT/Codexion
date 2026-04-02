/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 17:01:36 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/04/02 21:06:08 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1)
		return (-s2[0]);
	if (!s2)
		return (s1[0]);
	i = 0;
	if (n > 0)
	{
		while (s1[i] && s2[i] && (i < n))
		{
			if (s1[i] != s2[i])
				return ((unsigned char)s1[i] - (unsigned char)s2[i]);
			i++;
		}
	}
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

int	check_do_atoi(char **arg, int rep, int *temp)
{
	int			neg;
	int			i;
	long long	num;

	num = 0;
	i = 0;
	neg = 1;
	if (arg[rep][i] == '-' || arg[rep][i] == '+')
		if (arg[rep][i++] == '-')
			neg = -1;
	if (!ft_isdigit(arg[rep][i]))
		ft_out(NULL, temp, 2, "Error: Invalid number format. Expected a digit after optional sign.");
	while (ft_isdigit(arg[rep][i]))
	{
		if ((num * 10 + (arg[rep][i] - '0')) * neg > INT_MAX
			|| (num * 10 + (arg[rep][i] - '0')) * neg < INT_MIN)
			ft_out(NULL, temp, 2, "Error: Number out of range. Must be between -2147483648 and 2147483647.");
		num = num * 10 + (arg[rep][i] - '0');
		i++;
	}
	if (arg[rep][i] != '\0')
		ft_out(NULL, temp, 2, "Error: Invalid character after number.");
	return (neg * num);
}

int	ft_num_count(char *args[], int num_count)
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
			if (!ft_isitoa(args[ind.i][ind.j]) && num_count < 7)
				ft_out(NULL, NULL, -1, "Error: Invalid character in input.");
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

int	*split_args(char *args[], int size)
{
	t_mult_ind	ind;
	int			*input;
	char		**temp;

	input = malloc(size * sizeof(int));
	if (!input || args[1][0] == '\0')
		return (free(input), NULL);
	ind.i = -1;
	ind.k = 0;
	while (++ind.i >= 0 && args[ind.i] && ind.i < size - 2)
	{
		ind.j = -1;
		temp = ft_split_space(args[ind.i]);
		if (!temp)
			return (free(input), NULL);
		while (temp[++ind.j])
			input[ind.k++] = check_do_atoi(temp, ind.j, input);
		trash_2d_char(temp);
	}
	ind.i++;
	printf("Scheduler input %i: %s\n", ind.i, args[ind.i]);
	if (ft_strncmp(args[ind.i], "fifo", 4) == 0 || ft_strncmp(temp[ind.j], "fifo ", 4) == 0)
		input[ind.k] = 1;
	else if (ft_strncmp(args[ind.i], "edf", 3) == 0)
		input[ind.k] = 2;
	else
		ft_out(NULL, input, -1, "Error: Invalid scheduler. Must be 'fifo' or 'edf'.");
	return (input);
}

t_input_args	*parse_args_inputs(int argc, char *argv[])
{
	t_input_args	*input;
	int				*temp;

	argc = ft_num_count(&argv[1], 0);
	if (argc != 8)
	{
		ft_out(NULL, NULL, -2,
			"Incorrect argument input.\n"
			"Usage: Codexion number_of_coders time_to_burnout"
			" time_to_compile time_to_debug time_to_refactor"
			" number_of_compiles_required dongle_cooldown scheduler\n"
			);
	}
	temp = split_args(&argv[1], 8);
	if (!temp)
		ft_out(NULL, NULL, -2, "Error processing arguments. Please check your input format.");
	input = malloc(sizeof(t_input_args));
	input->number_of_coders = temp[0];
	input->time_to_burnout = temp[1];
	input->time_to_compile = temp[2];
	input->time_to_debug = temp[3];
	input->time_to_refactor = temp[4];
	input->number_of_compiles_required = temp[5];
	input->dongle_cooldown = temp[6];
	input->scheduler = temp[7];
	gettimeofday(&input->start_time, NULL);
	return (input);
}
