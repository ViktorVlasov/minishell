/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <ddraco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:45:08 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/05 22:39:57 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
    //char **args_for_commands;
    char    *line = "echo ; ech'o' 1\"2\"3";
    t_data  vars;
    vars.envp = ft_strdup_2arr(envp);
    
    int i = 0;
    int check = get_amount_line(envp);
    // while (i < check)
    // {
    //     printf("%s\n", vars.envp[i]);
    //     i++;
    // }
    
     parser(line, vars);
    
    // while (get_next_line(0, &line) > 0)
    // {
    //     parser(line, vars);
    //     free(line);
    // }

    //ft_echo(argv);
    // ft_pwd();
}