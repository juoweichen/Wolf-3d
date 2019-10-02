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

void	set_texture(t_wolf *wolf)
{
	int	x;
	int	y;
	int	i;

	y = -1;
	while (++y < TEX_H)
	{
		x = -1;
		while (++x < TEX_W)
		{
			i = -1;
			while (++i < TEX_NUM)
				wolf->tex.t[i][TEX_W * y + x] =
					*(int *)(wolf->tex.p[i].addr + (TEX_W * y + x) * BYTE);
		}
	}
}

void	load_texture(t_wolf *wolf)
{
	int i;
	int tex_w;
	int tex_h;

	tex_w = TEX_W;
	tex_h = TEX_H;
	i = 0;
	while (i < TEX_NUM)
	{
		if (!(wolf->tex.p[i].ptr = mlx_xpm_file_to_image(wolf->mlx,
			wolf->tex.name[i], &tex_w, &tex_h)))
		{
			printf("name = %s\n", wolf->tex.name[i]);
			perror("xpm error");
			exit(1);
		}
		wolf->tex.p[i].addr = mlx_get_data_addr(wolf->tex.p[i].ptr,
			&wolf->tex.p[i].bpp, &wolf->tex.p[i].sl, &wolf->tex.p[i].ed);
		i++;
	}
}

/*
**	wolf->tex.name[0]: defualt wall
**	wolf->tex.name[1]: floor
**	wolf->tex.name[2]: ceiling
**
**	wolf->tex.name[3~4]: other wall texture
**	wolf->tex.name[5~8]: Hitler wall texture
**	wolf->tex.name[9~12]: Nazi wall texture
**	wolf->tex.name[13~16]: another wall texture
**	wolf->tex.name[17~18]: sky-like wall texture
*/

void	name_texture_wall(t_wolf *wolf)
{
	ft_strcpy(wolf->tex.name[0], "resources/xpm/wall/redbrick.XPM");
	ft_strcpy(wolf->tex.name[1], "resources/xpm/wall/mossy.XPM");
	ft_strcpy(wolf->tex.name[2], "resources/xpm/wall/wood.XPM");
	ft_strcpy(wolf->tex.name[3], "resources/xpm/wall/greystone.XPM");
	ft_strcpy(wolf->tex.name[4], "resources/xpm/wall/eagle.XPM");
	ft_strcpy(wolf->tex.name[5], "resources/xpm/wall/Hitler1.xpm");
	ft_strcpy(wolf->tex.name[6], "resources/xpm/wall/Hitler2.xpm");
	ft_strcpy(wolf->tex.name[7], "resources/xpm/wall/Hitler3.xpm");
	ft_strcpy(wolf->tex.name[8], "resources/xpm/wall/Hitler4.xpm");
	ft_strcpy(wolf->tex.name[9], "resources/xpm/wall/Nazi1.xpm");
	ft_strcpy(wolf->tex.name[10], "resources/xpm/wall/Nazi2.xpm");
	ft_strcpy(wolf->tex.name[11], "resources/xpm/wall/Nazi3.xpm");
	ft_strcpy(wolf->tex.name[12], "resources/xpm/wall/Nazi4.xpm");
	ft_strcpy(wolf->tex.name[13], "resources/xpm/wall/sign.xpm");
	ft_strcpy(wolf->tex.name[14], "resources/xpm/wall/switch.xpm");
	ft_strcpy(wolf->tex.name[15], "resources/xpm/wall/door.xpm");
	ft_strcpy(wolf->tex.name[16], "resources/xpm/wall/cage.xpm");
	ft_strcpy(wolf->tex.name[17], "resources/xpm/wall/daysky.xpm");
	ft_strcpy(wolf->tex.name[18], "resources/xpm/wall/nightsky.xpm");
}

/*
**	wolf->tex.name[19~29]: object texture
**	wolf->tex.name[30~33]: teature object texture
**	wolf->tex.name[34~36]: boss texture
*/

void	name_texture_object(t_wolf *wolf)
{
	ft_strcpy(wolf->tex.name[19], "resources/xpm/object/armuor.xpm");
	ft_strcpy(wolf->tex.name[20], "resources/xpm/object/barral.xpm");
	ft_strcpy(wolf->tex.name[21], "resources/xpm/object/gun.xpm");
	ft_strcpy(wolf->tex.name[22], "resources/xpm/object/tnc.xpm");
	ft_strcpy(wolf->tex.name[23], "resources/xpm/object/tree.xpm");
	ft_strcpy(wolf->tex.name[24], "resources/xpm/object/biggun.xpm");
	ft_strcpy(wolf->tex.name[25], "resources/xpm/object/blood.xpm");
	ft_strcpy(wolf->tex.name[26], "resources/xpm/object/extralife!.xpm");
	ft_strcpy(wolf->tex.name[27], "resources/xpm/object/light.xpm");
	ft_strcpy(wolf->tex.name[28], "resources/xpm/object/meal.xpm");
	ft_strcpy(wolf->tex.name[29], "resources/xpm/object/spear.xpm");
	ft_strcpy(wolf->tex.name[30], "resources/xpm/object/teature1.xpm");
	ft_strcpy(wolf->tex.name[31], "resources/xpm/object/teature2.xpm");
	ft_strcpy(wolf->tex.name[32], "resources/xpm/object/teature3.xpm");
	ft_strcpy(wolf->tex.name[33], "resources/xpm/object/teature4.xpm");
	ft_strcpy(wolf->tex.name[34], "resources/xpm/object/boss1.xpm");
	ft_strcpy(wolf->tex.name[35], "resources/xpm/object/boss2.xpm");
	ft_strcpy(wolf->tex.name[36], "resources/xpm/object/boss3.xpm");
	ft_strcpy(wolf->tex.name[37], "resources/xpm/wall/colorbrick.xpm");
	ft_strcpy(wolf->tex.name[38], "resources/xpm/wall/mudbrick.xpm");
}
