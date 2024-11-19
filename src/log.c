#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct {
	int				die;
	int				eat;
	int				sleep;

	int				id;
	int				death;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;
	pthread_mutex_t	*mic;
}					t_param;

void	log_fork(t_param *param)
{
	struct timeval	time;
	int				ms;

	pthread_mutex_lock(param->mic);
	gettimeofday(&time, NULL);
	ms =  time.tv_sec * 1e3 + time.tv_usec / 1e3;
	printf("%d %d has taken a fork\n", ms, param->id);
	pthread_mutex_unlock(param->mic);
}

void	log_eat(t_param *param)
{
	struct timeval	time;
	int				ms;

	pthread_mutex_lock(param->mic);
	gettimeofday(&time, NULL);
	ms =  time.tv_sec * 1e3 + time.tv_usec / 1e3;
	printf("%d %d is eating\n", ms, param->id);
	pthread_mutex_unlock(param->mic);
}

void	log_sleep(t_param *param)
{
	struct timeval	time;
	int				ms;

	pthread_mutex_lock(param->mic);
	gettimeofday(&time, NULL);
	ms =  time.tv_sec * 1e3 + time.tv_usec / 1e3;
	printf("%d %d is sleeping\n", ms, param->id);
	pthread_mutex_unlock(param->mic);
}

void	log_think(t_param *param)
{
	struct timeval	time;
	int				ms;

	pthread_mutex_lock(param->mic);
	gettimeofday(&time, NULL);
	ms =  time.tv_sec * 1e3 + time.tv_usec / 1e3;
	printf("%d %d is thinking\n", ms, param->id);
	pthread_mutex_unlock(param->mic);
}

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
