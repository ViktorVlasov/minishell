/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 19:12:51 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/20 00:12:34 by efumiko          ###   ########.fr       */
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

int global_i = 1;

char        **ft_realloc_2arr(char **arr, int prev_size ,int size)
{
    char    **res;
    int     i;

    
    // for test
    ft_putnbr_fd(global_i, 1);
    ft_putstr_fd("\n", 1);
    global_i++;
    // end test
    
    i = 0;
    res = (char **)malloc((size + 1) * sizeof(char*));
    if (res == NULL)
        return (NULL);
    ft_putnbr_fd(size, 1);
    ft_putstr_fd("^size^\n", 1);
    while (i < prev_size)
    {
        ft_putstr_fd(arr[i], 1);
        ft_putstr_fd("\n", 1);
        res[i] = ft_strdup(arr[i]);
        // free(arr[i]);
        // arr[i] = NULL;
        i++;
    }
    ft_putstr_fd("Finish\n", 1);
    while (i < size + 1)
        res[i++] = NULL;
    if (arr && prev_size != 0)
        ft_free_array(&arr);
        // free(arr);
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