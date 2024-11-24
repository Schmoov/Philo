#include "../philo.h"
#include <pthread.h>
#include <sys/time.h>

bool	parse(int argc, char **argv, t_philo *input)
{
	int		i;
	int		*ptr;
	bool	err;

	input->meals = INT_MAX;
	ptr = (int *)input;
	err = false;
	i = 0;
	while (i + 1 < argc)
	{
		ptr[i] = get_int(argv[i + 1], &err);
		i++;
	}
	return (!err);
}

void	bon_apetit(t_philo *input, t_table *table)
{
	int			i;
	pthread_t	curr;

	i = 0;
	while (i < input->nb)
	{
		pthread_create(&curr, NULL, philosophize, &(table->seat[i]));
		table->thread[i] = curr;
		i++;
	}
}

void	reaper(t_philo *input, t_table *table)
{
	int				i;
	int				time;
	struct timeval	tv;

	while (1)
	{
		usleep(5);
		i = 0;
		gettimeofday(&tv, NULL);
		time = tv.tv_sec * 1000 + tv.tv_usec / 1000 - table->start;
		while (i < input->nb)
		{
			if (table->seat[i].death < time)
			{
				printf("%d %d died (%d)\n", time, i + 1, table->seat[i].death);
				exit(69);
			}
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	t_philo	input;
	t_table	table;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: philo nb die eat sleep [meals]\n");
		return (1);
	}
	if (!parse(argc, argv, &input))
	{
		printf("User skill issue\n");
		return (1);
	}
	if(!mise_en_place(&input, &table))
	{
		printf("The dining room is full\n");
		return (1);
	}
	bon_apetit(&input, &table);
	reaper(&input, &table);
}
