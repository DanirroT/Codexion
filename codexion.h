/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:40:31 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/04/02 20:41:59 by dmota-ri         ###   ########.fr       */
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
# include <limits.h>

typedef struct s_mult_ind
{
	int	i;
	int	j;
	int	k;
}		t_mult_ind;

// https://www.geeksforgeeks.org/c/thread-functions-in-c-c/

typedef struct s_input_args
{
	int				number_of_coders;
	int				time_to_burnout;
	int				time_to_compile; // main constraint. Connected to Matrix
	int				time_to_debug; // time spent debugging
	int				time_to_refactor; // after this is done, try to compile
	int				number_of_compiles_required;
	int				dongle_cooldown;
	int				scheduler;
	struct timeval	start_time;

}				t_input_args;

typedef struct s_programming_room
{
	pthread_t		*coders;
	pthread_mutex_t	*dongles;
	pthread_cond_t	*dongles_state;
}				t_programming_room;

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

dongle_cooldown (in milliseconds): After being released,
a dongle is unavailable until its cooldown has passed.

scheduler: The arbitration policy used by dongles to decide who gets them
when multiple coders request them.
The value must be exactly one of: fifo or edf.
- fifo means First In, First Out: the dongle is granted to the coder whose
request arrived first.
- edf means Earliest Deadline First with deadline = last_compile_start +
time_to_burnout.
*/

// Input and Utils

int				ft_isitoa(int c);
int				ft_isspace(int c);
int				ft_isdigit(int c);
int				ft_num_count(char *args[], int num_count);
t_input_args	*parse_args_inputs(int argc, char *argv[]);

// Utils

int				ft_out(t_input_args *args, int *temp, int code, char *msg);

void			*trash(void *ptr);
void			*trash_2d_void(void **ptr);
void			*trash_2d_char(char **ptr);
void			*trash_2d_int(int **ptr);

size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t dsize);

char			*ft_trim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			**ft_split_space(char const *s);

#endif
