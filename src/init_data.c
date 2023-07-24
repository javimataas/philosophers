/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatas-p <jmatas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:50:21 by jmatas-p          #+#    #+#             */
/*   Updated: 2023/07/24 18:57:21 by jmatas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_set_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			ft_exit_error(ERR_MEMORY, &table->alive);
		i++;
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
