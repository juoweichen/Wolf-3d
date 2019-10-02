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

void	bubble_sort_sprite(int *order, double *dist, int amount)
{
	int	j;
	int	is_sorted;

	while (1)
	{
		is_sorted = 1;
		j = 0;
		while (j < amount - 1)
		{
			if (dist[j] < dist[j + 1])
			{
				ft_swap_double(&dist[j], &dist[j + 1]);
				ft_swap_int(&order[j], &order[j + 1]);
				is_sorted = 0;
			}
			j++;
		}
		if (is_sorted)
			return ;
	}
}

void	init_sprite(t_wolf *wolf)
{
	int	i;

	i = 0;
	while (i < wolf->sprt.num)
	{
		wolf->sprt.order[i] = i;
		wolf->sprt.dist[i] = pow(wolf->cam.pos.x - wolf->sprt.elems[i].x, 2) +
			pow(wolf->cam.pos.y - wolf->sprt.elems[i].y, 2);
		i++;
	}
	bubble_sort_sprite(wolf->sprt.order, wolf->sprt.dist, wolf->sprt.num);
}

void	transform_sprite(t_wolf *wolf, int i)
{
	t_dcorr	sprite;
	double	inv;

	sprite.x = wolf->sprt.elems[wolf->sprt.order[i]].x - wolf->cam.pos.x;
	sprite.y = wolf->sprt.elems[wolf->sprt.order[i]].y - wolf->cam.pos.y;
	inv = 1.0 / (wolf->cam.plane.x * wolf->cam.dir.y - wolf->cam.dir.x *
		wolf->cam.plane.y);
	wolf->sprt.transform.x = inv * (wolf->cam.dir.y * sprite.x -
		wolf->cam.dir.x * sprite.y);
	wolf->sprt.transform.y = inv * (-wolf->cam.plane.y * sprite.x +
		wolf->cam.plane.x * sprite.y);
	wolf->sprt.screen_x = (int)((WD_W / 2) * (1 + wolf->sprt.transform.x /
		wolf->sprt.transform.y));
}

void	calc_sprite(t_wolf *wolf)
{
	wolf->sprt.h = abs((int)(WD_H / wolf->sprt.transform.y));
	wolf->sprt.start.y = -wolf->sprt.h / 2 + WD_H / 2;
	if (wolf->sprt.start.y < 0)
		wolf->sprt.start.y = 0;
	wolf->sprt.end.y = wolf->sprt.h / 2 + WD_H / 2;
	if (wolf->sprt.end.y >= WD_H)
		wolf->sprt.end.y = WD_H - 1;
	wolf->sprt.w = abs((int)(WD_H / wolf->sprt.transform.y));
	wolf->sprt.start.x = -wolf->sprt.w / 2 + wolf->sprt.screen_x;
	if (wolf->sprt.start.x < 0)
		wolf->sprt.start.x = 0;
	wolf->sprt.end.x = wolf->sprt.w / 2 + wolf->sprt.screen_x;
	if (wolf->sprt.end.x >= WD_W)
		wolf->sprt.end.x = WD_W - 1;
}

void	draw_one_sprite(t_wolf *wolf, int i)
{
	t_icorr pxl;
	t_icorr tex;
	int		d;
	int		color;

	pxl.x = wolf->sprt.start.x - 1;
	while (++pxl.x < wolf->sprt.end.x)
	{
		tex.x = 256 * (pxl.x - (-wolf->sprt.w / 2 + wolf->sprt.screen_x)) *
			TEX_W / wolf->sprt.w / 256;
		if (wolf->sprt.transform.y > 0 && pxl.x > 0 && pxl.x < WD_W &&
			wolf->sprt.transform.y < wolf->sprt.z_buf[pxl.x])
		{
			pxl.y = wolf->sprt.start.y - 1;
			while (++pxl.y < wolf->sprt.end.y)
			{
				d = pxl.y * 256 - WD_H * 128 + wolf->sprt.h * 128;
				tex.y = ((d * TEX_H) / wolf->sprt.h) / 256;
				if ((color = wolf->tex.t[wolf->sprt.elems[wolf->sprt.order[i]
					].tex][TEX_W * tex.y + tex.x]) != 0x980088)
					put_pixel(wolf, pxl.x, pxl.y, color);
			}
		}
	}
}
