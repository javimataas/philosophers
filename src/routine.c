/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatas-p <jmatas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:37:02 by jmatas-p          #+#    #+#             */
/*   Updated: 2023/09/28 20:05:18 by jmatas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_sleep(t_philo *philo)
{
	long long int	end_time;

	if (philo->table->time_to_sleep == 0)
		return ;
	ft_print_philo_status(philo, SLEEPING);
	end_time = ft_get_cur_time(philo->table) + philo->table->time_to_sleep;
	while (ft_get_cur_time(philo->table) < end_time)
	{
		if (!ft_should_continue(philo->table))
			break ;
		usleep(50);
	}
}

void	ft_think(t_philo *philo, int status)
{
	long long int	time_stop_thinking;

	pthread_mutex_lock(&philo->last_eat_mutex);
	time_stop_thinking = (philo->table->time_to_die
			- ft_get_cur_time(philo->table)
			- philo->last_eat - philo->table->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->last_eat_mutex);
	if (time_stop_thinking < 0)
		time_stop_thinking = 0;
	if (time_stop_thinking == 0 && status == -1)
		time_stop_thinking = 1;
	if (time_stop_thinking > 700)
		time_stop_thinking = 200;
	if (philo->table->time_to_sleep == 0
		&& (philo->table->time_to_die / 2) > philo->table->time_to_eat)
		time_stop_thinking = 10;
	if (time_stop_thinking != 0)
		ft_print_philo_status(philo, status);
	while (ft_get_cur_time(philo->table) < time_stop_thinking)
	{
		if (!ft_should_continue(philo->table))
			break ;
		usleep(50);
	}
}

void	ft_eat(t_philo *philo)
{
	long long int	time_stop_eating;

	if (philo->table->eat_reps == 0)
		return ;
	pthread_mutex_lock(&philo->table->forks[philo->first_fork]);
	ft_print_philo_status(philo, STARTING);
	pthread_mutex_lock(&philo->table->forks[philo->second_fork]);
	ft_print_philo_status(philo, STARTING);
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->last_eat = ft_get_cur_time(philo->table);
	ft_print_philo_status(philo, EATING);
	pthread_mutex_unlock(&philo->last_eat_mutex);
	time_stop_eating = ft_get_cur_time(philo->table)
		+ philo->table->time_to_eat;
	while (ft_get_cur_time(philo->table) < time_stop_eating)
	{
		if (!ft_should_continue(philo->table))
			break ;
		usleep(50);
	}
	pthread_mutex_lock(&philo->eat_count_mutex);
	philo->eat_count += 1;
	pthread_mutex_unlock(&philo->eat_count_mutex);
	pthread_mutex_unlock(&philo->table->forks[philo->first_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->second_fork]);
}

void	*ft_philo_start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->time_to_die == 0)
		return (NULL);
	while (philo->table->start_time > ft_get_init_time())
		usleep(100);
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->last_eat = ft_get_cur_time(philo->table);
	pthread_mutex_unlock(&philo->last_eat_mutex);
	if (philo->id % 2)
		ft_think(philo, -1);
	while (ft_should_continue(philo->table))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo, THINKING);
	}
	return (NULL);
}

void	*ft_one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->eat_reps == 0)
		return (NULL);
	if (philo->table->time_to_die == 0)
		return (NULL);
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->last_eat = ft_get_cur_time(philo->table);
	pthread_mutex_unlock(&philo->last_eat_mutex);
	while (philo->table->start_time > ft_get_init_time())
		usleep(10);
	pthread_mutex_lock(&philo->table->forks[0]);
	ft_print_philo_status(philo, STARTING);
	pthread_mutex_unlock(&philo->table->forks[0]);
	while (ft_should_continue(philo->table))
		usleep(100);
	return (NULL);
}
