/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <ddraco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:45:08 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/12 23:07:19 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
    //char **args_for_commands;
    //OS_ACTIVITY_DT_MODE=enable
    // char    *line = "echo '123\'";
    //echo ; ech'ab    co'   23
    char    *line = "   echo \"\\hello \\$PWD\"";
    // char    *line;
    t_data  vars;
    vars.err_status = 0;
    vars.envp = ft_strdup_2arr(envp);
    
    int i = 0;
    int check = get_amount_line(envp);
    // while (i < check)
    // {
    //     printf("%s\n", vars.envp[i]);
    //     i++;
    // }
    
    // get_next_line(0, &line);
    parser(line, &vars);
    
    // while (get_next_line(0, &line) > 0)
    // {
    //     parser(line, vars);
    //     free(line);
    // }
    
    check = get_amount_line(vars.args);
    while (i < check)
    {
        printf("%s\n", vars.args[i]);
        i++;
    }
}