/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:45:32 by parden            #+#    #+#             */
/*   Updated: 2024/12/10 19:26:42 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

bool	mise_en_place(t_philo *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	philo->start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	philo->child = malloc(philo->nb * sizeof(pid_t));
	if (!philo->child)
		return (false);
	philo->state = sem_open("state", O_CREAT, 0600, 1);
	if (philo->state == SEM_FAILED)
		return (free(philo->child), false);
	philo->fork = sem_open("fork", O_CREAT, 0600, philo->nb);
	if (philo->fork == SEM_FAILED)
		return (free(philo->child), sem_close(philo->state),
			sem_unlink("state"), false);
	return (true);
}

bool	parse(int argc, char **argv, t_philo *input)
{
	int		i;
	int		*ptr;
	bool	err;

	input->servings = INT_MAX;
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

bool	bon_apetit(t_philo *philo)
{
	int		i;
	pid_t	curr;

	sem_wait(philo->state);
	i = 0;
	while (i < philo->nb)
	{
		curr = fork();
		if (!curr)
		{
			introspect(philo, i);
		}
		if (curr == -1)
			wrap_up(philo, -1, i, false);
		philo->child[i++] = curr;
	}
	curr = waitpid(0, NULL, WNOHANG);
	if (curr)
		wrap_up(philo, curr, INT_MAX, false);
	sem_post(philo->state);
	return (true);
}

void	reaper(t_philo *phi)
{
	int		status;
	pid_t	child;
	int		fed;

	fed = 0;
	while (fed < phi->nb)
	{
		child = waitpid(0, &status, WNOHANG);
		sem_wait(phi->state);
		if (child && !WEXITSTATUS(status))
			return (wrap_up(phi, child, INT_MAX, true));
		sem_post(phi->state);
		if (child)
			fed++;
	}
	sem_wait(phi->state);
	wrap_up(phi, -1, INT_MAX, false);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (argc < 5 || argc > 6)
		return (printf("Usage: philo nb die eat sleep [meals]\n"));
	if (!parse(argc, argv, &philo))
		return (printf("User skill issue\n"));
	if (philo.nb == 1 && philo.servings)
	{
		printf("0 1 died\n(He did not bother sitting,"
			" and committed seppuku with the fork)\n");
		return (1);
	}
	if (!mise_en_place(&philo))
		return (printf("The dining room is full\n"));
	bon_apetit(&philo);
	reaper(&philo);
}
