#include "../philo_bonus.h"

void	clean_up(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->nb)
	{
		if (p->child[i] != -1 && kill(p->child[i], 0))
		{
			kill(p->child[i], SIGTERM);
			waitpid(p->child[i], NULL, 0);
		}
		i++;
	}
	philo_destroy(p);
}

void	bon_apetit(t_philo *philo)
{
	int		i;
	pid_t	curr;

	sem_wait(philo->state);
	i = 0;
	while (i < philo->nb)
	{
		curr = fork();
		if (!curr)
			introspect(philo, i);
		philo->child[i++] = curr;
		if (curr == -1)
			return (clean_up(philo));
	}
	sem_post(philo->state);
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

