/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 21:36:50 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/12 20:03:23 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void InsertionSort(char **mass, int n)
{
	char *newElement;
	int location;
	int i;

	i = 1;
	while (i < n)
	{
		newElement = mass[i];
		location = i - 1;
		while (location >= 0 && (ft_strcmp(mass[location], newElement) >= 0))
		{
			mass[location+1] = mass[location];
			location = location - 1;
		}
		mass[location+1] = newElement;
		i++;
	}
}

char *get_name_var_from_arg(char *argument)
{
	int res_len;
	int i;
	char *name_var;

	i = 0;
	while (argument[i] != '=')
		i++;    
	name_var = malloc(sizeof(char) * (i + 2));
	i = 0;
	while (argument[i] != '=')
	{
		name_var[i] = argument[i];
		i++;
	}
	name_var[i] = argument[i];
	i++;
	name_var[i] = '\0';
	return (name_var);
}

int ft_print_args(char **sorted_envp)
{
	int i;
	char *name_variable;

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

int valid_arg(char *arg)
{
	int i = 0;
	if ((arg[0] == '\0') || (!ft_isalpha(arg[0]) && (arg[0] != '_')))
		return (1);
	while (arg[++i])
		if (arg[i] == '=')
			break;
		else if (arg[i] == '_' || ft_isalpha(arg[i]) || ft_isdigit(arg[i]))
			continue;
		else
			return (1);
	return (0);
}

void replace_elem_in_envp(char **src, char *name_variable, char *replace)
{
	int i;
	char *tmp_for_free;
	
	i = 0;
	while (src[i])
	{
		if (ft_strncmp(src[i], name_variable, ft_strlen(name_variable)) == 0)
		{
			tmp_for_free = src[i];
			src[i] = ft_strdup(replace);
			free(tmp_for_free);
		}
		i++;   
	}
}

int ft_export_with_args(t_data *data)
{
	int i;
	char *name_variable;

	i = 1;
	while (data->args[i])
	{
		if (valid_arg(data->args[i]))
		{
			ft_putstr_fd("minishell: export: `", 1);
			ft_putstr_fd(data->args[i], 1);
			ft_putstr_fd("': not a valid identifier\n", 1);
			return (1);
		}
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
			if (find_elem_in_arrayStr(data->envp, data->args[i], 0) == NULL)
				data->envp = add_elem_in_arrayStr(data->envp, data->args[i]);
		i++;
	}
	return (0);
}

int ft_export(t_data *data)
{
	char **sorted_envp;
	
	if (!data->args[1])
	{
		sorted_envp = ft_strdup_2arr(data->envp);
		InsertionSort(sorted_envp, get_amount_line(sorted_envp));
		ft_print_args(sorted_envp);
		ft_free_array(&sorted_envp);
	}
	else 
		return (ft_export_with_args(data));       
	return (0);
}