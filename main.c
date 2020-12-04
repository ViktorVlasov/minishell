/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:45:08 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/04 23:32:44 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
    //char **args_for_commands;
    //parser(argc, argv, envp);
    //commands();
    char    *line;
    t_data  vars;

    line = NULL;
    vars.envp = envp;
    while (get_next_line(0, &line) > 0)
    {
        parser(line, vars);
        free(line);
    }
    
    // ft_putstr_fd(envp[1], 1);
    // ft_putchar_fd('\n', 1);

    //ft_echo(argv);
    // ft_pwd();
}