/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alive.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatas-p <jmatas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:55:30 by jmatas-p          #+#    #+#             */
/*   Updated: 2023/09/28 19:51:43 by jmatas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	ft_should_continue(t_table *table)
{
	pthread_mutex_lock(&table->alive_mutex);
	if (table->alive == 1)
	{
		pthread_mutex_unlock(&table->alive_mutex);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&table->alive_mutex);
		return (0);
	}
}

void	ft_start_meal(t_philo **philos, t_table *table)
{
	int	c;

	c = 0;
	table->start_time = (table->number_of_philosophers * 2 * 10)
		+ ft_get_init_time();
	if (table->number_of_philosophers == 1)
	{
		table->start_time = ft_get_init_time();
		if (pthread_create(&philos[c]->philo_thread,
				NULL, &ft_one_philo, philos[c]) != 0)
			ft_exit_error(ERR_PTHREAD, &table->alive);
		return ;
	}
	while (philos[c])
	{
		if (pthread_create(&philos[c]->philo_thread, NULL, &ft_philo_start,
				philos[c]) != 0)
			ft_exit_error(5, &table->alive);
		c++;
	}
}

int	ft_dead_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_eat_mutex);
	if ((ft_get_cur_time(philo->table) - philo->last_eat)
		>= philo->table->time_to_die)
	{
		pthread_mutex_unlock(&philo->last_eat_mutex);
		pthread_mutex_lock(&philo->table->alive_mutex);
		philo->table->alive = 0;
		pthread_mutex_unlock(&philo->table->alive_mutex);
		ft_print_philo_status(philo, DEAD);
		return (1);
	}
	pthread_mutex_unlock(&philo->last_eat_mutex);
	return (0);
}

int	ft_philo_ok(t_philo **philos)
{
	int	i;
	int	full;

	full = 1;
	i = 0;
	while (philos[i])
	{
		if (ft_dead_philo(philos[i]))
			return (1);
		pthread_mutex_lock(&philos[i]->eat_count_mutex);
		if (philos[i]->table->eat_reps == -1
			|| philos[i]->eat_count < philos[i]->table->eat_reps)
			full = 0;
		pthread_mutex_unlock(&philos[i]->eat_count_mutex);
		i++;
	}
	i = 0;
	if (full)
	{
		pthread_mutex_lock(&philos[i]->table->alive_mutex);
		philos[i]->table->alive = 0;
		pthread_mutex_unlock(&philos[i]->table->alive_mutex);
	}
	return (full);
}

void	ft_keep_loop(t_philo **philos)
{
	while (1)
	{
		if (ft_philo_ok(philos))
			break ;
	}
}
