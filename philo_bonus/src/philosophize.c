/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:48:49 by parden            #+#    #+#             */
/*   Updated: 2024/11/29 21:17:53 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	philo_skip_first(t_param *p)
{
	if (p->id % 2)
		usleep(p->phi->eat * 1000);
}

void	philo_skip_loop(t_param *p)
{
	if (p->phi->nb % 2)
	{
		if (p->skip == p->phi->nb / 2)
		{
			p->skip = 0;
			usleep(p->phi->eat * 1000);
		}
	}
}

void	philo_get_forks(t_param *p)
{
	struct timeval	time;

	sem_wait(p->fork);
	log_fork(p);
	sem_wait(p->fork);
	gettimeofday(&time, NULL);
	sem_wait(p->state);
	p->death = time.tv_sec * 1000 + time.tv_usec / 1000
		+ p->phi->die - p->phi->start;
	sem_post(p->state);
}

void	philo_eat(t_param *p)
{
	log_eat(p);
	usleep(p->phi->eat * 1000);
	sem_wait(p->state);
	p->meal++;
	sem_post(p->state);
	p->skip++;
	sem_post(p->fork);
	sem_post(p->fork);
	log_sleep(p);
	usleep(p->phi->sleep * 1000);
	log_think(p);
}

void	philosophize(void *param)
{
	t_param	*p;

	p = param;
	sem_wait(p->state);
	sem_post(p->state);
	philo_skip_first(p);
	sem_wait(p->state);
	while (!p->phi->over)
	{
		sem_post(p->state);
		philo_skip_loop(p);
		philo_get_forks(p);
		philo_eat(p);
		sem_wait(p->state);
	}
	sem_post(p->state);
}
