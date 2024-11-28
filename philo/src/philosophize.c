/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:48:49 by parden            #+#    #+#             */
/*   Updated: 2024/11/28 14:26:30 by parden           ###   ########.fr       */
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

bool	philo_get_forks(t_param *param)
{
	struct timeval	time;

	pthread_mutex_lock(param->first);
	log_fork(param);
	pthread_mutex_lock(param->second);
	gettimeofday(&time, NULL);
	pthread_mutex_lock(param->over_lock);
	if (*param->over)
		return (pthread_mutex_unlock(param->over_lock), false);
	param->death = time.tv_sec * 1000 + time.tv_usec / 1000
		+ param->die - param->start;
	pthread_mutex_unlock(param->over_lock);
	return (true);
}

void	philo_eat(t_param *param, bool is_over)
{
	if (!is_over)
	{
		log_eat(param);
		usleep(param->eat * 1000);
		pthread_mutex_lock(param->over_lock);
		param->meal++;
		pthread_mutex_unlock(param->over_lock);
		param->skip++;
	}
	pthread_mutex_unlock(param->first);
	pthread_mutex_unlock(param->second);
}

void	philo_sleep(t_param *param)
{
	log_sleep(param);
	usleep(param->sleep * 1000);
	log_think(param);
}

void	*philosophize(void *param)
{
	t_param	*p;
	bool	is_over;

	p = param;
	philo_skip_first(p);
	while (1)
	{
		philo_skip_loop(p);
		is_over = !philo_get_forks(p);
		philo_eat(p, is_over);
		if (is_over)
			break;
		philo_sleep(p);
	}
	return (NULL);
}
