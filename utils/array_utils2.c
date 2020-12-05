/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <ddraco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 19:12:51 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/05 19:19:55 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		get_amount_line(char **lines)
{
	int i;

	i = 0;
	if (!lines || !(*lines))
		return (0);
	while (lines[i])
		i++;
	return (i);
}

char        **ft_big_strdup(char **arr, size_t size, int flag)
{
    char    **res;
    int     i;

    i = 0;
    res = (char **)malloc(size * sizeof(char*));
    if (res == NULL)
        return (NULL);
    while (i < size - 1 - flag)
    {
        res[i] = ft_strdup(arr[i]);
        i++;
    }
    i = 0;
    while (i < size - 1 - flag)
    {
        free(arr[i]);
        i++;
    }
    if (size - flag > 1)
        free(arr);
    return(res);
}

void	*ft_realloc(void *ptr, int size, int newsize)
{
	char	*str;
	char	*new;
	int		i;

	str = (char*)ptr;
	if (!(new = (char*)malloc(sizeof(char) * newsize + 1)))
	{
		if (ptr && size != 0)
			free(ptr);
		return (NULL);
	}
	i = -1;
	while (++i < size)
		*(new + i) = *(str + i);
	while (i < newsize)
		*(new + i++) = '\0';
	if (ptr && size != 0)
		free(ptr);
	return (new);
}