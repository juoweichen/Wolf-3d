/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juochen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 22:52:51 by juochen           #+#    #+#             */
/*   Updated: 2018/04/19 22:52:56 by juochen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "../libft/includes/ft_printf.h"
# include "../minilibx_macos/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <time.h>

# define WD_W 1000
# define WD_H 1000

# define FOV 0.66
# define MOVE_SPEED 0.3
# define ROT_SPEED 0.1
# define BYTE 4

# define TEX_NUM 39
# define TEX_W 64
# define TEX_H 64
# define TEX_NAME_MAX 100

typedef struct		s_dcorr
{
	double			x;
	double			y;
}					t_dcorr;

typedef struct		s_icorr
{
	int				x;
	int				y;
}					t_icorr;

typedef struct		s_cam
{
	t_dcorr			pos;
	t_dcorr			dir;
	t_dcorr			plane;
	double			cam_x;
}					t_cam;

typedef struct		s_floor
{
	double			wall_dist;
	double			cam_dist;
	double			cur_dist;
	double			w;
	t_dcorr			cur;
	t_icorr			tex;
}					t_floor;

typedef struct		s_draw
{
	double			wall_dist;
	double			wall_x;
	int				line_h;
	int				start;
	int				end;
	t_dcorr			flrwall;
}					t_draw;

typedef struct		s_ray
{
	t_dcorr			dir;
	t_icorr			grid;
	t_dcorr			s_dist;
	t_dcorr			d_dist;
	t_icorr			step;
	int				is_side;
}					t_ray;

typedef struct		s_image
{
	void			*ptr;
	void			*addr;
	int				bpp;
	int				sl;
	int				ed;
}					t_img;

typedef struct		s_map
{
	int				w;
	int				h;
	int				**m;
}					t_map;

typedef struct		s_texture
{
	char			name[TEX_NUM][TEX_NAME_MAX];
	t_img			p[TEX_NUM];
	int				t[TEX_NUM][TEX_H * TEX_W];
	int				num;
	int				x;
	int				y;
}					t_tex;

typedef struct		s_sprite_elem
{
	int				x;
	int				y;
	int				tex;
}					t_sprt_elem;

typedef struct		s_sprite
{
	int				num;
	t_sprt_elem		*elems;
	double			z_buf[WD_W];
	int				*order;
	double			*dist;
	t_dcorr			transform;
	int				screen_x;
	int				h;
	int				w;
	t_icorr			start;
	t_icorr			end;
}					t_sprt;

typedef struct		s_wolf
{
	void			*mlx;
	void			*win;
	t_map			map;
	t_cam			cam;
	t_img			img;
	t_tex			tex;
	t_sprt			sprt;
}					t_wolf;

/*
**	main.c
*/
int					draw_frame(t_wolf *wolf);
/*
**	read_map.c
*/
int					get_mapsize(int fd, t_wolf *wolf);
int					check_map(int fd, t_wolf *wolf);
int					set_map(int fd, t_wolf *wolf);
/*
**	draw.c
*/
int					clear_img(t_wolf *wolf);
void				put_pixel(t_wolf *wolf, unsigned x, unsigned y,
	unsigned int color);
void				draw_wall(t_wolf *wolf, int x, t_draw *draw);
void				draw_floor(t_wolf *wolf, int x, t_draw *draw);
/*
**	raycaster.c
*/
void				init_raycaster(t_wolf *wolf, t_ray *ray, int x);
void				wall_detect(t_wolf *wolf, t_ray *ray);
void				calc_strip(t_wolf *wolf, t_ray *ray, t_draw *draw);
void				calc_texture(t_wolf *wolf, t_ray *ray, t_draw *draw);
void				calc_floor(t_ray *ray, t_draw *draw);
/*
**	key.c
*/
int					key_press(int keycode, t_wolf *wolf);
int					key_event(int keycode, t_wolf *wolf);
int					mouse_press(t_wolf *wolf);
/*
**	load_texture.c
*/
void				set_texture(t_wolf *wolf);
void				load_texture(t_wolf *wolf);
void				name_texture_wall(t_wolf *wolf);
void				name_texture_object(t_wolf *wolf);
/*
**	read_sprite.c
*/
int					get_sprite_num(int fd, t_wolf *wolf);
int					check_sprite(int fd, t_wolf *wolf);
int					set_sprite(int fd, t_wolf *wolf);
/*
**	sprite.c
*/
void				init_sprite(t_wolf *wolf);
void				draw_one_sprite(t_wolf *wolf, int i);
void				calc_sprite(t_wolf *wolf);
void				transform_sprite(t_wolf *wolf, int i);
/*
**	helper.c
*/
void				init_step(t_wolf *wolf, t_ray *ray);

#endif
