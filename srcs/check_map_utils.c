/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 21:32:32 by viroques          #+#    #+#             */
/*   Updated: 2020/10/30 21:32:33 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int        define_min_len(char **file, int i, t_mlx *mlx)
{
    int sup_len;
    int inf_len;
    int min_len;

    if (i > 0)
            sup_len = ft_strlen(file[i - 1]);
        else
            sup_len = 0;
        if (i < mlx->map.line - 1)
            inf_len = ft_strlen(file[i + 1]);
        else
            inf_len = 0;
        if (sup_len < inf_len)
            min_len = sup_len;
        else
            min_len = inf_len;
        if (i == 0)
            min_len = inf_len;
        if (i == mlx->map.line - 1)
            min_len = sup_len;
        return (min_len);
}

