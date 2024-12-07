/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:44:51 by parden            #+#    #+#             */
/*   Updated: 2024/12/07 19:36:40 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	log_fork(t_param *p)
{
	struct timeval	time;
	int				ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000 - p->phi->start;
	sem_wait(p->phi->state);
	sem_wait(p->sem);
	if (!p->intro.over)
		printf("%d %d has taken a fork\n", ms, p->intro.id);
	sem_post(p->sem);
	sem_post(p->phi->state);
}

void	log_eat(t_param *p)
{
	struct timeval	time;
	int				ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000 - p->phi->start;
	sem_wait(p->phi->state);
	sem_wait(p->sem);
	if (!p->intro.over)
		printf("%d %d is eating\n", ms, p->intro.id);
	sem_post(p->sem);
	sem_post(p->phi->state);
}

void	log_sleep(t_param *p)
{
	struct timeval	time;
	int				ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000 - p->phi->start;
	sem_wait(p->phi->state);
	sem_wait(p->sem);
	if (!p->intro.over)
		printf("%d %d is sleeping\n", ms, p->intro.id);
	sem_post(p->sem);
	sem_post(p->phi->state);
}

void	log_think(t_param *p)
{
	struct timeval	time;
	int				ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000 - p->phi->start;
	sem_wait(p->phi->state);
	sem_wait(p->sem);
	if (!p->intro.over)
		printf("%d %d is thinking\n", ms, p->intro.id);
	sem_post(p->sem);
	sem_post(p->phi->state);
}
