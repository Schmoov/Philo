/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:45:32 by parden            #+#    #+#             */
/*   Updated: 2024/12/09 15:06:11 by parden           ###   ########.fr       */
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
	philo->fork = sem_open("fork", O_CREAT, 0600, 2 * philo->nb);
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
		philo->child[i++] = curr;
	}
	sem_post(philo->state);
	return (true);
}

void wrap_up(t_philo *phi, pid_t child)
{
	int				i;
	struct timeval	time;
	int				ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000 - phi->start;
	i = 0;
	while (i < phi->nb)
	{
		if (kill(phi->child[i], 0))
			kill(phi->child[i], SIGTERM);
		if (phi->child[i] == child)
			printf("%d %d died\n", ms, i + 1);
		i++;
	}

	while (i < phi->nb)
	{
		if (i != child)
			waitpid(phi->child[i], NULL, 0);
		i++;
	}
	free(phi->child);
	sem_close(phi->fork);
	sem_unlink("fork");
	sem_close(phi->state);
	sem_unlink("state");
}

void reaper(t_philo *phi)
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
			return (wrap_up(phi, child));
		sem_post(phi->state);
		if (child)
			fed++;
	}
	sem_wait(phi->state);
	wrap_up(phi, -1);
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
	//wrap_up(&philo, &table);
}
