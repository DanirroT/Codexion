/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:40:31 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/04/20 17:09:03 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdlib.h>
# include <unistd.h>

# include <string.h>
# include <stdio.h>
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

enum s_scheduler_type {
	FIFO, // 0
	EDF   // 1
};

// https://www.geeksforgeeks.org/c/thread-functions-in-c-c/

typedef struct s_input_args
{
	int	number_of_coders;
	int	time_to_burnout;
	int	time_to_compile; // main constraint. Connected to Matrix
	int	time_to_debug; // time spent debugging
	int	time_to_refactor; // after this is done, try to compile
	int	number_of_compiles_required;
	int	dongle_cooldown;
	int	scheduler;

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

typedef struct s_dongle
{
	int				id;
	int				dongle_cooldown;
	pthread_t		thread;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	int				state;
}				t_dongle;

typedef struct s_coder
{
	int							id;
	long int					burnout_timer;
	long int					last_compile_time;
	int							compilations_complete;
	pthread_t					thread;
	t_dongle					*dongle_r;
	t_dongle					*dongle_l;
	struct s_programming_room	*room;
}				t_coder;

typedef struct s_programming_room
{
	t_coder			*coders;
	t_dongle		*dongles;

	t_input_args	*inputs;
	struct timeval	start_time;

	pthread_mutex_t	start_sim_m;
	pthread_cond_t	start_sim_c;

	pthread_mutex_t	pause_m;
	pthread_cond_t	pause_c;

	pthread_mutex_t	burnout_m;
	pthread_cond_t	burnout_c;
	int				burnout_state;
}				t_programming_room;

// Coder functions

void			do_compile(t_coder *self);
void			do_debug(t_coder *self);
void			do_refactor(t_coder *self);
void			take_dongles(t_coder *self);

void			*dongle_cooldown(void *input_raw);
void			free_dongles(t_coder *self);

void			*coder_funct(void *input_raw);

// Input and Utils

int				ft_isspace(int c);
int				ft_isdigit(int c);
// int				ft_num_count(char *args[], int num_count);
t_input_args	*parse_args_inputs(int argc, char *argv[]);

long long		get_time_past(struct timeval start);
struct timespec get_timespec_offset(int offset);
int				msleep(int wait);

int cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex, int *condition);
int cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex, int *condition, int delay);

int				ft_out(t_programming_room *room,
					int *temp, int code, char *msg);

void			*trash(void *ptr);
void			*trash_2d_char(char **ptr);
void			*trash_2d_int(int **ptr);

size_t			ft_strlcpy(char *dst, const char *src, size_t dsize);

char			**ft_split_space(char const *s);

#endif
