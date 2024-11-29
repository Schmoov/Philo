/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <parden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:32:44 by parden            #+#    #+#             */
/*   Updated: 2024/11/29 19:01:38 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	get_int(char *nptr, bool *err)
{
	long long	res;
	int			i;

	res = 0;
	i = 0;
	while (isdigit(nptr[i]) && res < INT_MAX)
	{
		res = 10 * res + nptr[i] - '0';
		i++;
	}
	if (nptr[i] || res > INT_MAX)
		*err = true;
	return (res);
}

void	table_destroy(t_table *table)
{
	free(table->thread);
	free(table->fork);
	free(table->seat);
}

void	thread_failed(t_philo *philo, t_table *table, int last)
{
	int	i;

	philo->over = true;
	pthread_mutex_unlock(&table->state);
	i = 0;
	while (i < last)
		pthread_join(table->thread[i++], NULL);
	i = 0;
	while (i < philo->nb)
		pthread_mutex_destroy(&table->fork[i++]);
	pthread_mutex_destroy(&table->state);
	table_destroy(table);
}

void	wrap_up(t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	while (i < philo->nb)
		pthread_join(table->thread[i++], NULL);
	i = 0;
	while (i < philo->nb)
		pthread_mutex_destroy(&table->fork[i++]);
	pthread_mutex_destroy(&table->state);
	table_destroy(table);
}
