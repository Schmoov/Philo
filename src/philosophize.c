/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:48:49 by parden            #+#    #+#             */
/*   Updated: 2024/11/25 19:49:22 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_skip_first(t_param *param)
{
	if (param->id % 2)
		usleep(param->eat * 1000);
}

void	philo_skip_loop(t_param *param)
{
	if (param->nb % 2)
	{
		if (param->skip == param->nb / 2)
		{
			param->skip = 0;
			usleep(param->eat * 1000);
		}
	}
}

void	philo_get_forks(t_param *param)
{
	struct timeval	time;

	pthread_mutex_lock(param->first);
	log_fork(param);
	pthread_mutex_lock(param->second);
	pthread_mutex_lock(param->dead);
	gettimeofday(&time, NULL);
	param->death = time.tv_sec * 1000 + time.tv_usec / 1000
		+ param->die - param->start;
	pthread_mutex_unlock(param->dead);
}

void	philo_eat(t_param *param)
{
	if (param->hungry)
	{
		log_eat(param);
		usleep(param->eat * 1000);
		param->meal++;
		param->skip++;
	}
	pthread_mutex_unlock(param->first);
	pthread_mutex_unlock(param->second);
}

void	philo_sleep(t_param *param)
{
	if (param->hungry)
	{
		log_sleep(param);
		usleep(param->sleep * 1000);
		log_think(param);
	}
}

void	*philosophize(void *param)
{
	t_param	*p;

	p = param;
	philo_skip_first(p);
	while (p->hungry)
	{
		philo_skip_loop(p);
		philo_get_forks(p);
		philo_eat(p);
		philo_sleep(p);
	}
	return (NULL);
}
