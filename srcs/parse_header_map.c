/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 21:33:24 by viroques          #+#    #+#             */
/*   Updated: 2020/11/01 17:57:35 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int				check_text(char **val, char *h, t_mlx *mlx, int *i_text)
{
	if (h[ft_hash(val[0])] == 0)
		h[ft_hash(val[0])] = 1;
	else
		return (error("Duplicate texture\n", -1));
	if (!ft_compt_args(val, 2))
		return (error("Texture must be followed by only one path\n", -1));
	if (!ft_strncmp(val[0], "S", 2))
	{
		if (!(mlx->texture[4]->img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr,
		val[1], &mlx->texture[4]->width, &mlx->texture[4]->height)))
			return (error("Invalide sprite texture, impossible to read\n", -1));
		mlx->texture[4]->data = (int *)mlx_get_data_addr(mlx->texture[4]
		->img_ptr, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	}
	else
	{
		if (!(mlx->texture[*i_text]->img_ptr = mlx_xpm_file_to_image(
		mlx->mlx_ptr, val[1], &mlx->texture[*i_text]->width,
		&mlx->texture[*i_text]->height)))
			return (error("Failed to load texture\n", -1));
		mlx->texture[*i_text]->data = (int *)mlx_get_data_addr(mlx->texture
		[*i_text]->img_ptr, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
		*i_text = *i_text + 1;
	}
	return (0);
}

static int			ft_get_resolution(char **values, char *hash, t_mlx *mlx)
{
	if (!ft_compt_args(values, 3))
		return (error("Res is follow by less or more than 2 values\n", -1));
	if (hash[ft_hash("R")] == 0)
	{
		hash[ft_hash(values[0])] = 1;
		if (!ft_str_is_digit(values[1]) || !ft_str_is_digit(values[2]))
			return (error("Resolution values must be a digit\n", -1));
		mlx->win_width = ft_atoi(values[1]);
		mlx->win_height = ft_atoi(values[2]);
		if (mlx->win_width < 0 || mlx->win_height < 0)
			return (error("Negative values for resolution\n", -1));
		//add resolution fo screen if >
	}
	else
		return (error("Resolution is define more than one time\n", -1));
	return (0);
}

static int			header_map(char **val, t_mlx *mlx, t_header_parser *parse)
{
	if (val[0][0] == 'R')
	{
		if (ft_get_resolution(val, parse->hash, mlx) < 0)
			return (-1);
	}
	else if (ft_strnstr("NOSOWEEA", val[0], 9))
	{
		if (check_text(val, parse->hash, mlx, &parse->index_text) < 0)
			return (-1);
	}
	else if (val[0][0] == 'F' || val[0][0] == 'C')
	{
		if (ft_get_color_fc(mlx, val, parse->hash) < 0)
			return (-1);
	}
	else if (val[0][0] == '\n')
		parse->compt = parse->compt - 1;
	else if ((val[0][0] == ' ' || ft_isdigit(val[0][0])) && parse->compt == 8)
		return (1);
	else
		return (error("Invalide characters in map\n", -1));
	return (0);
}

int					parse_header_map(t_mlx *mlx, char **file, char **file_n)
{
	t_header_parser parse;

	ft_bzero(&parse, sizeof(t_header_parser));
	if (ft_malloc_text(mlx) < 0)
		return (-1);
	while (file_n[parse.index])
	{
		if (!(parse.values = ft_split(file_n[parse.index], ' ')))
		{
			error("Malloc failed\n", -1);
			return (-1);
		}
		parse.check = header_map(parse.values, mlx, &parse);
		if (parse.check == 1)
		{
			ft_free_tab(parse.values);
			break ;
		}
		if (parse.check < 0)
			return (error_free("", -1, parse.values));
		ft_free_tab(parse.values);
		parse.index++;
		parse.compt++;
	}
	return (ft_count(mlx, &file[parse.compt], &file_n[parse.index]));
}
