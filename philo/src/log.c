/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:44:51 by parden            #+#    #+#             */
/*   Updated: 2024/11/28 17:28:44 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	log_fork(t_param *p)
{
	struct timeval	time;
	int				ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000 - p->phi->start;
	pthread_mutex_lock(p->state);
	if (!p->phi->over)
		printf("%d %d has taken a fork\n", ms, p->id);
	pthread_mutex_unlock(p->state);
}

void	log_eat(t_param *p)
{
	struct timeval	time;
	int				ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000 - p->phi->start;
	pthread_mutex_lock(p->state);
	if (!p->phi->over)
		printf("%d %d is eating\n", ms, p->id);
	pthread_mutex_unlock(p->state);
}

void	log_sleep(t_param *p)
{
	struct timeval	time;
	int				ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000 - p->phi->start;
	pthread_mutex_lock(p->state);
	if (!p->phi->over)
		printf("%d %d is sleeping\n", ms, p->id);
	pthread_mutex_unlock(p->state);
}

void	log_think(t_param *p)
{
	struct timeval	time;
	int				ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000 - p->phi->start;
	pthread_mutex_lock(p->state);
	if (!p->phi->over)
		printf("%d %d is thinking\n", ms, p->id);
	pthread_mutex_unlock(p->state);
}
