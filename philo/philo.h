/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:49:56 by parden            #+#    #+#             */
/*   Updated: 2024/11/28 13:36:52 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_input {
	int	nb;
	int	die;
	int	eat;
	int	sleep;
	int	servings;
}		t_input;

typedef struct s_param {
	int				nb;
	int				die;
	int				eat;
	int				sleep;
	int				servings;

	int				start;
	int				id;
	int				meal;
	int				skip;
	int				death;
	bool			*over;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;
	pthread_mutex_t	*mic;
	pthread_mutex_t	*over_lock;
}					t_param;

typedef struct s_table {
	int				start;
	bool			over;
	pthread_t		*thread;
	pthread_mutex_t	mic;
	pthread_mutex_t	over_lock;
	pthread_mutex_t	*fork;
	t_param			*seat;
}					t_table;

int		get_int(char *nptr, bool *err);
bool	parse(int argc, char **argv, t_input *input);
void	bon_apetit(t_input *input, t_table *table);
void	reaper(t_input *input, t_table *table);
void	wrap_up(t_input *input, t_table *table);

bool	mep_alloc(t_input *input, t_table *table);
void	mep_mutex(t_input *input, t_table *table);
void	mep_seat(t_input *input, t_table *table);
bool	mise_en_place(t_input *input, t_table *table);

void	log_fork(t_param *param);
void	log_eat(t_param *param);
void	log_sleep(t_param *param);
void	log_think(t_param *param);

void	philo_skip_first(t_param *param);
void	philo_skip_loop(t_param *param);
bool	philo_get_forks(t_param *param);
void	philo_eat(t_param *param, bool is_over);
void	philo_sleep(t_param *param);
void	*philosophize(void *param);

#endif
