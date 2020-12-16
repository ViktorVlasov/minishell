/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 20:24:25 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/16 15:03:37 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{

    (void)argc;
	(void)argv;
    
    // malloc and init t_data
    // signal(...)
    while (1)
    {
        // parse str and fill t_data struct
        
        // print("minishell")
        // function that exec commands
        // free struct
    }
    return (0);
}