/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 19:32:33 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/26 18:02:55 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**add_elem_in_arraystr(char **src, char *elem)
{
	char	**res;
	int		i;

	i = 0;
	if (!src)
		return (NULL);
	if (!elem)
		return (src);
	while (src[i])
		i++;
	if (!(res = (char**)malloc(sizeof(char*) * (i + 2))))
		return (NULL);
	res[i + 1] = NULL;
	i = 0;
	while (src[i])
	{
		res[i] = src[i];
		i++;
	}
	if (!(res[i] = ft_strdup(elem)))
		return (NULL);
	free(src);
	return (res);
}

/*
** boolFindPart = 1 - string from src includes elem
** boolFindPart = 0 - string from src equals elem
** if (!src)
**		return (NULL);
**	if (!elem)
**		return (src);
*/

char	**delete_elem_in_arraystr(char **src, char *elem, int bool_findpart)
{
	char	**res;
	int		i;
	int		k;

	i = 0;
	while (src[i])
		i++;
	if (!(res = (char**)malloc(sizeof(char*) * i)))
		return (NULL);
	i = 0;
	k = 0;
	while (src[i])
	{
		if (((bool_findpart && \
		ft_strncmp(src[i], elem, ft_strlen(elem)) == 0)) \
		|| ((bool_findpart == 0) && ft_strcmp(src[i], elem) == 0))
			free(src[i++]);
		else
			res[k++] = src[i++];
	}
	res[k] = NULL;
	free(src);
	return (res);
}

/*
** bool_findpart = 1 - string from src includes elem
** bool_findpart = 0 - string from src equals elem
*/

char	*find_elem_in_arraystr(char **src, char *elem, int bool_findpart)
{
	int i;

	i = 0;
	if (!src)
		return (NULL);
	if (!elem)
		return (NULL);
	while (src[i])
	{
		if ((bool_findpart == 0) && (ft_strcmp(src[i], elem) == 0))
			return (src[i]);
		if ((bool_findpart == 1) \
		&& (ft_strncmp(src[i], elem, ft_strlen(elem)) == 0))
			return (src[i]);
		i++;
	}
	return (NULL);
}

/*
** example value of name_var - "HOME="
*/

char	*get_value_from_var(char **envp, char *name_var)
{
	int		i;
	char	*result;

	i = 0;
	if (!envp)
		return (NULL);
	if (!name_var)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name_var, ft_strlen(name_var)) == 0)
		{
			result = envp[i] + ft_strlen(name_var);
			return (result);
		}
		i++;
	}
	return (NULL);
}

void	ft_free_array(char ***ar)
{
	char	**array;
	int		i;

	array = *ar;
	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}
