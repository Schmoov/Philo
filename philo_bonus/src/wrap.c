/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:26:13 by parden            #+#    #+#             */
/*   Updated: 2024/12/10 19:27:05 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	main_destroy(t_philo *phi)
{
	free(phi->child);
	sem_close(phi->fork);
	sem_unlink("fork");
	sem_close(phi->state);
	sem_unlink("state");
	exit(420);
}

void	wrap_up(t_philo *phi, pid_t child, int max, bool print)
{
	int				i;
	struct timeval	time;
	int				ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000 - phi->start;
	i = 0;
	while (i < phi->nb)
	{
		if (kill(phi->child[i], 0))
			kill(phi->child[i], SIGTERM);
		if (phi->child[i] == child && print)
			printf("%d %d died\n", ms, i + 1);
		i++;
	}
	while (i < phi->nb && i < max)
	{
		if (i != child)
			waitpid(phi->child[i], NULL, 0);
		i++;
	}
	main_destroy(phi);
}
