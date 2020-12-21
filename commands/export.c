/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 21:36:50 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/21 20:17:19 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_print_args(char **sorted_envp)
{
	int		i;
	char	*name_variable;

	i = 0;
	while (sorted_envp[i])
	{
		ft_putstr_fd("declare -x ", 1);
		if (ft_strchr(sorted_envp[i], '=') != NULL)
		{
			name_variable = get_name_var_from_arg(sorted_envp[i]);
			ft_putstr_fd(name_variable, 1);
			ft_putchar_fd('\"', 1);
			ft_putstr_fd(get_value_from_var(sorted_envp, name_variable), 1);
			ft_putstr_fd("\"\n", 1);
			free(name_variable);
		}
		else
		{
			ft_putstr_fd(sorted_envp[i], 1);
			ft_putstr_fd("\n", 1);
		}
		i++;
	}
	return (0);
}

int		valid_arg(char *arg, t_data *data)
{
	int i;

	i = 0;
	if ((arg[0] == '\0') || (!ft_isalpha(arg[0]) && (arg[0] != '_')))
	{
		data->err_status = 1;
		return (error_message_exp(arg));				
	}
	while (arg[++i])
		if (arg[i] == '=')
			break ;
		else if (arg[i] == '_' || ft_isalpha(arg[i]) || ft_isdigit(arg[i]))
			continue;
		else
		{
			data->err_status = 1;
			return (error_message_exp(arg));				
		}
	return (0);
}

int		ft_export_with_args(t_data *data)
{
	int		i;
	char	*name_variable;

	i = 0;
	while (data->args[++i])
	{
		if (valid_arg(data->args[i], data))
			continue;
		if (ft_strchr(data->args[i], '=') != NULL)
		{
			name_variable = get_name_var_from_arg(data->args[i]);
			if (find_elem_in_arrayStr(data->envp, name_variable, 1))
				replace_elem_in_envp(data->envp, name_variable, data->args[i]);
			else
				data->envp = add_elem_in_arrayStr(data->envp, data->args[i]);
			free(name_variable);
		}
		else
		{
			if (find_elem_in_arrayStr(data->envp, data->args[i], 0) == NULL)
				data->envp = add_elem_in_arrayStr(data->envp, data->args[i]);
		}
	}
	return (data->err_status == 1 ? 1 : 0);
}

int		ft_export(t_data *data)
{
	char	**sorted_envp;

	data->err_status = 0;
	if (!data->args[1])
	{
		sorted_envp = ft_strdup_2arr(data->envp);
		insertion_sort(sorted_envp, get_amount_line(sorted_envp));
		ft_print_args(sorted_envp);
		ft_free_array(&sorted_envp);
	}
	else
		return (ft_export_with_args(data));
	return (0);
}
