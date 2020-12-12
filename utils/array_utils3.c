/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 20:40:19 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/12 20:41:37 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	insertion_sort(char **mass, int n)
{
	char	*new_element;
	int		location;
	int		i;

	i = 1;
	while (i < n)
	{
		new_element = mass[i];
		location = i - 1;
		while (location >= 0 && (ft_strcmp(mass[location], new_element) >= 0))
		{
			mass[location + 1] = mass[location];
			location = location - 1;
		}
		mass[location + 1] = new_element;
		i++;
	}
}

char	*get_name_var_from_arg(char *argument)
{
	int		res_len;
	int		i;
	char	*name_var;

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

void	replace_elem_in_envp(char **src, char *name_variable, char *replace)
{
	int		i;
	char	*tmp_for_free;

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