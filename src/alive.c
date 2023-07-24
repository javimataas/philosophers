/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alive.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatas-p <jmatas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:55:30 by jmatas-p          #+#    #+#             */
/*   Updated: 2023/07/24 19:59:04 by jmatas-p         ###   ########.fr       */
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
		return (0);
}
