/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:40:31 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/04/01 20:37:02 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>

// https://www.geeksforgeeks.org/c/thread-functions-in-c-c/

typedef struct	s_input_args
{
	int		number_of_coders;
	int		time_to_burnout;
	int		time_to_compile; // main constraint. Connected to Matrix
	int		time_to_debug; // time spent debugging
	int		time_to_refactor; // after this is done, try to compile
	int		number_of_compiles_required;
	int		dongle_cooldown;
	int		scheduler;
	struct timeval start_time;

}				t_input_args;

/*
number_of_coders: The number of coders and also the number of dongles.

time_to_burnout (in milliseconds): If a coder did not start compiling within
time_to_burnout milliseconds since the beginning of their last compile or the
beginning of the simulation, they burn out.

time_to_compile (in milliseconds): The time it takes for a coder to compile.
During that time, they must hold two dongles.

time_to_debug (in milliseconds): The time a coder will spend debugging.

time_to_refactor (in milliseconds): The time a coder will spend refactoring.
After completing the refactoring phase, the coder will immediately attempt to
acquire dongles and start compiling again.
number_of_compiles_required: If all coders have compiled at least this
many times, the simulation stops. Otherwise, it stops when a coder burns
out.

dongle_cooldown (in milliseconds): After being released, a dongle is unavailable until its cooldown has passed.

scheduler: The arbitration policy used by dongles to decide who gets them
when multiple coders request them.
The value must be exactly one of: fifo or edf.
- fifo means First In, First Out: the dongle is granted to the coder whose
request arrived first.
- edf means Earliest Deadline First with deadline = last_compile_start +
time_to_burnout.
*/

// Utils

int ft_out(t_input_args *args, int code);

void	*trash(void *ptr);
void	*trash_2d_void(void **ptr);
void	*trash_2d_char(char **ptr);
void	*trash_2d_int(int **ptr);

char	*ft_trim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);

#endif
