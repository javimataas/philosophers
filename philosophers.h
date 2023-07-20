/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatas-p <jmatas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:08:38 by jmatas-p          #+#    #+#             */
/*   Updated: 2023/07/20 18:43:00 by jmatas-p         ###   ########.fr       */
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
	ERR_NAN
};

typedef struct s_table
{
	int	alive;
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_reps;
}	t_table;

//UTILS.C
int		ft_atoi(char *str, t_table *table);
void	ft_exit_error(int n, int *alive);

#endif