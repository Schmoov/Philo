/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:48:49 by parden            #+#    #+#             */
/*   Updated: 2024/11/28 18:13:50 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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

bool	philo_get_forks(t_param *p)
{
	struct timeval	time;

	pthread_mutex_lock(p->first);
	log_fork(p);
	pthread_mutex_lock(p->second);
	gettimeofday(&time, NULL);
	pthread_mutex_lock(p->state);
	p->death = time.tv_sec * 1000 + time.tv_usec / 1000
		+ p->phi->die - p->phi->start;
	pthread_mutex_unlock(p->state);
	return (true);
}

void	philo_eat(t_param *p)
{
	log_eat(p);
	usleep(p->phi->eat * 1000);
	pthread_mutex_lock(p->state);
	p->meal++;
	pthread_mutex_unlock(p->state);
	p->skip++;
	pthread_mutex_unlock(p->first);
	pthread_mutex_unlock(p->second);
	log_sleep(p);
	usleep(p->phi->sleep * 1000);
	log_think(p);
}

void	*philosophize(void *param)
{
	t_param	*p;

	p = param;
	philo_skip_first(p);
	pthread_mutex_lock(p->state);
	while (!p->phi->over)
	{
		pthread_mutex_unlock(p->state);
		philo_skip_loop(p);
		philo_get_forks(p);
		philo_eat(p);
		pthread_mutex_lock(p->state);
	}
	pthread_mutex_unlock(p->state);
	return (NULL);
}
