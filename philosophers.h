/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatas-p <jmatas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:08:38 by jmatas-p          #+#    #+#             */
/*   Updated: 2023/07/24 19:55:56 by jmatas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

enum e_datatype
{
	ERR_PHILO_NUM,
	ERR_ARGC,
	ERR_INT_RANGE,
	ERR_NAN,
	ERR_MEMORY,
	ERR_FORK_INIT
};

typedef struct s_table
{
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	alive_mutex;
	pthread_mutex_t	*forks;
	int				alive;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_reps;
}	t_table;

typedef struct s_philo
{
	pthread_t		philo_thread;
	pthread_mutex_t	last_eat_mutex;
	pthread_mutex_t	eat_count_mutex;
	int				first_fork;
	int				second_fork;
	int				id;
	int				eat_count;
	int				last_eat;
	t_table			*table;
}	t_philo;

// UTILS.C
int		ft_atoi(char *str, t_table *table);
void	ft_exit_error(int n, int *alive);
void	ft_print_table(t_table *table);
void	ft_print_philos(t_philo **philos, t_table *table);

// INIT_DATA.C
void	ft_init_table(t_table *table, int argc, char **argv);
t_philo	**ft_init_philos(t_table *table);

// CLEAN_DATA.C
void	ft_clean_data(t_table *table, t_philo **philos);

// ALIVE.C
int		ft_should_continue(t_table *table);

#endif