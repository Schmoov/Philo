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
	i = 1;
	while (i < argc)
	{
		ptr[i] = get_int(argv[i], &err);
		i++;
	}
	return (!err);
}

bool	mep_alloc(t_philo *input, t_table *table)
{
	int	n;

	n = input->nb;
	table->nb = n;
	table->chopsticks = malloc(n * sizeof(pthread_mutex_t));
	if (!table->chopsticks)
		return (false);
	table->seats = malloc(n * sizeof(t_param));
	if (!table->seats)
		return (free(table->chopsticks), false);
	return (true);
}

void	mep_chopsticks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb)
		pthread_mutex_init(&(table->chopsticks[i++]), NULL);
}

void	mep_seats(t_table *table)
{
	int		i;
	t_param *curr;

	i = 0;
	while (i < table->nb)
	{
		curr = &(table->seat[i]);

}

bool	mise_en_place(t_philo *input, t_table *table)
{
	if (!mep_alloc(input, table))
		return (false);
	mep_chopsticks(table);
	mep_seats(input, table);
	return (true);
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
	bon_apetit();
}
