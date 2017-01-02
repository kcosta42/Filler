/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 14:17:29 by kcosta            #+#    #+#             */
/*   Updated: 2017/01/02 13:51:53 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>

# include "libft.h"

typedef struct	s_vector
{
	int			x;
	int			y;
}				t_vector;

typedef struct	s_piece
{
	char		**shape;
	t_byte		count;
	t_vector	*snippet;
	t_vector	origin;
	t_vector	len;
}				t_piece;

typedef struct	s_result
{
	t_vector	position;
	t_byte		block;
	t_byte		distance;
}				t_result;

char			***get_board(void);
t_vector		*get_dim(void);
t_result		*get_result(void);

int				initialise_all(void);
int				update_board(int width, int height);
int				update_piece(t_piece *piece);
t_vector		nearest_opponent(char opponent);

unsigned long	ft_absolute_distance(t_vector pos1, t_vector pos2);
int				ft_error(char *msg, int ft_errnum);
void			ft_tabdel(char ***tab);

#endif
