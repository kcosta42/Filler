/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 16:26:11 by kcosta            #+#    #+#             */
/*   Updated: 2017/01/02 13:20:40 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	set_piece_origin(t_piece *piece)
{
	t_vector	pos;
	t_vector	bound;
	t_byte		index;

	bound.x = -1;
	bound.y = -1;
	pos.y = -1;
	index = 0;
	if (!(piece->snippet = (t_vector*)ft_memalloc(sizeof(t_vector) * piece->count)))
		return (ft_error("Error: Failed to allocate memory\n", 3));
	while (++pos.y < piece->len.y)
	{
		pos.x = -1;
		while (++pos.x < piece->len.x)
			if (piece->shape[pos.y][pos.x] == '*')
			{
				piece->snippet[index] = pos;
				if (pos.y < bound.y || bound.y == -1)
					bound.y = pos.y;
				if (pos.x < bound.x || bound.x == -1)
					bound.x = pos.x;
				index++;
			}
	}
	piece->origin = bound;
	return (0);
}

static int	set_piece_shape(t_piece *piece)
{
	char	*line;
	int		index;
	t_vector	pos;

	pos.y = -1;
	if (!(piece->shape = (char**)ft_memalloc(sizeof(char*) * (piece->len.y + 1))))
		return (ft_error("Error: Failed to allocate memory\n", 3));
	index = 0;
	piece->count = 0;
	while (index < piece->len.y)
	{
		if (ft_getline(0, &line) <= 0)
			return (ft_error("Error: Failed to read the file\n", 1));
		piece->shape[index++] = ft_strdup(line);
		ft_strdel(&line);
	}
	while (++pos.y < piece->len.y)
	{
		pos.x = -1;
		while (++pos.x < piece->len.x)
			if (piece->shape[pos.y][pos.x] == '*')
				piece->count++;
	}
	return (0);
}

static int	set_piece_len(t_piece *piece)
{
	char		*line;
	char		*tmp;

	if (ft_getline(0, &line) <= 0)
		return (ft_error("Error: Failed to read the file\n", 1));
	if (!line)
		return (ft_error("Error: Failed to read the file\n", 1));
	tmp = line;
	while (*line && !ft_isdigit(*line))
		line++;
	piece->len.y = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	piece->len.x = ft_atoi((*line) ? ++line : "0");
	if (!piece->len.x || !piece->len.y)
		return (ft_error("Error: Invalid length\n", 2));
	ft_strdel(&tmp);
	return (0);
}

int			update_piece(t_piece *piece)
{
	if (set_piece_len(piece))
		return (1);
	if (piece->shape)
		ft_tabdel(&(piece->shape));
	if (piece->snippet)
		ft_memdel((void**)&(piece->snippet));
	if (set_piece_shape(piece))
		return (2);
	if (set_piece_origin(piece))
		return (3);
	return (0);
}

int			update_board(int width, int height)
{
	t_vector		index;
	char			***board;
	char			*line;
	static t_byte	first = 1;

	index.y = -1;
	board = get_board();
	if (ft_getline(0, &line) <= 0)
		return (1);
	ft_strdel(&line);
	if (!first)
		if (ft_getline(0, &line) <= 0)
			return (1);
	first ? 0 : ft_strdel(&line);
	while (++index.y < height)
	{
		index.x = -1;
		if (ft_getline(0, &line) <= 0)
			return (1);
		while (++index.x < width)
			(*board)[index.y][index.x] = line[4 + index.x];
		ft_strdel(&line);
	}
	first = 0;
	return (0);
}
