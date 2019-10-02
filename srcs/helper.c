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

void	init_step(t_wolf *wolf, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->s_dist.x = (wolf->cam.pos.x - ray->grid.x) * ray->d_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->s_dist.x = (ray->grid.x + 1.0 - wolf->cam.pos.x) * ray->d_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->s_dist.y = (wolf->cam.pos.y - ray->grid.y) * ray->d_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->s_dist.y = (ray->grid.y + 1.0 - wolf->cam.pos.y) * ray->d_dist.y;
	}
}
