/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahim <brahim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 09:19:43 by brahim            #+#    #+#             */
/*   Updated: 2023/10/30 11:00:38 by brahim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <unistd.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>

# define TILE_SIZE 64
# define SPEED 10
# define ROT_ANGLE 5

# define ESC 53
# define RIGHT 124
# define LEFT 123
# define A 0
# define W 13
# define S 1
# define D 2

// a data struct must be created, it should have an mlx pointer, a win pointer, some info abt the map

typedef struct s_player
{
	/* if player is W then rot = 180
					S then rot = 90
					E then rot = 0
					N then rot = 270
		
		while right arrow is pressed : rot += 1
		      left arrow is pressed : rot -= 1
			  
		to move player :
			create a variable radian = rot * PI / 180;
			when W is pressed :
				x = speed * cos(radian)
				y = speed * sin(radian)
			when S is pressed :
				x = -speed * cos(radian)
				y = -speed * sin(radian)
			when A is pressed :
				x = -speed * cos(radian)
				y = -speed * sin(radian)
			when D is pressed :
				z = speed * cos(radian)
				y = speed * sin(radian)
			a function should fill the 
			*/

	double	rot; // W = 180, S = 90, E = 0, N = 270;
	double	x; // j in map * TILE_SIZE;
	double	y; // i in map * TILE_SIZE;
}	t_player;

typedef struct	s_data
{
	t_player	*player;
	void		*mlx;
	void		*win;
	char		**map;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;


#endif