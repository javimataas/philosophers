/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatas-p <jmatas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:37:46 by jmatas-p          #+#    #+#             */
/*   Updated: 2023/07/24 19:42:49 by jmatas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_join_philos(t_philo **philos, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		pthread_join(philos[i]->philo_thread, NULL);
		i++;
	}
}

void	ft_free_philos(t_philo **philos)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		pthread_mutex_destroy(&philos[i]->last_eat_mutex);
		pthread_mutex_destroy(&philos[i]->eat_count_mutex);
		free(philos[i]);
		i++;
	}
	free(philos);
}

void	ft_free_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philosophers - 1)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->table_mutex);
	free(table->forks);
}

void	ft_clean_data(t_table *table, t_philo **philos)
{
	usleep(100000);
	//ft_join_philos(philos, table);
	ft_free_philos(philos);
	ft_free_table(table);
}
