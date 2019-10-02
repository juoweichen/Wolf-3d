/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juochen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 13:34:19 by juochen           #+#    #+#             */
/*   Updated: 2018/05/04 12:49:55 by juochen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int		set_sprite(int fd, t_wolf *wolf)
{
	char	*line;
	char	**spline;
	int		x;
	int		y;

	y = -1;
	while (++y < wolf->sprt.num && get_next_line(fd, &line))
	{
		spline = ft_strsplit(line, ' ');
		x = -1;
		while (++x < 3)
		{
			wolf->sprt.elems[y].x = ft_atoi(spline[0]);
			wolf->sprt.elems[y].y = ft_atoi(spline[1]);
			wolf->sprt.elems[y].tex = ft_atoi(spline[2]) - 1;
		}
		ft_mstrdel_rows(&spline, 3);
		ft_strdel(&line);
	}
	return (1);
}

int		check_sprite_content(char **spline, int y)
{
	int	x;

	x = 0;
	while (spline[x])
	{
		if (!ft_isdigit_str(spline[x]) ||
			(x == 2 && ft_atoi(spline[x]) > TEX_NUM) ||
			(x == 2 && ft_atoi(spline[x]) > TEX_NUM))
		{
			ft_printf("illegal sprite content in row:%d col:%d\n", y, x);
			ft_printf("must be integer and range from 0 to %d\n", TEX_NUM + 1);
			return (-1);
		}
		if (ft_atoi(spline[x]) < 0)
			return (-1);
		x++;
	}
	if (x != 3)
	{
		ft_printf("wrong sprite format in row:%d col:%d\n", y, x);
		return (-1);
	}
	return (1);
}

int		check_sprite(int fd, t_wolf *wolf)
{
	char	*line;
	char	**spline;
	int		y;

	y = 0;
	while (get_next_line(fd, &line))
	{
		spline = ft_strsplit(line, ' ');
		if (check_sprite_content(spline, y) == -1)
			return (-1);
		ft_mstrdel_rows(&spline, 3);
		ft_strdel(&line);
		y++;
	}
	if (y != wolf->sprt.num)
	{
		ft_printf("wrong sprite size\n");
		return (-1);
	}
	return (1);
}

int		get_sprite_num(int fd, t_wolf *wolf)
{
	char	*line;

	if (get_next_line(fd, &line))
	{
		if (line && ft_isdigit_str(line))
		{
			wolf->sprt.num = ft_atoi(line);
			ft_strdel(&line);
			return (1);
		}
		ft_strdel(&line);
	}
	else
	{
		ft_printf("sprite number missing\n");
		return (-1);
	}
	return (1);
}
