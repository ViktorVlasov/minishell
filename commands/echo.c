/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:45:36 by efumiko           #+#    #+#             */
/*   Updated: 2021/01/04 11:30:38 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_data *data)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	if (!(data->args[1]))
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	while (data->args[++i])
	{
		if (ft_strncmp(data->args[i], "-n", 3) == 0)
		{
			flag = 1;
			continue ;
		}
		ft_putstr_fd(data->args[i], 1);
		if (data->args[i + 1])
			ft_putstr_fd(" ", 1);
	}
	if (!flag)
		ft_putstr_fd("\n", 1);
	return (0);
}
