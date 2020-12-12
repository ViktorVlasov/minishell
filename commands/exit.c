/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 22:11:55 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/12 23:00:58 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** exit 123 123 - many argumenst bash: exit: too many arguments
** exit asdsd - bash: exit: asdsd: numeric argument required
*/

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

int			ft_exit(t_data *data)
{
	int code;

	code = data->err_status; // code = $?
	ft_putstr_fd("exit\n", 1);
	if (data->args[1])
	{
		if (data->args[2])
		{
			ft_putstr_fd("exit: too many arguments\n", 1);
			return (1);
		}
		else if (check_argument_for_exit(data->args[1]))
		{
			ft_putstr_fd("exit: ", 1);
			ft_putstr_fd(data->args[1], 1);
			ft_putstr_fd(": numeric argument required\n", 1);
			code = 255;
		}
		else
			code = ft_atoi(data->args[1]);
	}
	exit(code % 255);
}
