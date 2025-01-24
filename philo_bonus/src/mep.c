/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mep.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:32:26 by parden            #+#    #+#             */
/*   Updated: 2025/01/24 17:35:22 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	mep_sem_unlink(t_philo *p)
{
	int	i;

	sem_close(p->state);
	sem_unlink("state");
	sem_close(p->fork);
	sem_unlink("fork");
	i = 0;
	while (i < p->nb && p->sem[i] != SEM_FAILED)
	{
		sem_close(p->sem[i]);
		sem_unlink(p->str_sem[i++]);
	}
}

void	mep_sem_close(t_philo *p)
{
	int	i;

	sem_close(p->state);
	sem_close(p->fork);
	i = 0;
	while (i < p->nb && p->sem[i] != SEM_FAILED)
		sem_close(p->sem[i++]);
}

bool	mep_sem(t_philo *p)
{
	int	i;

	p->state = sem_open("state", O_CREAT, 0600, 1);
	if (p->state == SEM_FAILED)
		return (false);
	p->fork = sem_open("fork", O_CREAT, 0600, p->nb);
	if (p->fork == SEM_FAILED)
		return (sem_close(p->state), sem_unlink("state"), false);
	i = 0;
	while (i < p->nb)
	{
		p->sem[i] = sem_open(p->str_sem[i], O_CREAT, 0600, 1);
		if (p->sem[i] == SEM_FAILED)
			return (mep_sem_unlink(p), false);
		i++;
	}
	return (true);
}

bool	mep_alloc(t_philo *p)
{
	p->str_sem = malloc(p->nb * 5);
	if (!p->str_sem)
		return (false);
	p->child = malloc(p->nb * sizeof(pid_t));
	if (!p->child)
		return (free(p->str_sem), false);
	p->sem = malloc(p->nb * sizeof(sem_t));
	if (!p->sem)
		return (free(p->str_sem), free(p->child), false);
	return (true);
}

bool	mise_en_place(t_philo *p)
{
	p->start = get_time();
	if (!mep_alloc(p))
		return (false);
	memset(p->child, -1, p->nb * sizeof(pid_t));
	mep_sem_str(p);
	if (!mep_sem(p))
		return (mep_free(p), false);
	return (true);
}
