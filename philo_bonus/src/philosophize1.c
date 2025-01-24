/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:48:49 by parden            #+#    #+#             */
/*   Updated: 2025/01/24 17:15:18 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	*philosophize(void *param)
{
	t_param	*p;
	sem_t	*sem;

	p = param;
	sem = p->phi->sem[p->intro.id];
	sem_wait(sem);
	sem_post(sem);
	philo_skip_first(p);
	sem_wait(sem);
	while (!p->intro.over)
	{
		sem_post(sem);
		philo_skip_loop(p);
		philo_get_forks(p);
		philo_eat(p);
		sem_wait(sem);
	}
	sem_post(sem);
	return (NULL);
}

void	introspect(t_param *p)
{
	int		time;
	sem_t	*sem;

	sem = p->phi->sem[p->intro.id];
	sem_wait(p->phi->state);
	sem_post(p->phi->state);
	sem_post(sem);
	while (1)
	{
		usleep(5);
		sem_wait(sem);
		time = get_time() - p->phi->start;
		if (p->intro.meal >= p->phi->servings || p->intro.death <= time)
		{
			p->intro.over = true;
			if (p->intro.death <= time)
				log_death(p, time);
			sem_post(sem);
			return ;
		}
		sem_post(sem);
	}
}

void intro_init(t_philo *phi, t_param *par, int i)
{
	par->intro.id = i;
	par->intro.meal = 0;
	par->intro.skip = i / 2;
	par->intro.death = phi->die;
	par->intro.over = false;
}

bool	take_seat(t_philo *phi, int i)
{
	t_param		param;
	pthread_t	think;
	bool		ret;

	param.phi = phi;
	intro_init(phi, &param, i);
	sem_wait(phi->sem[i]);
	if (!pthread_create(&think, NULL, philosophize, &param))
	{
		introspect(&param);
		pthread_join(think, NULL);
	}
	ret = param.intro.meal >= phi->servings;
	philo_destroy(phi, false);
	exit(ret);
}
