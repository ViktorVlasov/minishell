/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 21:40:45 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/20 00:56:43 by efumiko          ###   ########.fr       */
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
    for_semicolon->parsed_by_semicolon = ft_realloc_2arr(\
                for_semicolon->parsed_by_semicolon, counter ,counter + 1);
    ft_putstr_fd("TEST after realloc_2arr\n", 1);
    for_semicolon->parsed_by_semicolon[counter] =\
            (char *)malloc(i - for_semicolon->previous_semicolon_position + 1 - for_semicolon->add_if_semicolon_met); //возможно на 1 сивол больше надо выделить
    ft_strlcpy1(for_semicolon->parsed_by_semicolon[counter],\
            for_semicolon->line + for_semicolon->previous_semicolon_position +\
                for_semicolon->add_if_semicolon_met, i -\
                    for_semicolon->previous_semicolon_position + 1 -\
                        for_semicolon->add_if_semicolon_met);
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
                        ft_strlen(for_sem->rem), ft_strlen(for_sem->line) - i - 1); //сменили у i плюс на минус
                ft_strlcpy(for_sem->rem, for_sem->line + i + 1, ft_strlen(for_sem->line + i));
                for_sem->previous_semicolon_position = i;
                *counter += 1;
                for_sem->add_if_semicolon_met = 1;
            } 
        }
}

char        **semicolon(char *line, char parse_symb)
{
    sem_data    for_semicolon;
    int     i;
    int     counter;
    int     line_len;

    for_semicolon.add_if_semicolon_met = 0;
    for_semicolon.previous_semicolon_position = 0;
    for_semicolon.rem = NULL;
    for_semicolon.line = line;
    counter = 0;
    i = 0;
    line_len = ft_strlen(line);
    while (i < line_len)
    {
        when_sem_met(&for_semicolon, i, &counter, parse_symb);
        i++;
    }
    ft_putstr_fd("TEST before danger realloc\n", 1);
    //write(1, "1\n", 2);
    semicolon_realloc(&for_semicolon, counter, i);
    ft_putstr_fd("TEST after danger realloc\n", 1);
    if (for_semicolon.rem)
        free(for_semicolon.rem);
    return (for_semicolon.parsed_by_semicolon);
}