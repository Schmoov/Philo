/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mep.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:50:43 by parden            #+#    #+#             */
/*   Updated: 2024/12/02 18:49:11 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"
#include <fcntl.h>

bool	mep_alloc(t_philo *input, t_table *table)
{
	int	n;

	n = input->nb;
	table->child = malloc(n * sizeof(pid_t));
	if (!table->child)
		return (false);
	table->seat = malloc(n * sizeof(t_param));
	if (!table->seat)
		return (free(table->child), false);
	return (true);
}

void	mep_sem(t_philo *input, t_table *table)
{
	table->state = sem_open("state", O_CREAT, 0600, 1);
	table->fork = sem_open("fork", O_CREAT, 0600, 2 * input->nb);
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
		curr->table = table;
		curr->id = i + 1;
		curr->meal = 0;
		curr->skip = i / 2;
		curr->death = philo->die;
		curr->state = table->state;
		curr->fork = table->fork;
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
	mep_sem(philo, table);
	mep_seat(philo, table);
	return (true);
}
