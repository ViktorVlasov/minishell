/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 22:12:00 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/10 15:52:15 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_arg(char *argument)
{
    int i = 0;
    if ((argument[0] == '\0') || (!ft_isalpha(argument[0]) && (argument[0] != '_')))
        return (1);
    while (argument[++i])
        if (argument[i] == '_' || ft_isalpha(argument[i]) || ft_isdigit(argument[i]))
            continue;
        else
            return (1);
    return (0);
}

int ft_unset(t_data *data)
{
    int i;
    char *arg_with_equal;

    i = 1;
    while (data->args[i])
    {
        if (check_arg(data->args[i]))
        {
            ft_putstr_fd("minishell: unset: `", 1);
            ft_putstr_fd(data->args[i], 1);
            ft_putstr_fd("': not a valid identifier", 1);
            return (1);    
        }
        if (find_elem_in_arrayStr(data->envp, data->args[i], 0))
            delete_elem_in_arrayStr(data->envp, data->args[i], 0);
        else
        {
            arg_with_equal = ft_strjoin(data->args[1], "=");
            if (find_elem_in_arrayStr(data->envp, arg_with_equal, 1))
                delete_elem_in_arrayStr(data->envp, arg_with_equal, 1);
        }
    }
    return (0);
}