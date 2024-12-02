/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:45:32 by parden            #+#    #+#             */
/*   Updated: 2024/12/02 18:54:23 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"
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

bool	bon_apetit(t_philo *input, t_table *table)
{
	int		i;
	pid_t	curr;

	sem_wait(table->state);
	i = 0;
	while (i < input->nb)
	{
		curr = fork();
		if (!curr)
		{
			philosophize(&table->seat[i]);
			exit(420);
		}
		table->child[i++] = curr;
	}
	sem_post(table->state);
	return (true);
}

void reaper(t_philo *input, t_table *table)
{
	int		i;
	int		time;
	struct timeval	tv;
	bool	all_fed;
	int		casualty;

	while (1)
	{
		usleep(5);
		i = 0;
		casualty = -1;
		all_fed = true;
		gettimeofday(&tv, NULL);
		time = tv.tv_sec * 1000 + tv.tv_usec / 1000 - input->start;
		sem_wait(table->state);
		while (i < input->nb)
		{
			if (table->seat->death < time)
				casualty = i;
			if (table->seat->meal < input->servings)
				all_fed = false;
			i++;
		}
		if (casualty != -1 || all_fed)
		{
			input->over = true;
			if (casualty != -1)
				printf("%d %d died\n", time, casualty + 1);
			sem_post(table->state);
			return ;
		}
		sem_post(table->state);
	}
}

void wrap_up(t_philo *input, t_table *table)
{
	int	i;

	i = 0;
	while (i < input->nb)
		waitpid(table->child[i++], NULL, 0);
	table_destroy(table);
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
	bon_apetit(&input, &table);
	reaper(&input, &table);
	wrap_up(&input, &table);
}
