/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatas-p <jmatas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:18:51 by jmatas-p          #+#    #+#             */
/*   Updated: 2023/07/24 18:57:29 by jmatas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_exit_error(int n, int *alive)
{
	if (*alive == 0)
		return ;
	if (n == ERR_PHILO_NUM)
		printf("Error, the number of philosophers must be between 1 and 200\n");
	if (n == ERR_ARGC)
		printf("Error, the program must receive 4 or 5 arguments\n");
	if (n == ERR_INT_RANGE)
		printf("Error, the arguments received must be in the range of 'int'\n");
	if (n == ERR_NAN)
		printf("Error, the program must receive numbers\n");
	if (n == ERR_MEMORY)
		printf("Error, memory allocation / mutex init failed\n");
	*alive = 0;
}

int	ft_atoi(char *str, t_table *table)
{
	int				i;
	long long int	nbr;

	i = 0;
	nbr = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != '\0')
		ft_exit_error(ERR_NAN, &table->alive);
	i = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nbr = (nbr * 10) + (str[i] - '0');
		i++;
	}
	if (nbr > INT_MAX || nbr < INT_MIN)
		ft_exit_error(ERR_INT_RANGE, &table->alive);
	return (nbr);
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
