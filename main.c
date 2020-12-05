/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <ddraco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:45:08 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/05 19:21:03 by ddraco           ###   ########.fr       */
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
    char    *line = "echo ; ech'o' 1\"2\"3";
    t_data  vars;
    vars.envp = ft_big_strdup(envp, get_amount_line(envp), 0);
    
    parser(line, vars);
    // line = NULL;
    // vars.envp = envp;
    
    // while (get_next_line(0, &line) > 0)
    // {
    //     parser(line, vars);
    //     free(line);
    // }
    
    // ft_putstr_fd(envp[1], 1);
    // ft_putchar_fd('\n', 1);

    //ft_echo(argv);
    // ft_pwd();
}