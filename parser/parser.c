/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <ddraco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:48:08 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/12 20:00:45 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

char        *add_char(char *str, char symb)
{
    char    *new_str;
    int     length;

    length = ft_strlen(str);
    new_str = ft_realloc(str, length, length + 1);
    new_str[length] = symb;
    return (new_str);
}

char        *variable_handler(char *str, char *dst, int *iterator, t_data vars)
{
    char    *spec_symbols = "$'\" ";
    char    *rez;
    char    *tmp;
    char    *var;
    
    var = NULL;
    *iterator += 1;
    while (ft_strchr(spec_symbols, str[*iterator]) == NULL && str[*iterator] != '\0')
    {
        var = add_char(var, str[*iterator]);
        *iterator += 1;
    }
    *iterator -= 1; //потому что в основном цикле дальше идет i++
    if (var && var[0] == '?')
        dst = ft_itoa(vars.err_status);
    var = add_char(var, '=');
    rez = get_value_from_var(vars.envp, var);
    if (var)
        free(var);
    var = NULL;
    if (rez == NULL)
        return (dst);
    if (dst != NULL)
    {
        tmp = dst;
        dst = ft_strjoin(dst, rez);
        free(tmp);
    }
    else
        dst = ft_strdup(rez);
    return(dst);
}

char        *one_comma_worker(int *i, char *buffer, char *str)
{   
    *i = *i + 1;
    while (str[*i] != '\'' && str[*i] != '\0' && in_screening(str, *i) == 0)
    {
        if(str[*i] == '\\')
	    	*i += 1;
        buffer = add_char(buffer, str[*i]);
        *i += 1;
    }
    return (buffer);
}

char        *two_comma_worker(int *i, char *buffer, char *str, t_data vars)
{
    *i = *i + 1;
    while (str[*i] != '\"' && in_screening(str, *i) == 0 && str[*i] != '\0')
    {
        if (str[*i] != '$')
		{
			if(str[*i] == '\\')
	    		*i += 1;
            buffer = add_char(buffer, str[*i]);
		}
        else if (str[*i] == '$')
            buffer = variable_handler(str, buffer, i, vars);
        *i = *i + 1;
    }
    return (buffer);
}

int        error_check(char *line)
{
    int     i;

    i = 0;
    while (line[i] == ' ' && line[i] != '\0')
        i++;
    if (line[i] == ';' && line[i + 1] == '\0')
        ft_putstr_fd("syntax error near unexpected token `;'", 1);
    else if (line[i] == ';' && line[i + 1] == ';')
        ft_putstr_fd("syntax error near unexpected token `;;'", 1);
    else if (line[i] == '>' && line[i + 1] == '\0')
        ft_putstr_fd("syntax error near unexpected token `newline'", 1);
    else if (line[i] == '>' && line[i + 1] == '>')
        ft_putstr_fd(";;", 1);
        
        
         //; > >> < << |
    return (0);
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
    char    *tmp;
    int     error;

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
        tmp = parsed_by_semicolon[i];
        parsed_by_semicolon[i] = ft_strtrim(parsed_by_semicolon[i], " ");
        free(tmp);
        // printf("[%d]%s",i, parsed_by_semicolon[i]);
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
                    buffer = add_char(buffer, parsed_by_semicolon[counter][i]);
				}
                else if (parsed_by_semicolon[counter][i] == '\'')
                    buffer = one_comma_worker(&i, buffer, parsed_by_semicolon[counter]);
                else if (parsed_by_semicolon[counter][i] == '\"')
                    buffer = two_comma_worker(&i, buffer, parsed_by_semicolon[counter],vars);
                else if (parsed_by_semicolon[counter][i] == '$')
                    buffer = variable_handler(parsed_by_semicolon[counter], buffer, &i, vars);
                i++;
            }
            if (buffer)
            {
                ft_putstr_fd(buffer, 1);
                ft_putchar_fd('\n', 1);
            }
            if (buffer)
            {
                vars.args = add_elem_in_arrayStr(vars.args, buffer);
                free(buffer);
                ready_array_size++;
            }
            buffer = NULL;
            while (parsed_by_semicolon[counter][i] == ' ')
				i++;
        }
        //тут вызов функции обработчика
        counter++;
    }
    return (NULL);
}