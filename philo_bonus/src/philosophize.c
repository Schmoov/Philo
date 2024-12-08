/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:48:49 by parden            #+#    #+#             */
/*   Updated: 2024/12/08 21:35:23 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	philo_skip_first(t_param *p)
{
	if (p->intro.id % 2)
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
	struct timeval	time;

	sem_wait(p->phi->fork);
	log_fork(p);
	sem_wait(p->phi->fork);
	gettimeofday(&time, NULL);
	sem_wait(p->sem);
	p->intro.death = time.tv_sec * 1000 + time.tv_usec / 1000
		+ p->phi->die - p->phi->start;
	sem_post(p->sem);
}

void	philo_eat(t_param *p)
{
	log_eat(p);
	usleep(p->phi->eat * 1000);
	sem_wait(p->sem);
	p->intro.meal++;
	sem_post(p->sem);
	p->intro.skip++;
	sem_post(p->phi->fork);
	sem_post(p->phi->fork);
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
	p->str_sem[0] = 'I';
	p->str_sem[1] = '0' + (i + 1) / 100;
	p->str_sem[2] = '0' + ((i + 1) / 10 % 10);
	p->str_sem[3] = '0' + ((i + 1) % 10);
	p->str_sem[4] = 0;
	p->intro.id = i + 1;
	p->intro.meal = 0;
	p->intro.skip = i / 2;
	p->intro.death = p->phi->die;
	p->intro.over = false;
	p->sem = sem_open(p->str_sem, O_CREAT, 0600, 1);

}

void	introspect_loop(t_param *p)
{
	int				time;
	struct timeval	tv;

	sem_wait(p->phi->state);
	sem_post(p->phi->state);
	sem_post(p->sem);
	while (1)
	{
		usleep(5);
		gettimeofday(&tv, NULL);
		time = tv.tv_sec * 1000 + tv.tv_usec / 1000 - p->phi->start;
		sem_wait(p->sem);
		if (p->intro.meal >= p->phi->servings || p->intro.death <= time)
		{
			p->intro.over = true;
			break;
		}
		sem_post(p->sem);
	}
	sem_post(p->sem);
}

bool	introspect(t_philo *phi, int i)
{
	t_param		param;
	pthread_t	think;
	bool		ret;


	param.phi = phi;
	intro_param_init(&param, i);
	sem_wait(param.sem);
	pthread_create(&think, NULL, philosophize, &param);
	introspect_loop(&param);
	pthread_join(think, NULL);
	sem_close(param.sem);
	sem_close(phi->state);
	sem_close(phi->fork);
	sem_unlink(param.str_sem);
	ret = param.intro.meal >= phi->servings;
	free(phi->child);
	exit(ret);
}
