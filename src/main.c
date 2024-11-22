#include "../philo.h"
#include <pthread.h>

bool	parse(int argc, char **argv, t_philo *input)
{
	int		i;
	int		*ptr;
	bool	err;

	input->meals = 0;
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

void	reaper()
{
	sleep(120);
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
	reaper();
}
