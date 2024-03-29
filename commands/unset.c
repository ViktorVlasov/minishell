/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 22:12:00 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/26 17:59:10 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_arg(char *arg, t_data *data)
{
	int i;

	i = 0;
	if ((arg[0] == '\0') || (!ft_isalpha(arg[0]) && (arg[0] != '_')))
	{
		data->err_status = 1;
		return (error_message_unset(arg));
	}
	while (arg[++i])
		if (arg[i] == '_' || ft_isalpha(arg[i]) || ft_isdigit(arg[i]))
			continue;
		else
		{
			data->err_status = 1;
			return (error_message_unset(arg));
		}
	return (0);
}

int	ft_unset(t_data *data)
{
	int		i;
	char	*arg_with_eq;

	i = 0;
	data->err_status = 0;
	while (data->args[++i])
	{
		if (check_arg(data->args[i], data))
			continue;
		if (find_elem_in_arraystr(data->envp, data->args[i], 0))
			data->envp = delete_elem_in_arraystr(data->envp, data->args[i], 0);
		else
		{
			arg_with_eq = ft_strjoin(data->args[i], "=");
			if (find_elem_in_arraystr(data->envp, arg_with_eq, 1))
				data->envp = \
				delete_elem_in_arraystr(data->envp, arg_with_eq, 1);
			free(arg_with_eq);
		}
	}
	return (data->err_status == 1 ? 1 : 0);
}
