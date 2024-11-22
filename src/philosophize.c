#include "../philo.h"

void	philo_eat(t_param *param)
{
	struct timeval	time;

	pthread_mutex_lock(param->first);
	log_fork(param);
	pthread_mutex_lock(param->second);
	gettimeofday(&time, NULL);
	param->death = time.tv_sec * 1000 + time.tv_usec / 1000 + param->eat;
	log_eat(param);
	usleep(param->eat * 1000);
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
	while (1)
	{
		philo_eat(p);
		philo_sleep(p);
	}
	return (NULL);
}
