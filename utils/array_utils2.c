/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 19:12:51 by ddraco            #+#    #+#             */
/*   Updated: 2021/01/05 13:24:25 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		get_amount_line(char **lines)
{
	int	i;

	i = 0;
	if (!lines || !(*lines))
		return (0);
	while (lines[i])
		i++;
	return (i);
}

char	**ft_realloc_2arr(char **arr, int prev_size, int size)
{
	char	**res;
	int		i;

	i = 0;
	res = (char **)malloc((size + 1) * sizeof(char*));
	if (res == NULL)
		return (NULL);
	while (i < prev_size)
	{
		res[i] = ft_strdup(arr[i]);
		i++;
	}
	while (i < size + 1)
		res[i++] = NULL;
	if (arr && prev_size != 0)
		ft_free_array(&arr);
	return (res);
}

char	**ft_strdup_2arr(char **arr)
{
	char	**res;
	int		i;
	int		size;

	size = get_amount_line(arr);
	i = 0;
	res = (char **)malloc(sizeof(char*) * (size + 1));
	if (res == NULL)
		return (NULL);
	while (i < size)
	{
		res[i] = ft_strdup(arr[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	*ft_realloc(void *ptr, int size, int newsize)
{
	char	*str;
	char	*new;
	int		i;

	str = (char*)ptr;
	if (!(new = (char*)malloc(sizeof(char) * (newsize + 1))))
	{
		if (ptr && size != 0)
			free(ptr);
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		*(new + i) = *(str + i);
		i++;
	}
	while (i < newsize + 1)
	{
		*(new + i) = '\0';
		i++;
	}
	if (ptr && size != 0)
		free(ptr);
	return (new);
}

void	take_out_spaces(char **parsed_by_semicolon, int commands_amount)
{
	char	*tmp;
	int		i;

	i = 0;
	while (i < commands_amount)
	{
		tmp = parsed_by_semicolon[i];
		parsed_by_semicolon[i] = ft_strtrim(parsed_by_semicolon[i], " ");
		free(tmp);
		i++;
	}
}
