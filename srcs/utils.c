/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 01:35:54 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/31 19:10:28 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

char		***get_board(void)
{
	static char	**board;

	return (&board);
}

t_vector	*get_dim(void)
{
	static t_vector	dim;

	return (&dim);
}

t_result	*get_result(void)
{
	static t_result	result;

	return (&result);
}

void		ft_tabdel(char ***tab)
{
	int		i;

	i = 0;
	while ((*tab)[i])
	{
		ft_strdel(&((*tab)[i]));
		i++;
	}
	ft_strdel((char**)tab);
}

int			ft_error(char *msg, int ft_errnum)
{
	ft_putstr_fd(msg, 2);
	return (ft_errnum);
}
