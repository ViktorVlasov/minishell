/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <ddraco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 21:40:45 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/04 21:47:03 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int         in_commas(char *line, int symb_id, char comma_type)
{
    int     check1;
    int     check2;
    int     i;

    i = 0;
    check1 = 0;
    check2 = 0;
    while (i < ft_strlen(line))
    {
        if (line[i] == comma_type && check1 != 0)
            check2 = i;
        else if (line[i] == comma_type)
            check1 = i;
        if (check1 != 0 && check2 != 0)
        {
            if (symb_id > check1 && symb_id < check2)
                return (1);
        }
        i++;
    }
    return (0);
}

int         in_screening(char *line, int symb_id)
{
    if (line[symb_id - 1] == '\\')
        return (1);
    return (0);
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

// static void	*ft_realloc(void *ptr, size_t newsize)
// {
// 	char	*newptr;
// 	size_t	cursize;

// 	if (ptr == 0)
// 		return (malloc(newsize));
// 	cursize = sizeof(ptr);
// 	if (newsize <= cursize)
// 		return (ptr);
// 	newptr = malloc(newsize);
// 	ft_memcpy(ptr, newptr, cursize);
// 	free(ptr);
// 	return (newptr);
// }

static void	*ft_realloc(void *ptr, int size, int newsize)
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


char        **semicolon(char *line)
{
    int     i;
    int     counter;
    int     add_if_semicolon_met;
    int     previous_semicolon_position;
    char    **parsed_by_semicolon;
    char    *rem;

    add_if_semicolon_met = 0;
    previous_semicolon_position = 0;
    counter = 0;
    rem = NULL;
    // parsed_by_semicolon = (char**)malloc(1 *sizeof(char*));
    i = 0;
    while (i < ft_strlen(line))
    {
        if (line[i] == ';')
        {
            if (in_commas(line, i, '\'') == 0 &&
                     in_commas(line, i, '\"') == 0 && in_screening(line, i) == 0)
            {
                parsed_by_semicolon = ft_big_strdup(parsed_by_semicolon, counter + 1, 0);
                parsed_by_semicolon[counter] = (char *)malloc(i - previous_semicolon_position);
                ft_strlcpy(parsed_by_semicolon[counter], line + previous_semicolon_position + add_if_semicolon_met, i - previous_semicolon_position + 1 - add_if_semicolon_met);
                rem = ft_realloc(rem, ft_strlen(rem) ,ft_strlen(line) - i + 1);
                ft_strlcpy(rem, line + i + 1, ft_strlen(line + i));
                
                previous_semicolon_position = i;
                counter++;
                add_if_semicolon_met = 1;
            } 
        }
        i++;
    }
    parsed_by_semicolon = ft_big_strdup(parsed_by_semicolon, counter + 2, 1);
    parsed_by_semicolon[counter] = (char *)malloc(i - previous_semicolon_position);
    ft_strlcpy(parsed_by_semicolon[counter], line + previous_semicolon_position + add_if_semicolon_met, i - previous_semicolon_position + 1 - add_if_semicolon_met);
    parsed_by_semicolon[counter + 1] = NULL;
    return (parsed_by_semicolon);
}