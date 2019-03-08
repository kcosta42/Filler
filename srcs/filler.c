/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 14:18:20 by kcosta            #+#    #+#             */
/*   Updated: 2017/01/02 13:58:36 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int		valid_pos(t_piece piece, t_vector pos)
{
	char		**board;
	t_byte		index;
	t_vector	curr;
	int			used;

	board = *get_board();
	index = -1;
	used = 0;
	while (++index < piece.count)
	{
		curr.x = pos.x + piece.snippet[index].x;
		curr.y = pos.y + piece.snippet[index].y;
		if (curr.x < 0 || curr.y < 0 ||
			curr.x >= get_dim()->x || curr.y >= get_dim()->y)
			return (0);
		if (board[curr.y][curr.x] != '.')
			used++;
		if (used > 1)
			return (0);
	}
	return (1);
}

static t_byte	count_block(t_piece piece, t_vector pos, char c, char c2)
{
	char		**board;
	t_byte		count;
	t_byte		index;
	t_vector	curr;

	board = *get_board();
	index = -1;
	count = 0;
	while (++index < piece.count)
	{
		curr.x = pos.x + piece.snippet[index].x;
		curr.y = pos.y + piece.snippet[index].y;
		if (curr.x + 1 >= get_dim()->x || curr.y + 1 >= get_dim()->y
			|| curr.x - 1 < 0 || curr.y - 1 < 0)
			return (0);
		count += (board[curr.y][curr.x + 1] == c ||
				board[curr.y][curr.x + 1] == c2)
				+ (board[curr.y][curr.x - 1] == c ||
						board[curr.y][curr.x - 1] == c2)
				+ (board[curr.y + 1][curr.x] == c ||
						board[curr.y + 1][curr.x] == c2)
				+ (board[curr.y - 1][curr.x] == c ||
						board[curr.y - 1][curr.x] == c2);
	}
	return (count);
}

static void		update_result(t_piece piece, t_vector curr, char opponent)
{
	t_result	*res;
	t_byte		block;
	t_byte		dis;

	res = get_result();
	if (valid_pos(piece, curr))
	{
		block = count_block(piece, curr, opponent, ft_tolower(opponent));
		dis = ft_absolute_distance(curr, nearest_opponent(opponent));
		if (block > res->block)
		{
			res->block = block;
			res->position = curr;
		}
		else if (block == res->block && dis < res->distance)
		{
			res->distance = dis;
			res->position = curr;
		}
	}
}

static void		get_pos(t_piece piece, char opponent)
{
	t_vector	pos;
	char		**board;
	t_byte		index;
	t_vector	curr;

	board = *get_board();
	pos.y = (opponent == 'X') ? -1 : get_dim()->y;
	while ((opponent == 'X') ? ++pos.y < get_dim()->y : --pos.y)
	{
		pos.x = (opponent == 'X') ? -1 : get_dim()->x;
		while ((opponent == 'X') ? ++pos.x < get_dim()->x : --pos.x)
			if ((opponent == 'X') ?
				board[pos.y][pos.x] == 'O' || board[pos.y][pos.x] == 'o' :
				board[pos.y][pos.x] == 'X' || board[pos.y][pos.x] == 'x')
			{
				index = -1;
				while (++index < piece.count)
				{
					curr.x = pos.x - piece.snippet[index].x;
					curr.y = pos.y - piece.snippet[index].y;
					update_result(piece, curr, opponent);
				}
			}
	}
}

int				main(void)
{
	t_piece		piece;
	int			opponent;
	t_result	*res;

	opponent = initialise_all();
	if (opponent != 'O' && opponent != 'X')
		return (1);
	while (1)
	{
		if (update_board(get_dim()->x, get_dim()->y))
			return (2);
		if (update_piece(&piece))
			return (3);
		res = get_result();
		res->position.x = 0;
		res->position.y = 0;
		res->block = 0;
		res->distance = 255;
		get_pos(piece, opponent);
		ft_printf("%d %d\n", res->position.y, res->position.x);
	}
	return (0);
}
