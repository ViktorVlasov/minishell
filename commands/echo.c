/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:45:36 by efumiko           #+#    #+#             */
/*   Updated: 2020/11/28 20:29:13 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_echo(char **args)
{
    int i;
    int flag;

    i = 1; // maybe 0
    flag = 0;
    if (!args[i])
    {
        ft_putchar_fd('\n', 1);
        return ;
    }
    else if (ft_strncmp(args[i], "-n", 3) == 0)
    {
        flag = 1;
        i++;
    }
    while (args[i])
    {
        ft_putstr_fd(args[i], 1);
        if (args[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (!flag)
        ft_putstr_fd("\n", 1);
}