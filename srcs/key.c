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

void	move(t_wolf *wolf, int sign)
{
	if (wolf->map.m[(int)wolf->cam.pos.y]
		[(int)(wolf->cam.pos.x + wolf->cam.dir.x * MOVE_SPEED * sign)] == 0)
		wolf->cam.pos.x += wolf->cam.dir.x * MOVE_SPEED * sign;
	if (wolf->map.m[(int)(wolf->cam.pos.y +
		wolf->cam.dir.y * MOVE_SPEED * sign)][(int)wolf->cam.pos.x] == 0)
		wolf->cam.pos.y += wolf->cam.dir.y * MOVE_SPEED * sign;
	draw_frame(wolf);
}

void	rotate(t_wolf *wolf, int sign)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = wolf->cam.dir.x;
	wolf->cam.dir.x = wolf->cam.dir.x * cos(sign * ROT_SPEED) -
		wolf->cam.dir.y * sin(sign * ROT_SPEED);
	wolf->cam.dir.y = old_dirx * sin(sign * ROT_SPEED) +
		wolf->cam.dir.y * cos(sign * ROT_SPEED);
	old_planex = wolf->cam.plane.x;
	wolf->cam.plane.x = wolf->cam.plane.x * cos(sign * ROT_SPEED) -
		wolf->cam.plane.y * sin(sign * ROT_SPEED);
	wolf->cam.plane.y = old_planex * sin(sign * ROT_SPEED) +
		wolf->cam.plane.y * cos(sign * ROT_SPEED);
	draw_frame(wolf);
}

int		key_press(int keycode, t_wolf *wolf)
{
	if (keycode == 13)
		move(wolf, 1);
	if (keycode == 1)
		move(wolf, -1);
	if (keycode == 2)
		rotate(wolf, -1);
	if (keycode == 0)
		rotate(wolf, 1);
	return (1);
}

int		key_event(int keycode, t_wolf *wolf)
{
	ft_printf("Key code: %d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_image(wolf->mlx, wolf->img.ptr);
		mlx_destroy_window(wolf->mlx, wolf->win);
		exit(0);
	}
	return (1);
}

int		mouse_press(t_wolf *wolf)
{
	(void)wolf;
	exit(EXIT_SUCCESS);
	return (0);
}
