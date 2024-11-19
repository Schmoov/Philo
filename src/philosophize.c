#include "../philo.h"

void	philo_eat(t_param *param)
{
	struct timeval	time;

	pthread_mutex_lock(param->first);
	log_fork(param);
	pthread_mutex_lock(param->second);
	gettimeofday(&time, NULL);
	param->death = time.tv_sec * 1e3 + time.tv_usec / 1e3 + param->eat;
	log_eat(param);
	usleep(param->eat * 1e3);
}

void	philo_sleep(t_param *param)
{
		log_sleep(param);
		usleep(param->sleep * 1e3);
		log_think(param);
}

void	philosophize(t_param *param)
{
	while (1)
	{
		philo_eat(param);
		philo_sleep(param);
	}
}
