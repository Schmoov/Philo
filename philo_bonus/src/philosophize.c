/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:48:49 by parden            #+#    #+#             */
/*   Updated: 2024/12/07 19:08:18 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	philo_skip_first(t_param *p)
{
	if (p->id % 2)
		usleep(p->phi->eat * 1000);
}

void	philo_skip_loop(t_param *p)
{
	if (p->phi->nb % 2)
	{
		if (p->skip == p->phi->nb / 2)
		{
			p->skip = 0;
			usleep(p->phi->eat * 1000);
		}
	}
}

void	philo_get_forks(t_param *p)
{
	struct timeval	time;

	sem_wait(p->fork);
	log_fork(p);
	sem_wait(p->fork);
	gettimeofday(&time, NULL);
	sem_wait(p->state);
	p->death = time.tv_sec * 1000 + time.tv_usec / 1000
		+ p->phi->die - p->phi->start;
	sem_post(p->state);
}

void	philo_eat(t_param *p)
{
	log_eat(p);
	usleep(p->phi->eat * 1000);
	sem_wait(p->state);
	p->meal++;
	sem_post(p->state);
	p->skip++;
	sem_post(p->fork);
	sem_post(p->fork);
	log_sleep(p);
	usleep(p->phi->sleep * 1000);
	log_think(p);
}

void	*philosophize(void *param)
{
	t_param	*p;

	p = param;
	sem_wait(p->sem);
	sem_post(p->sem);
	philo_skip_first(p);
	sem_wait(p->sem);
	while (!p->intro.over)
	{
		sem_post(p->sem);
		philo_skip_loop(p);
		philo_get_forks(p);
		philo_eat(p);
		sem_wait(p->sem);
	}
	sem_post(p->sem);
	return (NULL);
}

void	intro_param_init(t_param *p, int i)
{
	char	sem[9] = "intro";

	sem[5] = '0' + (i + 1) / 100;
	sem[6] = '0' + ((i + 1) / 10 % 10);
	sem[7] = '0' + ((i + 1) % 10);
	sem[8] = 0;
	p->intro.id = i + 1;
	p->intro.meal = 0;
	p->intro.skip = i / 2;
	p->intro.death = p->phi->die;
	p->intro.over = false;
	p->sem = sem_open(sem, O_CREAT, 0600, 1);

}

bool	introspect(t_philo *phi, int i)
{
	t_param		param;
	pthread_t	think;


	param.phi = phi;
	intro_param_init(&param, i);
	sem_wait(param.sem);
	pthread_create(&think, NULL, philosophize, &param);
	sem_wait(phi->state);
	sem_post(phi->state);
	sem_post(param.sem);
	while (1)
	{
		usleep(5);
		sem_wait(param.sem);
		if (param.intro.meal >= phi->servings)
		{
			param.intro.over = true;
			break;
		}
		if (param.intro.death <= time)
		{
			param.intro.over = true;
			break;
		}
		sem_post(param.sem);
	}
	sem_post(param.sem);
	pthread_join(think, NULL);
	free(phi->child);
	return (param.intro.meal >= phi->servings);
}
