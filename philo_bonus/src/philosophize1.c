/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:48:49 by parden            #+#    #+#             */
/*   Updated: 2024/12/10 19:33:26 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

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

bool	intro_param_init(t_param *p, int i)
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
	return (p->sem != SEM_FAILED);
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
			break ;
		}
		sem_post(p->sem);
	}
	sem_post(p->sem);
}

void	thread_failed(t_philo *phi, t_param *param)
{
	sem_close(param->sem);
	sem_close(phi->state);
	sem_close(phi->fork);
	sem_unlink(param->str_sem);
	free(phi->child);
	exit(false);
}

bool	introspect(t_philo *phi, int i)
{
	t_param		param;
	pthread_t	think;
	bool		ret;

	param.phi = phi;
	if (!intro_param_init(&param, i))
	{
		free(phi->child);
		exit(false);
	}
	sem_wait(param.sem);
	if (pthread_create(&think, NULL, philosophize, &param))
		thread_failed(phi, &param);
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
