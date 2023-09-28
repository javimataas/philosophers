/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatas-p <jmatas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:18:51 by jmatas-p          #+#    #+#             */
/*   Updated: 2023/09/27 19:43:46 by jmatas-p         ###   ########.fr       */
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
	if (n == ERR_PTHREAD)
		printf("Error, wrong thread creation\n");
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

void	ft_print_philo_status(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->table->table_mutex);
	if (status == DEAD)
		printf("%lld %d %s\n", ft_get_cur_time(philo->table),
			philo->id, "died");
	if (!ft_should_continue(philo->table))
	{
		pthread_mutex_unlock(&philo->table->table_mutex);
		return ;
	}
	if (status == STARTING)
		printf("%lld %d %s\n", ft_get_cur_time(philo->table), philo->id,
			"has taken a fork");
	if (status == EATING)
		printf("%lld %d %s\n", ft_get_cur_time(philo->table), philo->id,
			"is eating");
	if (status == SLEEPING)
		printf("%lld %d %s\n", ft_get_cur_time(philo->table), philo->id,
			"is sleeping");
	if (status == THINKING)
		printf("%lld %d %s\n", ft_get_cur_time(philo->table), philo->id,
			"is thinking");
	pthread_mutex_unlock(&philo->table->table_mutex);
}
