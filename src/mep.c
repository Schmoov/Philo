#include "../philo.h"
#include <sys/time.h>

bool	mep_alloc(t_philo *input, t_table *table)
{
	int	n;

	n = input->nb;
	table->nb = n;
	table->thread = malloc(n * sizeof(pthread_t));
	if (!table->thread)
		return (false);
	table->fork = malloc(n * sizeof(pthread_mutex_t));
	if (!table->fork)
		return (free(table->thread), false);
	table->seat = malloc(n * sizeof(t_param));
	if (!table->seat)
		return (free(table->thread), free(table->fork), false);
	return (true);
}

void	mep_fork(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb)
		pthread_mutex_init(&(table->fork[i++]), NULL);
}

void	mep_seat(t_philo *input, t_table *table)
{
	int				i;
	t_param			*curr;

	i = 0;
	while (i < table->nb)
	{
		curr = &(table->seat[i]);
		curr->nb = table->nb;
		curr->start = table->start;
		curr->die = input->die;
		curr->eat = input->eat;
		curr->sleep = input->sleep;
		curr->id = i + 1;
		curr->meal = 0;
		curr->death = input->die;
		curr->first = &(table->fork[i ? i : table->nb - 1]);
		curr->second = &(table->fork[i ? i - 1 : 0]);
		curr->mic = &(table->mic);
		i++;
	}
}

bool	mise_en_place(t_philo *input, t_table *table)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	table->start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (!mep_alloc(input, table))
		return (false);
	pthread_mutex_init(&(table->mic), NULL);
	mep_fork(table);
	mep_seat(input, table);
	return (true);
}
