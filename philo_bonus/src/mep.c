#include "../philo_bonus.h"

void	mep_sem_str(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->nb)
	{
		p->str_sem[i][0] = 'I';
		p->str_sem[i][1] = '0' + (i + 1) / 100;
		p->str_sem[i][2] = '0' + ((i + 1) / 10 % 10);
		p->str_sem[i][3] = '0' + ((i + 1) % 10);
		p->str_sem[i][4] = 0;
		i++;
	}
}

void	mep_sem_unlink(t_philo *p)
{
	int	i;

	sem_close(p->state);
	sem_unlink("state");
	sem_close(p->fork);
	sem_unlink("fork");
	i = 0;
	while (i < p->nb && p->sem[i] != SEM_FAILED)
	{
		sem_close(p->sem[i]);
		sem_unlink(p->str_sem[i++]);
	}
}

void	mep_sem_close(t_philo *p)
{
	int	i;

	sem_close(p->state);
	sem_close(p->fork);
	i = 0;
	while (i < p->nb && p->sem[i] != SEM_FAILED)
		sem_close(p->sem[i++]);
}

bool	mep_sem(t_philo *p)
{
	int	i;

	p->state = sem_open("state", O_CREAT, 0600, 1);
	if (p->state == SEM_FAILED)
		return (false);
	p->fork = sem_open("fork", O_CREAT, 0600, p->nb);
	if (p->fork == SEM_FAILED)
		return (sem_close(p->state), sem_unlink("state"), false);
	i = 0;
	while (i < p->nb)
	{
		p->sem[i] = sem_open(p->str_sem[i], O_CREAT, 0600, 1);
		if (p->sem[i] == SEM_FAILED)
			return (mep_sem_unlink(p), false);
		i++;
	}
	return (true);
}

bool	mep_alloc(t_philo *p)
{
	p->str_sem = malloc(p->nb * 5);
	if (!p->str_sem)
		return (false);
	p->child = malloc(p->nb * sizeof(pid_t));
	if (!p->child)
		return (free(p->str_sem), false);
	p->sem = malloc(p->nb * sizeof(sem_t));
	if (!p->sem)
		return (free(p->str_sem), free(p->child), false);
	return (true);
}

void	mep_free(t_philo *p)
{
	free(p->str_sem);
	free(p->child);
	free(p->sem);
}

bool	mise_en_place(t_philo *p)
{
	p->start = get_time();
	if (!mep_alloc(p))
		return (false);
	memset(p->child, -1, p->nb * sizeof(pid_t));
	mep_sem_str(p);
	if (!mep_sem(p))
		return (mep_free(p), false);
	return (true);
}

void	philo_destroy(t_philo *p, bool unlink)
{
	if (unlink)
		mep_sem_unlink(p);
	else
		mep_sem_close(p);
	mep_free(p);
}
