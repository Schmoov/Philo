/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:45:32 by parden            #+#    #+#             */
/*   Updated: 2024/11/28 18:03:47 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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

void	bon_apetit(t_philo *input, t_table *table)
{
	int			i;
	pthread_t	curr;

	i = 0;
	while (i < input->nb)
	{
		pthread_create(&curr, NULL, philosophize, &table->seat[i]);
		table->thread[i] = curr;
		i++;
	}
}

void	reaper(t_philo *philo, t_table *table)
{
	int				i;
	int				time;
	int				casualty;
	bool			all_fed;
	struct timeval	tv;

	while (1)
	{
		usleep(5);
		i = 0;
		gettimeofday(&tv, NULL);
		time = tv.tv_sec * 1000 + tv.tv_usec / 1000 - philo->start;
		pthread_mutex_lock(&table->state);
		casualty = -1;
		all_fed = true;
		while (i < philo->nb)
		{
			if (table->seat[i].death < time)
			{
				casualty = i;
				break;
			}
			if (table->seat[i].meal < philo->servings)
				all_fed = false;
			i++;
		}
		if (casualty != -1 || all_fed)
		{
			philo->over = true;
			if (casualty != -1)
				printf("%d %d died\n", time, i + 1);
			pthread_mutex_unlock(&table->state);
			return;
		}
		pthread_mutex_unlock(&table->state);
	}
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
	free(table->thread);
	free(table->fork);
	free(table->seat);
}

int	main(int argc, char **argv)
{
	t_philo	input;
	t_table	table;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: philo nb die eat sleep [meals]\n");
		return (1);
	}
	if (!parse(argc, argv, &input))
	{
		printf("User skill issue\n");
		return (1);
	}
	if (input.nb == 1 && input.servings)
	{
		printf("0 1 died\n(He did not bother sitting,"
			" and committed seppuku with the fork)\n");
		return (1);
	}
	if (!mise_en_place(&input, &table))
	{
		printf("The dining room is full\n");
		return (1);
	}
	bon_apetit(&input, &table);
	reaper(&input, &table);
	wrap_up(&input, &table);
}
