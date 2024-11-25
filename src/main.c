/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:45:32 by parden            #+#    #+#             */
/*   Updated: 2024/11/25 20:20:21 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>
#include <sys/time.h>

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
		pthread_create(&curr, NULL, philosophize, &(table->seat[i]));
		table->thread[i] = curr;
		i++;
	}
}

void	reaper(t_philo *input, t_table *table)
{
	int				i;
	int				time;
	bool			casualty;
	struct timeval	tv;

	while (1)
	{
		casualty = false;
		usleep(5);
		i = 0;
		gettimeofday(&tv, NULL);
		time = tv.tv_sec * 1000 + tv.tv_usec / 1000 - table->start;
		while (i < input->nb)
		{
			pthread_mutex_lock(&table->dead[i]);
			if (table->seat[i].death < time)
			{
				pthread_mutex_lock(&table->mic);
				printf("%d %d died\n", time, i + 1);
				pthread_mutex_unlock(&table->mic);
				casualty = true;
			}
			pthread_mutex_unlock(&table->dead[i]);
			if (table->seat[i].meal >= input->servings)
				table->seat[i].hungry = false;
			i++;
			if (casualty)
				return ;
		}
	}
}

void	wrap_up(t_philo *input, t_table *table)
{
	int	i;

	i = 0;
	while (i < input->nb)
		table->seat[i++].hungry = false;
	i = 0;
	while (i < input->nb)
		pthread_join(table->thread[i++], NULL);
}

void	dishes(t_philo *input, t_table *table)
{
	int	i;

	i = 0;
	while (i < input->nb)
	{
		pthread_mutex_destroy(&table->fork[i]);
		pthread_mutex_destroy(&table->dead[i++]);
	}
	pthread_mutex_destroy(&table->mic);
	free(table->thread);
	free(table->fork);
	free(table->dead);
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
	if (!mise_en_place(&input, &table))
	{
		printf("The dining room is full\n");
		return (1);
	}
	bon_apetit(&input, &table);
	reaper(&input, &table);
	wrap_up(&input, &table);
	dishes(&input, &table);
}
