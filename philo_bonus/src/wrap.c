/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:26:13 by parden            #+#    #+#             */
/*   Updated: 2025/01/24 14:52:02 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	main_destroy(t_philo *phi)
{
	free(phi->child);
	sem_close(phi->fork);
	sem_unlink("fork");
	sem_close(phi->state);
	sem_unlink("state");
	exit(420);
}

