/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juochen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 14:30:46 by juochen           #+#    #+#             */
/*   Updated: 2018/04/23 23:20:18 by juochen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx/mlx.h"
#include <unistd.h>

void ft_putchar(char c)
{
	write(1, &c, 1);
}

int deal_key(int key, void *param)
{
	ft_putchar('X');
	return (0);
}

int main()
{
	void *mlx_ptr;
	void *win_ptr;
	int x;
	int y;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "mlx 42");
	mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xFFFFFF);
	x = 250;
	y = 250;
	while (1)
	{
		/*
		while (x < 500)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, x, 300, 0xFFFF00);
			x++;
		}
		x = 0;
		while (y < 500)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, 300, y, 0xFF0000);
			y++;
		}
		y = 0;
		*/
		x = 1;
		y = 300;
		while (y < 500 && x < 500)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xFF0000);
			x++;
			y = 300 -  ((x * x) / 1000);

		}
		x = 1;
		y = 300;
		while (y < 500 && x < 500)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xFFFF00);
			x++;
			y = 300 -  ((x * x) / 500);

		}
		y = 300;
		x = 1;

	}	
	mlx_key_hook(win_ptr, deal_key, (void *)0);
	mlx_loop(mlx_ptr);
}
