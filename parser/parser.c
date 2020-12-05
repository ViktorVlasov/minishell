/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <ddraco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:48:08 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/05 19:17:15 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

void        just_add()
{
    
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
    char    **ready_array;
    char    *spec_symbols = "$'\"";
    int     i;
    int     commands_amount;
    int     j;
    int     counter;

    i = 0;
    counter = 0;
    
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
            
            if (ft_strchr(spec_symbols, parsed_by_semicolon[counter][i]) == NULL)
                just_add();
            else if (parsed_by_semicolon[counter][i] == '\'')
                one_comma_worker();
            else if (parsed_by_semicolon[counter][i] == '\"')
                two_comma_worker();
            else if (parsed_by_semicolon[counter][i] == ' ')
                
            i++;
        }
        counter++;
    }
    return (NULL);
}