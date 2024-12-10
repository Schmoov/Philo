/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:48:49 by parden            #+#    #+#             */
/*   Updated: 2024/12/10 19:28:55 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	philo_skip_first(t_param *p)
{
	if (p->intro.id % 2)
		usleep(p->phi->eat * 1000);
}

void	philo_skip_loop(t_param *p)
{
	if (p->phi->nb % 2)
	{
		if (p->intro.skip == p->phi->nb / 2)
		{
			p->intro.skip = 0;
			usleep(p->phi->eat * 1000);
		}
	}
}

void	philo_get_forks(t_param *p)
{
	struct timeval	time;

	sem_wait(p->phi->fork);
	log_fork(p);
	sem_wait(p->phi->fork);
	gettimeofday(&time, NULL);
	sem_wait(p->sem);
	p->intro.death = time.tv_sec * 1000 + time.tv_usec / 1000
		+ p->phi->die - p->phi->start;
	sem_post(p->sem);
}

void	philo_eat(t_param *p)
{
	log_eat(p);
	usleep(p->phi->eat * 1000);
	sem_wait(p->sem);
	p->intro.meal++;
	sem_post(p->sem);
	p->intro.skip++;
	sem_post(p->phi->fork);
	sem_post(p->phi->fork);
	log_sleep(p);
	usleep(p->phi->sleep * 1000);
	log_think(p);
}
