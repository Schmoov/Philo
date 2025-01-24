/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bon_apetit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:31:58 by parden            #+#    #+#             */
/*   Updated: 2025/01/24 17:32:00 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	clean_up(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->nb)
	{
		if (p->child[i] != -1 && kill(p->child[i], 0))
		{
			kill(p->child[i], SIGTERM);
			waitpid(p->child[i], NULL, 0);
		}
		i++;
	}
	philo_destroy(p, true);
}

bool	bon_apetit(t_philo *philo)
{
	int		i;
	pid_t	curr;

	sem_wait(philo->state);
	i = 0;
	while (i < philo->nb)
	{
		curr = fork();
		if (!curr)
			take_seat(philo, i);
		philo->child[i++] = curr;
		if (curr == -1)
			return (clean_up(philo), false);
	}
	sem_post(philo->state);
	return (true);
}

void	reaper(t_philo *phi)
{
	int		status;
	pid_t	child;
	int		fed;

	fed = 0;
	while (fed < phi->nb)
	{
		child = waitpid(0, &status, WNOHANG);
		if (child && !WEXITSTATUS(status))
			return ;
		if (child)
			fed++;
	}
	return ;
}
