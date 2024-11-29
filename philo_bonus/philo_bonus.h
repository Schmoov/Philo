/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:49:56 by parden            #+#    #+#             */
/*   Updated: 2024/11/29 21:25:20 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <unistd.h>
# include <sys/time.h>
# include <fcntl.h>
# include <semaphore.h>

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
	t_philo	*phi;

	int		id;
	int		meal;
	int		skip;
	int		death;

	sem_t	*state;
	sem_t	*fork;
}			t_param;

typedef struct s_table {
	sem_t	*state;
	sem_t	*fork;
	pid_t	*child;
	t_param	*seat;
}			t_table;

void	log_fork(t_param *p);
void	log_eat(t_param *p);
void	log_sleep(t_param *p);
void	log_think(t_param *p);

int		get_int(char *nptr, bool *err);
bool	parse(int argc, char **argv, t_philo *input);
bool	bon_apetit(t_philo *input, t_table *table);

bool	mep_alloc(t_philo *input, t_table *table);
void	mep_sem(t_philo *input, t_table *table);
void	mep_seat(t_philo *philo, t_table *table);
bool	mise_en_place(t_philo *philo, t_table *table);

void	philo_skip_first(t_param *p);
void	philo_skip_loop(t_param *p);
void	philo_get_forks(t_param *p);
void	philo_eat(t_param *p);
void	philosophize(void *param);

#endif
