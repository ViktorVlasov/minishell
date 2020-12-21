/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 21:19:11 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/21 20:25:32 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_data *data)
{
	int i;

	i = 0;
	while (data->envp[i])
	{
		if (ft_strchr(data->envp[i], '=') != NULL)
		{
			ft_putstr_fd(data->envp[i], 1);
			ft_putchar_fd('\n', 0);
		}
		i++;
	}
	return (0);
}
