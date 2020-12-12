/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:45:36 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/12 16:07:24 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_data *data)
{
	int i;
	int flag;

	i = 1;
	flag = 0;
	if (!(data->args[i]))
	{
		ft_putchar_fd('\n', 1);
		return ;
	}
	else if (ft_strncmp(data->args[i], "-n", 3) == 0)
	{
		flag = 1;
		i++;
	}
	while (data->args[i])
	{
		ft_putstr_fd(data->args[i], 1);
		if (data->args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!flag)
		ft_putstr_fd("\n", 1);
}
