/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:49:56 by parden            #+#    #+#             */
/*   Updated: 2025/01/24 16:32:22 by parden           ###   ########.fr       */
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
	char	(*str_sem)[5];
	sem_t	**sem;
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
}			t_param;

void	clean_up(t_philo *p);
bool	bon_apetit(t_philo *philo);
void	reaper(t_philo *phi);
void	log_str(t_param *p, char *str);
void	log_death(t_param *p, int time);
bool	parse(int argc, char **argv, t_philo *input);
void	mep_sem_str(t_philo *p);
void	mep_sem_unlink(t_philo *p);
void	mep_sem_close(t_philo *p);
bool	mep_sem(t_philo *p);
bool	mep_alloc(t_philo *p);
void	mep_free(t_philo *p);
bool	mise_en_place(t_philo *p);
void	philo_destroy(t_philo *p, bool unlink);
void	*philosophize(void *param);
void	introspect(t_param *p);
void intro_init(t_philo *phi, t_param *par, int i);
bool	take_seat(t_philo *phi, int i);
void	philo_skip_first(t_param *p);
void	philo_skip_loop(t_param *p);
void	philo_get_forks(t_param *p);
void	philo_eat(t_param *p);
int	get_int(char *nptr, bool *err);
int	get_time();
#endif
