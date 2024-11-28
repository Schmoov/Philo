/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:44:51 by parden            #+#    #+#             */
/*   Updated: 2024/11/28 14:40:47 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	log_fork(t_param *param)
{
	struct timeval	time;
	int				ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000 - param->start;
	pthread_mutex_lock(param->over_lock);
	pthread_mutex_lock(param->mic);
	if (!*param->over)
		printf("%d %d has taken a fork\n", ms, param->id);
	pthread_mutex_unlock(param->mic);
	pthread_mutex_unlock(param->over_lock);
}

void	log_eat(t_param *param)
{
	struct timeval	time;
	int				ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000 - param->start;
	pthread_mutex_lock(param->over_lock);
	pthread_mutex_lock(param->mic);
	if (!*param->over)
		printf("%d %d is eating\n", ms, param->id);
	pthread_mutex_unlock(param->mic);
	pthread_mutex_unlock(param->over_lock);
}

void	log_sleep(t_param *param)
{
	struct timeval	time;
	int				ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000 - param->start;
	pthread_mutex_lock(param->over_lock);
	pthread_mutex_lock(param->mic);
	if (!*param->over)
		printf("%d %d is sleeping\n", ms, param->id);
	pthread_mutex_unlock(param->mic);
	pthread_mutex_unlock(param->over_lock);
}

void	log_think(t_param *param)
{
	struct timeval	time;
	int				ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000 - param->start;
	pthread_mutex_lock(param->over_lock);
	pthread_mutex_lock(param->mic);
	if (!*param->over)
		printf("%d %d is thinking\n", ms, param->id);
	pthread_mutex_unlock(param->mic);
	pthread_mutex_unlock(param->over_lock);
}
