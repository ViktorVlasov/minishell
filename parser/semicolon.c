/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <ddraco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 21:40:45 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/21 18:04:07 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int         in_commas(char *line, int symb_id, char comma_type)
{
    int     check1;
    int     check2;
    int     i;
    int     line_len;

    i = 0;
    check1 = 0;
    check2 = 0;
    line_len = ft_strlen(line);
    while (i < line_len)
    {
        if (line[i] == comma_type && check1 != 0)
            check2 = i;
        else if (line[i] == comma_type)
            check1 = i;
        if (check1 != 0 && check2 != 0)
        {
            if (symb_id > check1 && symb_id < check2)
                return (1);
            check1 = 0;
            check2 = 0;
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

size_t	ft_strlcpy1(char *dst, const char *src, size_t size)
{
	size_t tmpsize;
	size_t i;

	if (!dst || !src)
		return (0);
	tmpsize = size;
	i = 0;
	while (src[i] != '\0' && tmpsize > 0)
	{
		dst[i] = src[i];
		tmpsize--;
		i++;
	}
	if (i < size)
		dst[i] = '\0';
	else if (size > 0)
		dst[i - 1] = '\0';
	return (ft_strlen(src));
}

void         semicolon_realloc(sem_data *for_semicolon, int counter, int i)
{
    if (counter == 0)
    {
        for_semicolon->parsed_by_semicolon[counter] = (char *)malloc(i + 1);
        ft_strlcpy(for_semicolon->parsed_by_semicolon[counter],\
                            for_semicolon->line, i + 1);
    }
    else
    {
        for_semicolon->parsed_by_semicolon[counter] =\
                (char *)malloc(i - for_semicolon->previous_semicolon_position);
        ft_strlcpy(for_semicolon->parsed_by_semicolon[counter],\
            for_semicolon->line + for_semicolon->previous_semicolon_position + 1,\
                i - for_semicolon->previous_semicolon_position);
    }
}

void        when_sem_met(sem_data *for_sem, int i, int *counter, char parse_symb)
{
    if (for_sem->line[i] == parse_symb)
    {
        if (in_commas(for_sem->line, i, '\'') == 0 &&\
                 in_commas(for_sem->line, i, '\"') == 0 &&\
                    in_screening(for_sem->line, i) == 0)
        {
            semicolon_realloc(for_sem, *counter, i);
            for_sem->rem = ft_realloc(for_sem->rem,\
                    ft_strlen(for_sem->rem), ft_strlen(for_sem->line) - i);
            ft_strlcpy(for_sem->rem, for_sem->line + i + 1,\
                    ft_strlen(for_sem->line + i));
            for_sem->previous_semicolon_position = i;
            *counter += 1;
        } 
    }
}

int         args_counter(int str_len, char parse_symb, char *line)
{
    int     i;
    int     args_amount;

    i = 0;
    args_amount = 0;
    while (i < str_len)
    {
        if (line[i] == parse_symb)
        {
            if (in_commas(line, i, '\'') == 0 &&
                     in_commas(line, i, '\"') == 0 && in_screening(line, i) == 0)
            {
                args_amount++;
            }
        }
        i++;
    }
    return (args_amount);
}

char        **semicolon(char *line, char parse_symb)
{
    sem_data    for_semicolon;
    int     i;
    int     counter;
    int     line_len;
    int     args_amount;

    line_len = ft_strlen(line);
    args_amount = args_counter(line_len, parse_symb, line);
    for_semicolon.previous_semicolon_position = 0;
    for_semicolon.rem = NULL;
    for_semicolon.line = line;
    counter = 0;
    i = 0;
    for_semicolon.parsed_by_semicolon = (char **)malloc(sizeof(char *)\
                * (args_amount + 2));
    for_semicolon.parsed_by_semicolon[args_amount + 1] = NULL;
    while (i < line_len)
    {
        when_sem_met(&for_semicolon, i, &counter, parse_symb);
        i++;
    }
    semicolon_realloc(&for_semicolon, counter, i);
    if (for_semicolon.rem)
        free(for_semicolon.rem);
    return (for_semicolon.parsed_by_semicolon);
}

// char        **semicolon1(char *line, char parse_symb)
// {
//     int     i;
//     int     counter;
//     int     previous_semicolon_position;
//     char    **parsed_by_semicolon;
//     char    *rem;
//     int     check_counter = 0;

//     previous_semicolon_position = 0;
//     counter = 0;
//     rem = NULL;
//     i = 0;
//     while (i < (int)ft_strlen(line))
//     {
//         if (line[i] == parse_symb)
//         {
//             if (in_commas(line, i, '\'') == 0 &&
//                      in_commas(line, i, '\"') == 0 && in_screening(line, i) == 0)
//             {
//                 check_counter++;
//             }
//         }
//         i++;
//     }
//     parsed_by_semicolon = (char **)malloc(sizeof(char *) * (check_counter + 2));
//     parsed_by_semicolon[check_counter + 1] = NULL;
//     i = 0;
//     while (i < (int)ft_strlen(line))
//     {
//         if (line[i] == parse_symb)
//         {
//             if (in_commas(line, i, '\'') == 0 &&
//                      in_commas(line, i, '\"') == 0 && in_screening(line, i) == 0)
//             {
//                 if (counter == 0)
//                 {
//                     parsed_by_semicolon[counter] = (char *)malloc(i + 1);
//                     ft_strlcpy(parsed_by_semicolon[counter], line, i + 1);
//                 }
//                 else
//                 {
//                     parsed_by_semicolon[counter] = (char *)malloc(i - previous_semicolon_position);
//                     ft_strlcpy(parsed_by_semicolon[counter], line + previous_semicolon_position + 1, i - previous_semicolon_position);
//                 }
//                 rem = ft_realloc(rem, ft_strlen(rem) ,ft_strlen(line) - i);
//                 ft_strlcpy(rem, line + i + 1, ft_strlen(line + i));
                
//                 previous_semicolon_position = i;
//                 counter++;
//             } 
//         }
//         i++;
//     }
//     if (counter == 0)
//     {
//         parsed_by_semicolon[counter] = (char *)malloc(i + 1);
//         ft_strlcpy(parsed_by_semicolon[counter], line, i + 1);
//     }
//     else
//     {
//         parsed_by_semicolon[counter] = (char *)malloc(i - previous_semicolon_position);
//         ft_strlcpy(parsed_by_semicolon[counter], line + previous_semicolon_position + 1, i - previous_semicolon_position);
//     }
//     return (parsed_by_semicolon);
// }