/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:45:32 by parden            #+#    #+#             */
/*   Updated: 2024/11/29 19:08:50 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <bits/pthreadtypes.h>

bool	parse(int argc, char **argv, t_philo *input)
{
	int		i;
	int		*ptr;
	bool	err;

	input->servings = INT_MAX;
	ptr = (int *)input;
	err = false;
	i = 0;
	while (i + 1 < argc)
	{
		ptr[i] = get_int(argv[i + 1], &err);
		i++;
	}
	return (!err);
}

bool	bon_apetit(t_philo *input, t_table *table)
{
	int			i;
	pthread_t	curr;

	pthread_mutex_lock(&table->state);
	i = 0;
	while (i < input->nb)
	{
		if (pthread_create(&curr, NULL, philosophize, &table->seat[i]))
			break ;
		table->thread[i] = curr;
		i++;
	}
	if (i < input->nb)
		return (thread_failed(input, table, i), false);
	pthread_mutex_unlock(&table->state);
	return (true);
}

int	reaper_helper(t_philo *philo, t_table *table, int *casualty, bool *all_fed)
{
	int				i;
	int				time;
	struct timeval	tv;

	i = 0;
	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000 - philo->start;
	while (i < philo->nb)
	{
		if (table->seat[i].death < time)
		{
			*casualty = i;
			break ;
		}
		if (table->seat[i].meal < philo->servings)
			*all_fed = false;
		i++;
	}
	return (time);
}

void	reaper(t_philo *philo, t_table *table)
{
	int		time;
	int		casualty;
	bool	all_fed;

	while (1)
	{
		usleep(5);
		pthread_mutex_lock(&table->state);
		casualty = -1;
		all_fed = true;
		time = reaper_helper(philo, table, &casualty, &all_fed);
		if (casualty != -1 || all_fed)
		{
			philo->over = true;
			if (casualty != -1)
				printf("%d %d died\n", time, casualty + 1);
			pthread_mutex_unlock(&table->state);
			return ;
		}
		pthread_mutex_unlock(&table->state);
	}
}

int	main(int argc, char **argv)
{
	t_philo	input;
	t_table	table;

	if (argc < 5 || argc > 6)
		return (printf("Usage: philo nb die eat sleep [meals]\n"));
	if (!parse(argc, argv, &input))
		return (printf("User skill issue\n"));
	if (input.nb == 1 && input.servings)
	{
		printf("0 1 died\n(He did not bother sitting,"
			" and committed seppuku with the fork)\n");
		return (1);
	}
	if (!mise_en_place(&input, &table))
		return (printf("The dining room is full\n"));
	if (bon_apetit(&input, &table))
	{
		reaper(&input, &table);
		wrap_up(&input, &table);
	}
}
