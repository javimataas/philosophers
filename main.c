/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatas-p <jmatas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:02:47 by jmatas-p          #+#    #+#             */
/*   Updated: 2023/07/20 18:52:18 by jmatas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_leaks(void)
{
	system("leaks -q philo");
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
}

void	ft_print_table(t_table *table)
{
	printf("number_of_philosophers: %d\n", table->number_of_philosophers);
	printf("time_to_die: %d\n", table->time_to_die);
	printf("time_to_eat: %d\n", table->time_to_eat);
	printf("time_to_sleep: %d\n", table->time_to_sleep);
	if (table->eat_reps != -1)
		printf("eat_reps: %d\n", table->eat_reps);
	else
		printf("eat_reps: null\n");
}

int	main(int argc, char **argv)
{
	t_table	table;

	atexit(ft_leaks);
	table.alive = 1;
	if (argc == 5 || argc == 6)
	{
		ft_init_table(&table, argc, argv);
		ft_print_table(&table);
	}
	else
		ft_exit_error(ERR_ARGC, &table.alive);
	return (0);
}
