/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahim <brahim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 09:20:55 by brahim            #+#    #+#             */
/*   Updated: 2023/11/01 19:20:56 by brahim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_exit(t_data *data)
{
	free(data->player);
	free(data);
	exit (EXIT_SUCCESS);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_2d(t_data *data)
{
	int x;
	int y;
	int i = -1;
	int j;

	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (data->map[i][j] == '1')
			{
				y = -1;
				while (++y < TILE_SIZE)
				{
					x = -1;
					while(++x < TILE_SIZE)
						my_mlx_pixel_put(data, j * TILE_SIZE + x, i * TILE_SIZE + y, 0x00FF0000);
				}
			}
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	y = TILE_SIZE;
	while (y < 768)
	{
		x = -1;
		while (++x < 1536)
			my_mlx_pixel_put(data, x, y, 0x99999999);
		y += TILE_SIZE;
	}
	x = TILE_SIZE;
	while (x < 1536)
	{
		y = -1;
		while (++y < 768)
			my_mlx_pixel_put(data, x, y, 0xBBBBBBBB);
		x += TILE_SIZE;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void	draw_player(t_data *data)
{
	int x;
	int y;

	y = data->player->y - 5;
	while(++y < data->player->y + 4)
	{
		x = data->player->x - 5;
		while (++x < data->player->x + 4)
			my_mlx_pixel_put(data, x, y, 0x00FFFFFF);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int	key_handle(int key, t_data *data)
{
	int		i;
	int		j;
	double	radian;

	radian = data->player->rot * M_PI / 180;
	if (key == ESC)
		ft_exit(data);
	if (key == LEFT)
	{
		if (data->player->rot <= 0)
			data->player->rot = 360;
		data->player->rot -= ROT_ANGLE;
		radian = data->player->rot * M_PI / 180;
	}
	if (key == RIGHT)
	{
		if (data->player->rot >= 360)
			data->player->rot = 0;
		data->player->rot += ROT_ANGLE;
		radian = data->player->rot * M_PI / 180;
	}
	if (key == W)
	{
		j = (data->player->x + (SPEED * cos(radian))) / TILE_SIZE;
		i = (data->player->y + (SPEED * sin(radian))) / TILE_SIZE;
		if (data->map[i][j] == '0')
		{	
			data->player->x += SPEED * cos(radian);
			data->player->y += SPEED * sin(radian);
		}
	}
	if (key == D)
	{
		j = (data->player->x + (SPEED * cos(radian + M_PI_2))) / TILE_SIZE;
		i = (data->player->y + (SPEED * sin(radian + M_PI_2))) / TILE_SIZE;
		if (data->map[i ][j] == '0')
		{	
			data->player->x += SPEED * cos(radian + M_PI_2);
			data->player->y += SPEED * sin(radian + M_PI_2);
		}
	}
	if (key == S)
	{
		j = (data->player->x + (-SPEED * cos(radian))) / TILE_SIZE;
		i = (data->player->y + (-SPEED * sin(radian))) / TILE_SIZE;
		if (data->map[i][j] == '0')
		{	
			data->player->x += -SPEED * cos(radian);
			data->player->y += -SPEED * sin(radian);
		}
	}
	if (key == A)
	{
		j = (data->player->x + (-SPEED * cos(radian + M_PI_2))) / TILE_SIZE;
		i = (data->player->y + (-SPEED * sin(radian + M_PI_2))) / TILE_SIZE;
		if (data->map[i][j] == '0')
		{	
			data->player->x += -SPEED * cos(radian + M_PI_2);
			data->player->y += -SPEED * sin(radian + M_PI_2);
		}
	}
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, 1536, 768);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length,
								&data->endian);
	draw_2d(data);
	draw_player(data);
	return (0);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (write(2, "Invalid number of arguments !\n", 30), 1);
	t_data *data;

	data = malloc(sizeof(t_data));
	data->player = malloc(sizeof(t_player));
	char	**m = malloc(sizeof(char *) * 13);
	if (!m)
		return (0);
	m[0] = "111111111111111111111111";
	m[1] = "100000000000000000000101";
	m[2] = "100000000000000011111001";
	m[3] = "100111111000000000000001";
	m[4] = "100000000000000000000001";
	m[5] = "100000000000110000000001";
	m[6] = "100000000000000000000001";
	m[7] = "100000000000010000000001";
	m[8] = "100000000000000000000001";
	m[9] = "100000111000001111111001";
	m[10] = "100000000000000000000001";
	m[11] = "111111111111111111111111";
	m[12] = NULL;
	
	data->mlx = mlx_init();
	data->map = m;
	data->win = mlx_new_window(data->mlx, 1536, 768, "salondryas");
	data->img = mlx_new_image(data->mlx, 1536, 768);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length,
								&data->endian);
	data->player->x = 80;
	data->player->y = 80;
	data->player->rot = 270;
	draw_2d(data);
	draw_player(data);
	mlx_hook(data->win, 17, 0, ft_exit, data);
	mlx_hook(data->win, 2, 1L<<0, key_handle, data);
	mlx_loop(data->mlx);
	return (0);
}