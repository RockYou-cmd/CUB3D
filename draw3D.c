/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 01:58:36 by ael-korc          #+#    #+#             */
/*   Updated: 2022/10/28 02:00:40 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	strip(float x1, float y1, float y2, int x_offset, int w)
{
	float	y;
	float	inc;
	int		pos;

	y = 0;
	inc = 0;
	while (y <= y2)
	{
		pos = data.img_addr[w][((int)inc * 32) + x_offset];
		my_main_mlx_pixel_put(x1, y1 + y, pos);
		inc += (data.texture_size / y2);
		y ++;
	}
}

void	read_textures(void)
{
	int		x;
	int		y;
	void	*_img;
	int		bits;

	_img = mlx_xpm_file_to_image(data.mlx, data.props.no, &x, &y);
	if (!_img)
		end_game("mlx image error");
	data.img_addr[0]
		= (int *)mlx_get_data_addr(_img, &bits, &data.length, &data.endian);
	_img = mlx_xpm_file_to_image(data.mlx, data.props.so, &x, &y);
	if (!_img)
		end_game("mlx image error");
	data.img_addr[1]
		= (int *)mlx_get_data_addr(_img, &bits, &data.length, &data.endian);
	_img = mlx_xpm_file_to_image(data.mlx, data.props.we, &x, &y);
	if (!_img)
		end_game("mlx image error");
	data.img_addr[2]
		= (int *)mlx_get_data_addr(_img, &bits, &data.length, &data.endian);
	_img = mlx_xpm_file_to_image(data.mlx, data.props.ea, &x, &y);
	if (!_img)
		end_game("mlx image error");
	data.img_addr[3]
		= (int *)mlx_get_data_addr(_img, &bits, &data.length, &data.endian);
}

void	draw3d(float wall_hight, int i, int x_offset, int way)
{
	if (way && data.ud)
		strip(i * data.rays.width, (data.window_hight / 2) - (wall_hight / 2),
			wall_hight, x_offset, 0);
	else if (way && !data.ud)
		strip(i * data.rays.width, (data.window_hight / 2) - (wall_hight / 2),
			wall_hight, x_offset, 1);
	else if (!way && data.rl)
		strip (i * data.rays.width, (data.window_hight / 2) - (wall_hight / 2),
			wall_hight, x_offset, 3);
	else if (!way && !data.rl)
		strip (i * data.rays.width, (data.window_hight / 2) - (wall_hight / 2),
			wall_hight, x_offset, 2);
	main_dda(i * data.rays.width, 0, i
		* data.rays.width, (data.window_hight / 2) - (wall_hight / 2));
	main_dda(i * data.rays.width, (data.window_hight / 2) + (wall_hight / 2),
		i * data.rays.width, data.window_hight);
}
