/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:44:51 by parden            #+#    #+#             */
/*   Updated: 2025/01/24 17:14:33 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	log_str(t_param *p, char *str)
{
	sem_t	*sem;

	sem = p->phi->sem[p->intro.id];
	sem_wait(sem);
	if (p->intro.over)
	{
		sem_post(sem);
		return ;
	}
	sem_wait(p->phi->state);
	printf("%d %d %s\n", get_time() - p->phi->start, p->intro.id + 1, str);
	sem_post(p->phi->state);
	sem_post(sem);
}

void	log_death(t_param *p, int time)
{
	sem_wait(p->phi->state);
	printf("%d %d died\n", time, p->intro.id + 1);
	//sem_post(p->phi->state);
}
