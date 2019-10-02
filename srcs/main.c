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

void	draw_sprite(t_wolf *wolf)
{
	int	i;

	init_sprite(wolf);
	i = 0;
	while (i < wolf->sprt.num)
	{
		transform_sprite(wolf, i);
		calc_sprite(wolf);
		draw_one_sprite(wolf, i);
		i++;
	}
}

int		draw_frame(t_wolf *wolf)
{
	int		x;
	t_ray	ray;
	t_draw	draw;

	x = 0;
	while (x < WD_W)
	{
		init_raycaster(wolf, &ray, x);
		wall_detect(wolf, &ray);
		calc_strip(wolf, &ray, &draw);
		calc_texture(wolf, &ray, &draw);
		calc_floor(&ray, &draw);
		draw_wall(wolf, x, &draw);
		draw_floor(wolf, x, &draw);
		wolf->sprt.z_buf[x] = draw.wall_dist;
		x++;
	}
	draw_sprite(wolf);
	mlx_put_image_to_window(wolf->mlx, wolf->win, wolf->img.ptr, 0, 0);
	return (1);
}

void	init_env(t_wolf *wolf)
{
	wolf->img.ptr = mlx_new_image(wolf->mlx, WD_H, WD_W);
	wolf->img.addr = mlx_get_data_addr(wolf->img.ptr, &wolf->img.bpp,
		&wolf->img.sl, &wolf->img.ed);
	wolf->cam.dir.x = -1;
	wolf->cam.dir.y = 0;
	wolf->cam.plane.x = 0;
	wolf->cam.plane.y = FOV;
	name_texture_wall(wolf);
	name_texture_object(wolf);
	load_texture(wolf);
	set_texture(wolf);
	if (!(wolf->sprt.dist = (double *)ft_memalloc(sizeof(double) *
		wolf->sprt.num)) || !(wolf->sprt.order =
		(int *)ft_memalloc(sizeof(int) * wolf->sprt.num)))
	{
		perror("memalloc error\n");
		exit(1);
	}
}

int		readmap(char *map_name, t_wolf *wolf)
{
	int		fd;

	if ((fd = open(map_name, O_RDONLY)) < 0)
		return (-1);
	if (get_mapsize(fd, wolf) == -1 || check_map(fd, wolf) == -1)
		return (-1);
	if (!ft_skipline(fd))
		return (-1);
	if (get_sprite_num(fd, wolf) == -1 || check_sprite(fd, wolf) == -1)
		return (-1);
	close(fd);
	if ((fd = open(map_name, O_RDONLY)) < 0)
		return (-1);
	if (!ft_skipline(fd))
		return (-1);
	if ((wolf->map.m = (int **)ft_memalloc(sizeof(int *) *
		wolf->map.h)) == NULL || set_map(fd, wolf) == -1)
		return (-1);
	if (!ft_skipline(fd) || !ft_skipline(fd))
		return (-1);
	if ((wolf->sprt.elems = (t_sprt_elem *)ft_memalloc(sizeof(t_sprt_elem) *
	wolf->sprt.num)) == NULL || set_sprite(fd, wolf) == -1)
		return (-1);
	close(fd);
	return (1);
}

int		main(int argc, char **argv)
{
	t_wolf	wolf;

	if (argc == 2)
	{
		if ((readmap(argv[1], &wolf)) == -1 || wolf.cam.pos.x == 0 ||
			wolf.cam.pos.y == 0)
		{
			ft_printf("map error\n");
			exit(1);
		}
		wolf.mlx = mlx_init();
		wolf.win = mlx_new_window(wolf.mlx, WD_W, WD_H, "wolf3d");
		init_env(&wolf);
		draw_frame(&wolf);
		mlx_key_hook(wolf.win, key_event, &wolf);
		mlx_hook(wolf.win, 2, 2, key_press, &wolf);
		mlx_hook(wolf.win, 17, 0, mouse_press, &wolf);
		mlx_loop(wolf.mlx);
	}
	else
		ft_printf("usage: ./wolf3d maps/[map_file]\n");
	return (0);
}
