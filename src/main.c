/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatas-p <jmatas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:02:47 by jmatas-p          #+#    #+#             */
/*   Updated: 2023/07/24 19:55:39 by jmatas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_leaks(void)
{
	system("leaks -q philo");
}
//atexit(ft_leaks);

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	**philos;

	atexit(ft_leaks);
	table.alive = 1;
	if (argc == 5 || argc == 6)
	{
		ft_init_table(&table, argc, argv);
		philos = ft_init_philos(&table);
		if (ft_should_continue(&table))
		{
			//Begin simulation
			printf("Begin simulation\n");
		}
		usleep(1000);
		ft_clean_data(&table, philos);
	}
	else
		ft_exit_error(ERR_ARGC, &table.alive);
	return (0);
}
