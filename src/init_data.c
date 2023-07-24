/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatas-p <jmatas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:50:21 by jmatas-p          #+#    #+#             */
/*   Updated: 2023/07/24 19:36:01 by jmatas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_set_forks(t_table *table)
{
	int	i;

	i = 1;
	while (i < table->number_of_philosophers)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			ft_exit_error(ERR_MEMORY, &table->alive);
		i++;
	}
}

void	ft_init_philo_forks(t_philo *philo)
{
	if (!(philo->id % 2))
	{
		philo->first_fork = (philo->id) % philo->table->number_of_philosophers;
		philo->second_fork = philo->id - 1;
	}
	else
	{
		philo->first_fork = philo->id - 1;
		philo->second_fork = (philo->id) % philo->table->number_of_philosophers;
	}
}

void	ft_init_table(t_table *table, int argc, char **argv)
{
	table->number_of_philosophers = ft_atoi(argv[1], table);
	if (table->number_of_philosophers == 0
		|| table->number_of_philosophers > 200)
		ft_exit_error(ERR_PHILO_NUM, &table->alive);
	table->time_to_die = ft_atoi(argv[2], table);
	table->time_to_eat = ft_atoi(argv[3], table);
	table->time_to_sleep = ft_atoi(argv[4], table);
	if (argc == 6)
		table->eat_reps = ft_atoi(argv[5], table);
	else
		table->eat_reps = -1;
	if (pthread_mutex_init(&table->table_mutex, NULL))
		ft_exit_error(ERR_MEMORY, &table->alive);
	table->forks = malloc(sizeof(pthread_mutex_t)
			* table->number_of_philosophers);
	if (!table->forks)
		ft_exit_error(ERR_MEMORY, &table->alive);
	ft_set_forks(table);
}

t_philo	**ft_init_philos(t_table *table)
{
	int		i;
	t_philo	**philos;

	i = 0;
	philos = malloc(sizeof(t_philo *) * (table->number_of_philosophers + 1));
	if (!philos)
		ft_exit_error(ERR_MEMORY, &table->alive);
	while (i < table->number_of_philosophers)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			ft_exit_error(ERR_MEMORY, &table->alive);
		philos[i]->id = i + 1;
		philos[i]->table = table;
		philos[i]->eat_count = 0;
		philos[i]->last_eat = 0;
		if (pthread_mutex_init(&philos[i]->eat_count_mutex, NULL))
			ft_exit_error(ERR_MEMORY, &table->alive);
		if (pthread_mutex_init(&philos[i]->last_eat_mutex, NULL))
			ft_exit_error(ERR_MEMORY, &table->alive);
		ft_init_philo_forks(philos[i]);
		i++;
	}
	philos[i] = NULL;
	return (philos);
}
