/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 21:19:11 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/12 20:58:36 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_data *data)
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
}
