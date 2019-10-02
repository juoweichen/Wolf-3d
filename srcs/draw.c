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

int		clear_img(t_wolf *wolf)
{
	unsigned x;
	unsigned y;

	y = -1;
	while (++y < WD_H)
	{
		x = -1;
		while (++x < WD_W)
			put_pixel(wolf, x, y, 0x808080);
	}
	return (0);
}

void	put_pixel(t_wolf *wolf, unsigned x, unsigned y, unsigned int color)
{
	unsigned int	cv;

	cv = mlx_get_color_value(wolf->mlx, color);
	*(int *)(wolf->img.addr + (y * WD_W + x) * BYTE) = cv;
}

void	draw_wall(t_wolf *wolf, int x, t_draw *draw)
{
	int y;
	int d;
	int color;

	y = draw->start;
	while (y <= draw->end)
	{
		d = y * 256 - WD_H * 128 + draw->line_h * 128;
		wolf->tex.y = ((d * TEX_H) / (draw->line_h * 256));
		color = wolf->tex.t[wolf->tex.num][TEX_W * wolf->tex.y + wolf->tex.x];
		put_pixel(wolf, x, y, color);
		y++;
	}
}

void	draw_floor(t_wolf *wolf, int x, t_draw *draw)
{
	t_floor	flr;
	int		y;
	int		color;

	flr.wall_dist = draw->wall_dist;
	flr.cam_dist = 0.0;
	if (draw->end < 0)
		draw->end = WD_H;
	y = draw->end + 1;
	while (y < WD_H)
	{
		flr.cur_dist = WD_H / (2.0 * y - WD_H);
		flr.w = (flr.cur_dist - flr.cam_dist) / (flr.wall_dist - flr.cam_dist);
		flr.cur.x = flr.w * draw->flrwall.x + (1.0 - flr.w) * wolf->cam.pos.x;
		flr.cur.y = flr.w * draw->flrwall.y + (1.0 - flr.w) * wolf->cam.pos.y;
		flr.tex.x = (int)(flr.cur.x * TEX_W) % TEX_W;
		flr.tex.y = (int)(flr.cur.y * TEX_H) % TEX_H;
		color = wolf->tex.t[1][TEX_W * flr.tex.y + flr.tex.x];
		put_pixel(wolf, x, y, color);
		color = wolf->tex.t[2][TEX_W * flr.tex.y + flr.tex.x];
		put_pixel(wolf, x, WD_H - y, color);
		y++;
	}
}
