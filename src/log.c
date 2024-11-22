#include "../philo.h"

void	log_fork(t_param *param)
{
	struct timeval	time;
	int				ms;

	pthread_mutex_lock(param->mic);
	gettimeofday(&time, NULL);
	ms =  time.tv_sec * 1000 + time.tv_usec / 1000;
	printf("%d %d has taken a fork\n", ms, param->id);
	pthread_mutex_unlock(param->mic);
}

void	log_eat(t_param *param)
{
	struct timeval	time;
	int				ms;

	pthread_mutex_lock(param->mic);
	gettimeofday(&time, NULL);
	ms =  time.tv_sec * 1000 + time.tv_usec / 1000;
	printf("%d %d is eating\n", ms, param->id);
	pthread_mutex_unlock(param->mic);
}

void	log_sleep(t_param *param)
{
	struct timeval	time;
	int				ms;

	pthread_mutex_lock(param->mic);
	gettimeofday(&time, NULL);
	ms =  time.tv_sec * 1000 + time.tv_usec / 1000;
	printf("%d %d is sleeping\n", ms, param->id);
	pthread_mutex_unlock(param->mic);
}

void	log_think(t_param *param)
{
	struct timeval	time;
	int				ms;

	pthread_mutex_lock(param->mic);
	gettimeofday(&time, NULL);
	ms =  time.tv_sec * 1000 + time.tv_usec / 1000;
	printf("%d %d is thinking\n", ms, param->id);
	pthread_mutex_unlock(param->mic);
}
