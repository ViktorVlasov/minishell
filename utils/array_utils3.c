/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 20:40:19 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/30 23:55:59 by efumiko          ###   ########.fr       */
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

int		in_commas(char *line, int symb_id, char comma_type)
{
	int	check1;
	int	check2;
	int	i;
	int	line_len;

	i = 0;
	check1 = -1;
	check2 = -1;
	line_len = ft_strlen(line);
	while (i < line_len)
	{
		if (line[i] == comma_type && check1 != -1)
			check2 = i;
		else if (line[i] == comma_type)
			check1 = i;
		if (check1 != -1 && check2 != -1)
		{
			if (symb_id > check1 && symb_id < check2)
				return (1);
			check1 = -1;
			check2 = -1;
		}
		i++;
	}
	return (0);
}

int		in_screening(char *line, int symb_id)
{
	if (line[symb_id - 1] == '\\')
		return (1);
	return (0);
}
