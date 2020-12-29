/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 22:11:55 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/29 12:57:09 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	check_argument_for_exit(char *string)
{
	int i;

	i = 0;
	while (string[i])
	{
		if ((i == 0) && (string[i] == '-'))
		{
			i++;
			continue;
		}
		if (!ft_isdigit(string[i]))
			return (1);
		i++;
	}
	return (0);
}

int			ft_exit(t_data *data, int is_pipe)
{
	int code;

	code = data->err_status;
	if (is_pipe == 0)
		ft_putstr_fd("exit\n", 1);
	if (data->args[1])
	{
		if (data->args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		else if (check_argument_for_exit(data->args[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(data->args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			code = 255;
		}
		else
			code = ft_atoi(data->args[1]);
	}
	if (is_pipe == 0)
		exit(code % 256);
	return (0);
}
