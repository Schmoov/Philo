/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:49:56 by parden            #+#    #+#             */
/*   Updated: 2024/11/25 19:49:58 by parden           ###   ########.fr       */
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
	int	nb;
	int	die;
	int	eat;
	int	sleep;
	int	servings;
}		t_philo;

typedef struct s_param {
	int				nb;
	int				start;
	int				die;
	int				eat;
	int				sleep;

	int				id;
	int				meal;
	int				skip;
	int				death;
	bool			hungry;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*mic;
}					t_param;

typedef struct s_table {
	int				nb;
	int				start;
	pthread_t		*thread;
	pthread_mutex_t	mic;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*dead;
	t_param			*seat;
}					t_table;

int		get_int(char *nptr, bool *err);

void	log_fork(t_param *param);
void	log_eat(t_param *param);
void	log_sleep(t_param *param);
void	log_think(t_param *param);

bool	mise_en_place(t_philo *input, t_table *table);
bool	mep_alloc(t_philo *input, t_table *table);
void	mep_fork(t_table *table);
void	mep_seat(t_philo *input, t_table *table);

void	*philosophize(void *param);
void	philo_eat(t_param *param);
void	philo_sleep(t_param *param);
#endif
