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

int		set_map(int fd, t_wolf *wolf)
{
	char	*line;
	char	**spline;
	int		x;
	int		y;
	int		num;

	y = -1;
	while (++y < wolf->map.h && get_next_line(fd, &line))
	{
		spline = ft_strsplit(line, ' ');
		wolf->map.m[y] = (int *)ft_memalloc(sizeof(int) * wolf->map.w);
		x = -1;
		while (++x < wolf->map.w)
		{
			if ((num = ft_atoi(spline[x])) < 0)
			{
				wolf->cam.pos.x = x;
				wolf->cam.pos.y = y;
			}
			wolf->map.m[y][x] = (num < 0 ? 0 : num);
		}
		ft_mstrdel_rows(&spline, wolf->map.w);
		ft_strdel(&line);
	}
	return (1);
}

int		check_map_content(t_wolf *wolf, char **spline, int y)
{
	int x;

	x = 0;
	while (spline[x])
	{
		if (!ft_isdigit_str(spline[x]) || ft_atoi(spline[x]) > TEX_NUM)
		{
			ft_printf("illegal map content in row:%d col:%d\n", y, x);
			ft_printf("must be integer and range from 0 to %d\n", TEX_NUM + 1);
			return (-1);
		}
		if (x == 0 || x == wolf->map.w - 1 || y == 0 || y == wolf->map.h - 1)
			if (ft_atoi(spline[x]) < 1)
			{
				ft_printf("hole in row:%d col:%d\n", y, x);
				return (-1);
			}
		x++;
	}
	if (x != wolf->map.w)
	{
		ft_printf("wrong colmun in row:%d col:%d\n", y, x);
		return (-1);
	}
	return (1);
}

int		check_map(int fd, t_wolf *wolf)
{
	char	*line;
	char	**spline;
	int		y;

	y = 0;
	while (get_next_line(fd, &line))
	{
		spline = ft_strsplit(line, ' ');
		if (check_map_content(wolf, spline, y) == -1)
			return (-1);
		ft_mstrdel_rows(&spline, wolf->map.w);
		ft_strdel(&line);
		if (++y == wolf->map.h)
			break ;
	}
	return (1);
}

int		get_mapsize(int fd, t_wolf *wolf)
{
	char	*line;
	char	**spline;

	if (get_next_line(fd, &line))
	{
		spline = ft_strsplit(line, ' ');
		if (spline && spline[0] && spline[1] && spline[2] == NULL &&
			ft_isdigit_str(spline[0]) && ft_isdigit_str(spline[1]))
		{
			wolf->map.w = ft_atoi(spline[0]);
			wolf->map.h = ft_atoi(spline[1]);
			ft_mstrdel_rows(&spline, 2);
			ft_strdel(&line);
			return ((wolf->map.w > 0 && wolf->map.h > 0) ? 1 : -1);
		}
		ft_mstrdel_norows(&spline);
		ft_strdel(&line);
	}
	else
	{
		ft_printf("map size missing\n");
		return (-1);
	}
	return (1);
}
