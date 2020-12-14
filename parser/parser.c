/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:48:08 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/14 22:37:43 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

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

char        *pars_one_arg(int *i, char *line, t_data *vars)
{
    char    *buffer;
    char    *spec_symbols;
    
    spec_symbols = "$'\"";
    buffer = NULL;
    while (line[*i] != ' ' && line[*i] != '\0')
    {
        if (ft_strchr(spec_symbols, line[*i]) == NULL)
		{
			if(line[*i] == '\\')
				*i += 1;
            buffer = add_char(buffer, line[*i]);
		}
        else if (line[*i] == '\'')
            buffer = one_comma_worker(i, buffer, line);
        else if (line[*i] == '\"')
            buffer = two_comma_worker(i, buffer, line ,vars);
        else if (line[*i] == '$')
            buffer = variable_handler(line, buffer, i, vars);
        if (line[*i] != '\0')
            *i += 1;
    }
    while (line[*i] == ' ')
		*i += 1;
    return (buffer);
}

void        parse_command(char *command, t_data *vars, int *ready_array_size)
{
    int     i;
    int     command_length;
    char    *buffer;

    i = 0;
    command_length = ft_strlen(command);
    while (i < command_length)
    {
        vars->args = ft_realloc_2arr(vars->args,\
                *ready_array_size, *ready_array_size + 1);
        buffer = pars_one_arg(&i, command, vars);
        if (buffer)
        {
            vars->args = add_elem_in_arrayStr(vars->args, buffer);
            free(buffer);
            *ready_array_size += 1;
        }
        buffer = NULL;
    }
}

void        take_out_spaces(char **parsed_by_semicolon, int commands_amount)
{
    char    *tmp;
    int     i;

    i = 0;
    while (i < commands_amount)
    {
        tmp = parsed_by_semicolon[i];
        parsed_by_semicolon[i] = ft_strtrim(parsed_by_semicolon[i], " ");
        free(tmp);
        i++;
    }
}

void        cmd_exec(t_data *vars)
{
    // if нужно проверить, есть ли среди аргментов редирект,
    //else //выполняем эти аргументы
    
}

void        start(char *line, t_data *vars)
{
    char    **parsed_by_semicolon;
    int     commands_amount;
    int     counter;
    int     ready_array_size;

    counter = 0;
    ready_array_size = 0; //когда сделаем очищение структуры перенсти эту переменную в функцию parse_command, чтобы она каждый раз обнулялась и заполняла струтукру с нуля
    parsed_by_semicolon = semicolon(line);
    commands_amount = get_amount_line(parsed_by_semicolon);
    take_out_spaces(parsed_by_semicolon, commands_amount);
    while (counter < commands_amount)
    {
        parse_command(parsed_by_semicolon[counter],vars, &ready_array_size);
        // cmd_exec(vars);
        counter++;
    }
    ft_free_array(&parsed_by_semicolon);
}




// int i = 0;
// int count_redir = 0;
// while (args[i])
// {
//     if (args[i] == ">>" && args[i+1])
     
       
//         count_redir++;
// }

// i = 0;
// while (args[i])
// {
//     if (args[i] == ">>" && args[i + 1])
//         fd = open() // создаем файл
//         count_redir--;
//         if (count_redir == 1) // 1 or 0???
//             dup2() // перенаправляем стандартный вывод в файл
//     i++;
// }

// char **names_files;

// while (args[i])
// {
//     if (args[i] == ">>" && args[i+1])
//     {
//         names_files = ft_realloc_2arr(names_files, get_amount_line(names_files), get_amount_line(names_files) + 1);
//         names_files = add_elem_in_arrayStr(names_files, args[i+1]);
//     }
// }

