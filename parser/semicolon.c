/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 21:40:45 by ddraco            #+#    #+#             */
/*   Updated: 2020/11/28 22:34:01 by efumiko          ###   ########.fr       */
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
        if (check1 == 1 && check2 == 1)
        {
            if (symb_id > check1 && symb_id < check2)
                return (1);
        }
        if (line[i] == comma_type)
            check1 = 1;
        if (line[i] == comma_type && check1 == 1)
            check2 = 1;
    }
    return (0);
}

int         in_screening(char *line, int symb_id)
{
    if (line[symb_id - 1] == '\\')
        return (1);
    return (0);
}

char        **ft_big_strdup(char **arr, size_t size)
{
    char    **res;

    res = (char **)malloc(size * sizeof(char*));
    if (res == NULL)
        return (NULL);
    // перевыделение памяти под двумерный массив
}

char        **semicolon(char *line)
{
    int     i;
    char    **parsed_by_semicolon;

    parsed_by_semicolon = (char**)malloc(get_amount_line(line) * sizeof(char*));
    i = 0;
    while (i < ft_strlen(line))
    {
        if (line[i] == ';')
        {
            if (in_commas(line, i, '\'') == 1 ||
                     in_commas(line, i, '\"') == 1 || in_screening(line, i) == 1)
                //что случается, когда нашли точку с запятой, не дописано условие
        }
    }
}