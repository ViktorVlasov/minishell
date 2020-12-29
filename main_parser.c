/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:45:08 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/26 15:33:333 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

t_data	*ft_init(char **content)
{
	t_data *new;

	new = (t_data*)malloc(sizeof(t_data));
	if (new == NULL)
		return (NULL);
    new->args = NULL;
	new->envp = ft_strdup_2arr((char **)content);
	new->pipe = NULL;
	new->redirects = NULL;
    new->err_status = 0;
	return (new);
}

void init_structure(t_data *vars)
{
    vars->fd0 = dup(0);
    vars->fd1 = dup(1);    
}


int main(int argc, char **argv, char **envp)
{
    //char **args_for_commands;
    //OS_ACTIVITY_DT_MODE=enable
    // char    *line = "echo '123\'";
    //echo ; ech'ab    co'   23
    argc = 0;
    argv = NULL;
    // char    *line = "echo tttt >> test111 >> test33 123 | echo 123 > test222 | grep \"t\" < test222";
    // char    *line = "export ;export abrakadabra; unset abrakadabra; export";
    // char    *line = "   echo abc | grep "abc";export abc=123;export sdasd; export"; //WTF????????????????????????????????????????????????
    // char    *line = "echo 1111111111111111111; echo 12abc=123';' echo12 sdasd"; 
    char    *line;
	// char    *line = "grep \"abc\" < test1 >> test2 | echo 123 | echo 444";
    t_data  *vars;
    vars = ft_init(envp);

    //для дебагера!!!
    // vars->envp = add_elem_in_arraystr(vars->envp, "PATH=/Users/efumiko/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Users/efumiko/.brew/bin");
    
    init_structure(vars);
    
    // get_next_line(0, &line);
    // start(line, vars);
    // free(line);
    
    ft_putstr_fd("minishell: ", 1);
    while (get_next_line(0, &line) > 0)
    {
        start(line, vars);
        free(line);
        ft_putstr_fd("minishell: ", 1);
    }

    ft_free_array(&vars->envp);
    free(vars);
}