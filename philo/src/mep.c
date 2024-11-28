/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mep.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:50:43 by parden            #+#    #+#             */
/*   Updated: 2024/11/28 18:12:32 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	mep_alloc(t_philo *input, t_table *table)
{
	int	n;

	n = input->nb;
	table->thread = malloc(n * sizeof(pthread_t));
	if (!table->thread)
		return (false);
	table->fork = malloc(n * sizeof(pthread_mutex_t));
	if (!table->fork)
		return (free(table->thread), false);
	table->seat = malloc(n * sizeof(t_param));
	if (!table->seat)
		return (free(table->thread), free(table->fork), false);
	return (true);
}

void	mep_mutex(t_philo *input, t_table *table)
{
	int	i;

	pthread_mutex_init(&table->state, NULL);
	i = 0;
	while (i < input->nb)
		pthread_mutex_init(&table->fork[i++], NULL);
}

void	mep_seat(t_philo *philo, t_table *table)
{
	int				i;
	t_param			*curr;

	i = 0;
	while (i < philo->nb)
	{
		curr = &table->seat[i];
		curr->phi = philo;
		curr->id = i + 1;
		curr->meal = 0;
		curr->skip = i / 2;
		curr->death = philo->die;
		curr->state = &table->state;
		if (i)
		{
			curr->first = &table->fork[i];
			curr->second = &table->fork[i - 1];
		}
		else
		{
			curr->first = &table->fork[philo->nb - 1];
			curr->second = &table->fork[0];
		}
		i++;
	}
}

bool	mise_en_place(t_philo *philo, t_table *table)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	philo->start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	philo->over = false;
	if (!mep_alloc(philo, table))
		return (false);
	mep_mutex(philo, table);
	mep_seat(philo, table);
	return (true);
}
