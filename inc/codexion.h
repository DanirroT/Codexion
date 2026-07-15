/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:40:31 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/07/15 23:29:14 by dmota-ri         ###   ########.fr       */
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
}	t_mult_ind;

enum e_scheduler_type
{
	FIFO,
	EDF
};

enum e_status
{
	DONE,
	ACTIVE
};

enum e_dongle_state
{
	HELD,
	FREE
};

// https://www.geeksforgeeks.org/c/thread-functions-in-c-c/

typedef struct s_input_args
{
	int	number_of_coders;
	int	time_to_burnout;
	int	time_to_compile;
	// main constraint. Connected to Matrix
	int	time_to_debug;
	// time spent debugging
	int	time_to_refactor;
	// after this is done, try to compile
	int	number_of_compiles_required;
	int	dongle_cooldown;
	int	scheduler;

}	t_input_args;

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
- edf means Earliest Deadline First with deadline = last_ct_start +
time_to_burnout.
*/

typedef struct s_list
{
	void				*content;
	struct s_list		*next;
	// struct s_int_list	*prev;
}	t_list;

typedef struct s_dongle
{
	int							id;

	pthread_t					thread;

	pthread_mutex_t				state_m;
	pthread_cond_t				take;
	pthread_cond_t				free;
	pthread_cond_t				ready;
	int							state;
	t_list						*queue;

	int							d_ready;

	struct s_programming_room	*room;
}	t_dongle;

typedef struct s_coder
{
	int							id;

	pthread_t					thread;
	pthread_t					burnout_thread;

	long long					last_ct;
	int							compilations_complete;

	pthread_mutex_t				compiling_m;
	pthread_cond_t				compiling_c;

	t_dongle					*dongle_r;
	t_dongle					*dongle_l;

	int							c_ready;

	struct s_programming_room	*room;
}	t_coder;

typedef struct s_programming_room
{
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_t		burnout_thread;
	int				b_ready;

	t_input_args	*inputs;
	struct timeval	start_time;

	pthread_mutex_t	print_m;
	pthread_mutex_t	ready_m;

	pthread_mutex_t	start_sim_m;
	pthread_cond_t	start_sim_c;

	pthread_mutex_t	burnout_m;
	int				burnout_state;
	int				complete_state;
}	t_programming_room;

int							ft_out(t_programming_room *room, void *temp, int code);

// Input
int							parse_args_inputs(char *argv[], t_programming_room *room);
// void						print_inputs(t_input_args *inputs);
// int							ft_num_count(char *args[], int num_count);
int							check_do_atoi_strict_pos(char **arg, int rep,
								int *temp, t_programming_room *room);

// Coder functions
void						*coder_funct(void *input_raw);
void						*coder_burnout(void *input_raw);
// void						do_compile(t_coder *self);
// void						do_compile_loop(t_coder *self);


// Coder <-> Queue Communication
void						take_dongles(t_coder *self);
void						free_dongles(t_coder *self);

// // Dongle functions
// void						*dongle_cooldown(void *input_raw);

void						*dongle_funct(void *input_raw);

// Queue Management
t_list						*ft_lstnew(void *content);
int							ft_lstsize(t_list *lst);
void						ft_lstadd_back(t_list **lst, t_list *new);
void						ft_lstclear(t_list **lst);

void						add_d_queue(t_dongle *dongle, t_coder *self);
void						remove_from_queue(t_dongle *dongle, int id);
void						print_queue(t_list *queue, int d_id, char *s);

// Time
unsigned long long			get_time_past(struct timeval start);
struct timespec				get_timespec_offset(int offset);
int							msleep(int wait);
int							safe_msleep(int wait, t_programming_room *room);

// Mutex Safe Functions
unsigned long long			print_event(t_programming_room *room, int id, char *msg);
int							check_burnout(t_programming_room *room);
// void						safe_add_val_int(int *var, int val, pthread_mutex_t *mutex);
void						safe_mod_val_int(int *var, int val, pthread_mutex_t *mutex);
void						safe_broadcast(pthread_cond_t *cond, pthread_mutex_t *mutex);
void						safe_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex,
								t_programming_room *room);
int							safe_cond_timedwait(pthread_cond_t *cond,
								pthread_mutex_t *mutex,
								int offset, t_programming_room *room);

// // Utils
int							ft_isspace(int c);
int							ft_isdigit(int c);
int							power(int base, int exp);

void						*trash(void *ptr);
void						*trash_2d_char(char **ptr);

char						**ft_split_space(char const *s);

#endif
