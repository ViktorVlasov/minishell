/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 19:12:51 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/07 21:18:14 by efumiko          ###   ########.fr       */
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

char        **ft_realloc_2arr(char **arr, size_t size, int flag)
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

char        **ft_strdup_2arr(char **arr)
{
    char    **res;
    int     i;
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