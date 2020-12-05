/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <ddraco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:48:08 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/05 22:27:22 by ddraco           ###   ########.fr       */
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
    if (length == 0)
        new_str[0] = symb;    
    else
        new_str[length + 1] = symb;
    return (new_str);
}
void        one_comma_worker()
{
    
}
void        two_comma_worker()
{
    
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
    // printf("%d", j);
    while (i < commands_amount)
    {
        parsed_by_semicolon[i] = ft_strtrim(parsed_by_semicolon[i], " ");
        printf("[%d]%s",i, parsed_by_semicolon[i]);
        i++;
    }
    
    while (counter < commands_amount)
    {
        i = 0;
        while (i < ft_strlen(parsed_by_semicolon[counter]))
        {
            vars.args = ft_realloc_2arr(vars.args, ready_array_size + 1, 0);
            while (parsed_by_semicolon[counter][i] != ' ')
            {
                if (ft_strchr(spec_symbols, parsed_by_semicolon[counter][i]) == NULL)
                    just_add(buffer, parsed_by_semicolon[counter][i]);
                else if (parsed_by_semicolon[counter][i] == '\'')
                    one_comma_worker();
                else if (parsed_by_semicolon[counter][i] == '\"')
                    two_comma_worker();
                i++;
            }
            
            // else if (parsed_by_semicolon[counter][i] == ' ')
            ready_array_size++;
        }
        counter++;
    }
    return (NULL);
}