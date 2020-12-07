/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 22:12:00 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/07 23:44:52 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_unset(t_data *data)
{
    int i;
    char *arg_with_equal;

    i = 1;
    while (data->args[i])
    {
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