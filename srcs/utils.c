/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 21:33:46 by viroques          #+#    #+#             */
/*   Updated: 2020/11/01 18:28:00 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int			ft_compt_args(char **tab, int size)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	if (i == size)
		return (1);
	return (0);
}

void		ft_free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int			ft_str_is_digit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int			ft_hash(char *key)
{
	int i;
	int hash_value;

	i = 0;
	hash_value = 0;
	while (key[i])
	{
		hash_value = hash_value << 8;
		hash_value += key[i];
		i++;
	}
	return (hash_value % H_SIZE);
}

int			long_atoi(const char *nptr)
{
	int			i;
	int			negativ;
	long long	res;

	i = 0;
	negativ = 1;
	res = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
			|| nptr[i] == '\r' || nptr[i] == '\v' || nptr[i] == '\f')
		i++;
	if (nptr[i] == '-')
		negativ = -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (nptr[i] <= '9' && nptr[i] >= '0')
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	if (res > INT_MAX)
		res = INT_MAX;
	if (res < INT_MIN)
		res = INT_MIN;
	return ((int)(res * negativ));
}
