/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:49:56 by parden            #+#    #+#             */
/*   Updated: 2024/11/29 18:57:11 by parden           ###   ########.fr       */
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

typedef struct s_philo {
	int		nb;
	int		die;
	int		eat;
	int		sleep;
	int		servings;

	int		start;
	bool	over;
}		t_philo;

typedef struct s_param {
	t_philo			*phi;

	int				id;
	int				meal;
	int				skip;
	int				death;

	pthread_mutex_t	*state;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;
}					t_param;

typedef struct s_table {
	pthread_mutex_t	state;
	pthread_t		*thread;
	pthread_mutex_t	*fork;
	t_param			*seat;
}					t_table;

int		get_int(char *nptr, bool *err);
bool	parse(int argc, char **argv, t_philo *input);
bool	bon_apetit(t_philo *input, t_table *table);
void	reaper(t_philo *philo, t_table *table);
void	wrap_up(t_philo *philo, t_table *table);

void	thread_failed(t_philo *philo, t_table *table, int last);
void	table_destroy(t_table *table);
bool	mep_alloc(t_philo *input, t_table *table);
bool	mep_mutex(t_philo *input, t_table *table);
void	mep_seat(t_philo *philo, t_table *table);
bool	mise_en_place(t_philo *philo, t_table *table);

void	log_fork(t_param *p);
void	log_eat(t_param *p);
void	log_sleep(t_param *p);
void	log_think(t_param *p);

void	philo_skip_first(t_param *p);
void	philo_skip_loop(t_param *p);
bool	philo_get_forks(t_param *p);
void	philo_eat(t_param *p);
void	*philosophize(void *param);

#endif
