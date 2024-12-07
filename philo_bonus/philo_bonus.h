/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:49:56 by parden            #+#    #+#             */
/*   Updated: 2024/12/07 19:59:43 by parden           ###   ########.fr       */
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
	sem_t	*sem;
}			t_param;
#endif
