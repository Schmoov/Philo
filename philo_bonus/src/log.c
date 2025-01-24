/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:44:51 by parden            #+#    #+#             */
/*   Updated: 2025/01/24 16:32:47 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	log_str(t_param *p, char *str)
{
	sem_t	*sem;

	sem = p->phi->sem[p->intro.id];
	sem_wait(p->phi->state);
	sem_wait(sem);
	if (!p->intro.over)
		printf("%d %d %s\n", get_time() - p->phi->start, p->intro.id, str);
	sem_post(sem);
	sem_post(p->phi->state);
}

void	log_death(t_param *p, int time)
{
	sem_t	*sem;

	sem = p->phi->sem[p->intro.id];
	sem_wait(p->phi->state);
	sem_wait(sem);
	if (!p->intro.over)
		printf("%d %d died\n", time, p->intro.id);
	sem_post(p->phi->state);
}
