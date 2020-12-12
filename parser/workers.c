/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   workers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <ddraco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 23:03:43 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/12 23:04:16 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char        *add_char(char *str, char symb)
{
    char    *new_str;
    int     length;

    length = ft_strlen(str);
    new_str = ft_realloc(str, length, length + 1);
    new_str[length] = symb;
    return (new_str);
}

char        *variable_handler(char *str, char *dst, int *iterator, t_data *vars)
{
    char    *spec_symbols = "=$'\" ";
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
        dst = ft_itoa(vars->err_status);
    var = add_char(var, '=');
    rez = get_value_from_var(vars->envp, var);
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
    if (str[*i] == '\0')
        buffer = add_char(buffer, str[*i]);
    while (str[*i] != '\'' && str[*i] != '\0')
    {
        buffer = add_char(buffer, str[*i]);
        *i += 1;
    }
    return (buffer);
}

char        *two_comma_worker(int *i, char *buffer, char *str, t_data *vars)
{
    char    *spec_symb;
    
    spec_symb = "\\$\"";
    *i = *i + 1;
    if (str[*i] == '\0')
        buffer = add_char(buffer, str[*i]);
    while (str[*i] != '\0')
    {
        if (str[*i] == '\"' && in_screening(str, *i) == 0)
            break;
        if (str[*i] != '$')
        {
		    if(str[*i] == '\\' && ft_strchr(spec_symb, str[*i + 1]) != NULL)
			    *i += 1;
            buffer = add_char(buffer, str[*i]);
        }
        else if (str[*i] == '$' && in_screening(str, *i) == 0)
            buffer = variable_handler(str, buffer, i, vars);
        *i = *i + 1;
    }
    return (buffer);
}