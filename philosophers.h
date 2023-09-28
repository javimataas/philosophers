/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatas-p <jmatas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:08:38 by jmatas-p          #+#    #+#             */
/*   Updated: 2023/09/27 19:43:00 by jmatas-p         ###   ########.fr       */
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

enum e_errors
{
	ERR_PHILO_NUM,
	ERR_ARGC,
	ERR_INT_RANGE,
	ERR_NAN,
	ERR_MEMORY,
	ERR_FORK_INIT,
	ERR_PTHREAD
};

enum e_states
{
	STARTING,
	THINKING,
	SLEEPING,
	EATING,
	DEAD
};

typedef struct s_table
{
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	alive_mutex;
	pthread_mutex_t	*forks;
	int				alive;
	int				number_of_philosophers;
	long long		start_time;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
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
int			ft_atoi(char *str, t_table *table);
void		ft_exit_error(int n, int *alive);
void		ft_print_philo_status(t_philo *philo, int status);

// INIT_DATA.C
void		ft_init_table(t_table *table, int argc, char **argv);
t_philo		**ft_init_philos(t_table *table);

// CLEAN_DATA.C
void		ft_clean_data(t_table *table, t_philo **philos);

// ALIVE.C
int			ft_should_continue(t_table *table);
void		ft_start_meal(t_philo **philos, t_table *table);
void		ft_keep_loop(t_philo **philos);

// TIME.C
long long	ft_get_init_time(void);
long long	ft_get_cur_time(t_table *table);

// ROUTINE.C
void		*ft_philo_start(void *arg);
void		*ft_one_philo(void *arg);

#endif
