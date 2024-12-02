/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <parden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:32:44 by parden            #+#    #+#             */
/*   Updated: 2024/12/02 18:54:53 by parden           ###   ########.fr       */
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
