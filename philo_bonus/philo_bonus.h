/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:49:56 by parden            #+#    #+#             */
/*   Updated: 2024/12/08 21:16:58 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/wait.h>

typedef struct s_philo {
	int		nb;
	int		die;
	int		eat;
	int		sleep;
	int		servings;

	int		start;
	sem_t	*state;
	sem_t	*fork;
	pid_t	*child;
}			t_philo;

typedef struct s_intro {
	int		id;
	int		meal;
	int		skip;
	int		death;
	bool	over;

}			t_intro;

typedef struct s_param {
	t_philo	*phi;
	t_intro	intro;
	char	str_sem[5];
	sem_t	*sem;
}			t_param;

void	log_fork(t_param *p);
void	log_eat(t_param *p);
void	log_sleep(t_param *p);
void	log_think(t_param *p);
bool	mise_en_place(t_philo *philo);
bool	parse(int argc, char **argv, t_philo *input);
bool	bon_apetit(t_philo *philo);
void wrap_up(t_philo *phi, pid_t child);
void reaper(t_philo *phi);
void	philo_skip_first(t_param *p);
void	philo_skip_loop(t_param *p);
void	philo_get_forks(t_param *p);
void	philo_eat(t_param *p);
void	*philosophize(void *param);
void	intro_param_init(t_param *p, int i);
void	introspect_loop(t_param *p);
bool	introspect(t_philo *phi, int i);
int	get_int(char *nptr, bool *err);

#endif
