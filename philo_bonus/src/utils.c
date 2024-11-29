/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <parden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:32:44 by parden            #+#    #+#             */
/*   Updated: 2024/11/29 21:20:52 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

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
	free(table->child);
	free(table->seat);
}

/*
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
*/
