#include "../philo.h"

void	philo_skip_first(t_param *param)
{
	if (!(param->id % 2))
		usleep(param->eat * 1000);
}

void	philo_skip_loop(t_param *param)
{
	if (param->nb % 2)
	{
		if (param->id == param->skip + 1)
		{
			usleep(param->eat * 1000 * 2);
			param->skip = (param->skip + 1) % param->nb;
		}
	}
}

void	philo_eat(t_param *param)
{
	struct timeval	time;

	pthread_mutex_lock(param->first);
	log_fork(param);
	pthread_mutex_lock(param->second);
	gettimeofday(&time, NULL);
	param->death = time.tv_sec * 1000 + time.tv_usec / 1000 + param->die - param->start;
	log_eat(param);
	param->skip = (param->skip + 2) % param->nb;
	usleep(param->eat * 1000);
	param->meal++;
	pthread_mutex_unlock(param->first);
	pthread_mutex_unlock(param->second);
}

void	philo_sleep(t_param *param)
{
		log_sleep(param);
		usleep(param->sleep * 1000);
		log_think(param);
}

void	*philosophize(void *param)
{
	t_param	*p;

	p = param;
	philo_skip_first(p);
	while (1)
	{
		philo_skip_loop(p);
		philo_eat(p);
		philo_sleep(p);
	}
	return (NULL);
}
