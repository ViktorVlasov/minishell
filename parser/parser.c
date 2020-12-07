/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <ddraco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:48:08 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/07 23:36:58 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

char        *just_add(char *str, char symb)
{
    char    *new_str;
    int     length;

    length = ft_strlen(str);
    new_str = ft_realloc(str, length, length + 1);
    new_str[length] = symb;
    return (new_str);
}
char        *one_comma_worker(int *i, char *buffer, char *str)
{
    int     counter;
    int     buf_size;
    int     iterator;
    int     i_pos;
    
    *i = *i + 1;
    i_pos = *i;
    iterator = 0;
    buf_size = ft_strlen(buffer);
    counter = 0;
    while (str[*i] != '\'')
    {
        counter++;
        *i = *i + 1;
    }
    buffer = ft_realloc(buffer, buf_size, buf_size + counter);
    while (counter > 0)
    {
        buffer[buf_size + iterator] = str[i_pos + iterator];
        iterator++;
        counter--;
    }
    return (buffer);
}
char        *two_comma_worker()
{
    return (NULL);
}

char        **parser(char *line, t_data vars)
{
    char    **parsed_by_semicolon;
    char    *spec_symbols = "$'\"";
    int     i;
    int     commands_amount;
    int     j;
    int     counter;
    int     ready_array_size;
    char    *buffer;

    i = 0;
    counter = 0;
    ready_array_size = 0;
    parsed_by_semicolon = semicolon(line);
    commands_amount = get_amount_line(parsed_by_semicolon);
    buffer = NULL;
	// ft_putchar_fd('1', 1);
    // printf("%d", 1);
    while (i < commands_amount)
    {
        parsed_by_semicolon[i] = ft_strtrim(parsed_by_semicolon[i], " ");
        printf("[%d]%s",i, parsed_by_semicolon[i]);
        i++;
    }
    // ft_putchar_fd('2', 1);
	// ft_putchar_fd('\n', 1);
    while (counter < commands_amount)
    {
        i = 0;
        while (i < ft_strlen(parsed_by_semicolon[counter]))
        {
            vars.args = ft_realloc_2arr(vars.args, ready_array_size,ready_array_size + 1);
            while (parsed_by_semicolon[counter][i] != ' ' && parsed_by_semicolon[counter][i] != '\0')
            {
                if (ft_strchr(spec_symbols, parsed_by_semicolon[counter][i]) == NULL)
				{
					if(parsed_by_semicolon[counter][i] == '\\')
						i++;
                    buffer = just_add(buffer, parsed_by_semicolon[counter][i]);
				}
                else if (parsed_by_semicolon[counter][i] == '\'')
                    buffer = one_comma_worker(&i, buffer, parsed_by_semicolon[counter]);
                else if (parsed_by_semicolon[counter][i] == '\"')
                    two_comma_worker(); //нужен обработчик $
                i++;
            }
			// ft_putstr_fd(buffer, 1);
			// ft_putchar_fd('\n', 1);
            vars.args = add_elem_in_arrayStr(vars.args, buffer);
            if (buffer)
                free(buffer);
            buffer = NULL;
            ready_array_size++;
            while (parsed_by_semicolon[counter][i] == ' ')
				i++;
        }
        //тут вызов функции обработчика
        counter++;
    }
    return (NULL);
}