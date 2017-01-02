/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/31 19:40:06 by kcosta            #+#    #+#             */
/*   Updated: 2017/01/02 13:57:40 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static long				ft_pow(int nbr, int power)
{
	long	result;

	if (power < 0)
		return (-1);
	result = 1;
	while (power--)
		result *= nbr;
	return (result);
}

static unsigned long	ft_sqrt(long nbr)
{
	unsigned long	result;

	if (nbr <= 0)
		return (0);
	result = 1;
	while (result * result < (unsigned long)nbr)
		result++;
	return (result);
}

unsigned long			ft_absolute_distance(t_vector pos1, t_vector pos2)
{
	return (ft_sqrt(ft_pow(pos1.x - pos2.x, 2) + ft_pow(pos1.y - pos2.y, 2)));
}

t_vector				nearest_opponent(char opponent)
{
	t_vector	pos;
	char		**board;

	board = *get_board();
	pos.y = (opponent == 'O') ? -1 : get_dim()->y;
	pos.x = -1;
	while ((opponent == 'O') ? ++pos.y < get_dim()->y : --pos.y)
	{
		pos.x = (opponent == 'O') ? -1 : get_dim()->x;
		while ((opponent == 'O') ? ++pos.x < get_dim()->x : --pos.x)
		{
			if ((opponent == 'O') ? board[pos.y][pos.x] == 'O'
								|| board[pos.y][pos.x] == 'o' :
									board[pos.y][pos.x] == 'X'
								|| board[pos.y][pos.x] == 'x')
				return (pos);
		}
	}
	return (pos);
}
