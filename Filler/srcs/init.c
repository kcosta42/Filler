/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 01:49:45 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/31 02:14:33 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	initialise_board(int width, int height)
{
	int			index;
	char		***board;

	board = get_board();
	if (!(*board = (char**)ft_memalloc(sizeof(char*) * (height + 1))))
		return (ft_error("Error: Failed to allocate memory\n", 3));
	index = 0;
	while (index <= height)
		if (!((*board)[index++] = ft_strnew(width)))
			return (ft_error("Error: Failed to allocate memory\n", 3));
	return (0);
}

static int	initialise_dim(void)
{
	char		*line;
	char		*tmp;
	t_vector	*dim;

	dim = get_dim();
	if (ft_getline(0, &line) <= 0)
		return (ft_error("Error: Failed to read the file\n", 1));
	if (!line)
		return (ft_error("Error: Failed to read the file\n", 1));
	tmp = line;
	while (*line && !ft_isdigit(*line))
		line++;
	dim->y = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	dim->x = ft_atoi((*line) ? ++line : "0");
	if (!dim->x || !dim->y)
		return (ft_error("Error: Invalid length\n", 2));
	ft_strdel(&tmp);
	return (0);
}

static int	initialise_player(int *player)
{
	char		*line;

	if (ft_getline(0, &line) <= 0)
		return (ft_error("Error: Failed to read the file\n", 1));
	if (!line)
		return (ft_error("Error: Failed to read the file\n", 1));
	if (ft_strncmp(line, "$$$ exec p", 10))
		return (ft_error("Error: Failed to read the file\n", 1));
	*player = (ft_strncmp(ft_strchr(line, 'p'), "p1", 2)) ? 'O' : 'X';
	ft_strdel(&line);
	return (0);
}

int			initialise_all(void)
{
	int		player;

	if (initialise_player(&player))
		return (1);
	if (initialise_dim())
		return (2);
	if (initialise_board(get_dim()->x, get_dim()->y))
		return (3);
	return (player);
}
