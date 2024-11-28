/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mep.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:50:43 by parden            #+#    #+#             */
/*   Updated: 2024/11/28 14:02:57 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	mep_alloc(t_input *input, t_table *table)
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

void	mep_mutex(t_input *input, t_table *table)
{
	int	i;

	pthread_mutex_init(&table->mic, NULL);
	pthread_mutex_init(&table->over_lock, NULL);
	i = 0;
	while (i < input->nb)
		pthread_mutex_init(&(table->fork[i++]), NULL);
}

void	mep_seat(t_input *input, t_table *table)
{
	int				i;
	t_param			*curr;

	i = 0;
	while (i < input->nb)
	{
		curr = &table->seat[i];
		curr->nb = input->nb;
		curr->die = input->die;
		curr->eat = input->eat;
		curr->sleep = input->sleep;
		curr->servings = input->servings;

		curr->start = table->start;
		curr->id = i + 1;
		curr->meal = 0;
		curr->skip = i / 2;
		curr->death = input->die;
		curr->over = &table->over;
		curr->first = &table->fork[i ? i : input->nb - 1];
		curr->second = &table->fork[i ? i - 1 : 0];
		curr->mic = &table->mic;
		curr->over_lock = &table->over_lock;
		i++;
	}
}

bool	mise_en_place(t_input *input, t_table *table)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	table->start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	table->over = false;
	if (!mep_alloc(input, table))
		return (false);
	mep_mutex(input, table);
	mep_seat(input, table);
	return (true);
}
