#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo {
	int	nb;
	int	die;
	int	eat;
	int	sleep;
	int	meals;
}		t_philo;

typedef struct s_param {
	int				die;
	int				eat;
	int				sleep;
	int				meals;

	int				id;
	int				death;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;
	pthread_mutex_t	*mic;
}					t_param;

typedef struct s_table {
	int				nb;
	pthread_mutex_t	*chopstick;
	t_param			*seat;
}					t_table;

int	get_int(char *nptr, bool *err);

void	log_fork(t_param *param);
void	log_eat(t_param *param);
void	log_sleep(t_param *param);
void	log_think(t_param *param);

void	philo_eat(t_param *param);
void	philo_sleep(t_param *param);
void	philosophize(t_param *param);
#endif
