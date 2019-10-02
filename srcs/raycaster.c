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

void	init_raycaster(t_wolf *wolf, t_ray *ray, int x)
{
	wolf->cam.cam_x = 2 * x / (double)WD_W - 1;
	ray->dir.x = wolf->cam.dir.x + wolf->cam.plane.x * wolf->cam.cam_x;
	ray->dir.y = wolf->cam.dir.y + wolf->cam.plane.y * wolf->cam.cam_x;
	ray->grid.x = (int)wolf->cam.pos.x;
	ray->grid.y = (int)wolf->cam.pos.y;
	ray->d_dist.x = fabs(1 / ray->dir.x);
	ray->d_dist.y = fabs(1 / ray->dir.y);
	init_step(wolf, ray);
}

void	wall_detect(t_wolf *wolf, t_ray *ray)
{
	int	is_hit;

	is_hit = 0;
	while (is_hit == 0)
	{
		if (ray->s_dist.x < ray->s_dist.y)
		{
			ray->s_dist.x += ray->d_dist.x;
			ray->grid.x += ray->step.x;
			ray->is_side = 0;
		}
		else
		{
			ray->s_dist.y += ray->d_dist.y;
			ray->grid.y += ray->step.y;
			ray->is_side = 1;
		}
		if (wolf->map.m[ray->grid.y][ray->grid.x] > 0)
			is_hit = 1;
	}
}

void	calc_strip(t_wolf *wolf, t_ray *ray, t_draw *draw)
{
	if (ray->is_side == 0)
		draw->wall_dist = (ray->grid.x - wolf->cam.pos.x +
		(1 - ray->step.x) / 2) / ray->dir.x;
	else
		draw->wall_dist = (ray->grid.y - wolf->cam.pos.y +
		(1 - ray->step.y) / 2) / ray->dir.y;
	draw->line_h = (int)(WD_H / draw->wall_dist);
	draw->start = -draw->line_h / 2 + WD_H / 2;
	if (draw->start < 0)
		draw->start = 0;
	draw->end = draw->line_h / 2 + WD_H / 2;
	if (draw->end >= WD_H)
		draw->end = WD_H - 1;
}

void	calc_texture(t_wolf *wolf, t_ray *ray, t_draw *draw)
{
	wolf->tex.num = wolf->map.m[ray->grid.y][ray->grid.x] - 1;
	if (ray->is_side == 0)
		draw->wall_x = wolf->cam.pos.y + draw->wall_dist * ray->dir.y;
	else
		draw->wall_x = wolf->cam.pos.x + draw->wall_dist * ray->dir.x;
	draw->wall_x -= floor(draw->wall_x);
	wolf->tex.x = (int)(draw->wall_x * (double)TEX_W);
	if (ray->is_side == 0 && ray->dir.x > 0)
		wolf->tex.x = TEX_W - wolf->tex.x - 1;
	if (ray->is_side == 1 && ray->dir.y < 0)
		wolf->tex.x = TEX_W - wolf->tex.x - 1;
}

void	calc_floor(t_ray *ray, t_draw *draw)
{
	if (ray->is_side == 0 && ray->dir.x > 0)
	{
		draw->flrwall.x = ray->grid.x;
		draw->flrwall.y = ray->grid.y + draw->wall_x;
	}
	else if (ray->is_side == 0 && ray->dir.x < 0)
	{
		draw->flrwall.x = ray->grid.x + 1.0;
		draw->flrwall.y = ray->grid.y + draw->wall_x;
	}
	else if (ray->is_side == 1 && ray->dir.y > 0)
	{
		draw->flrwall.x = ray->grid.x + draw->wall_x;
		draw->flrwall.y = ray->grid.y;
	}
	else
	{
		draw->flrwall.x = ray->grid.x + draw->wall_x;
		draw->flrwall.y = ray->grid.y + 1.0;
	}
}
