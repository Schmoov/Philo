/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:48:49 by parden            #+#    #+#             */
/*   Updated: 2025/01/24 18:23:00 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	philo_skip_first(t_param *p)
{
	if (!(p->intro.id % 2))
		usleep(p->phi->eat * 1000);
}

void	philo_skip_loop(t_param *p)
{
	if (p->phi->nb % 2)
	{
		if (p->intro.skip == p->phi->nb / 2)
		{
			p->intro.skip = 0;
			usleep(p->phi->eat * 1000);
		}
	}
}

void	philo_get_forks(t_param *p)
{
	sem_wait(p->phi->fork);
	log_str(p, "has taken a fork");
	sem_wait(p->phi->fork);
	sem_wait(p->phi->sem[p->intro.id]);
	p->intro.death = get_time() + p->phi->die - p->phi->start;
	sem_post(p->phi->sem[p->intro.id]);
}

void	philo_eat(t_param *p)
{
	log_str(p, "is eating");
	usleep(p->phi->eat * 1000);
	sem_wait(p->phi->sem[p->intro.id]);
	p->intro.meal++;
	sem_post(p->phi->sem[p->intro.id]);
	p->intro.skip++;
	sem_post(p->phi->fork);
	sem_post(p->phi->fork);
	log_str(p, "is sleeping");
	usleep(p->phi->sleep * 1000);
	log_str(p, "is thinking");
}
