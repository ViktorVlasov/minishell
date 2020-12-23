/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 22:57:33 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/23 23:02:58 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void        do_cmd(t_data *vars, int is_pipe)
{
	// if (vars->names_files)
	// 	do_redirects();
	// Обработка редиректов (возможно здесь)
	// printf("%s\n", args[0]);
	if (vars->args && vars->args[0])
	{
		// ft_putstr_fd(vars->args[0], 1);
		if (ft_strcmp(vars->args[0], "pwd") == 0)
			vars->err_status = ft_pwd();
		else if (ft_strcmp(vars->args[0], "env") == 0)
			vars->err_status = ft_env(vars);
		else if (ft_strcmp(vars->args[0], "echo") == 0)
			vars->err_status = ft_echo(vars);
		else if (ft_strcmp(vars->args[0], "export") == 0)
			vars->err_status = ft_export(vars);
		else if (ft_strcmp(vars->args[0], "unset") == 0)
			vars->err_status = ft_unset(vars);
		else if (ft_strcmp(vars->args[0], "cd") == 0)
			vars->err_status = ft_cd(vars);
		else if (ft_strcmp(vars->args[0], "exit") == 0)
			vars->err_status = ft_exit(vars, is_pipe);
		else
			vars->err_status = ft_command(vars);
	}
}

void        cmd_exec(t_data *vars)
{
	// if нужно проверить, есть ли среди аргментов редирект,
	//else //выполняем эти аргументы
	int fd[2];
	t_data *current_pipe;
	current_pipe = vars->pipe;
	
	if (vars->pipe)
	{
		while (current_pipe->pipe)
		{
			pipe(fd);
			dup2(fd[1], 1);
			do_cmd(current_pipe, 1);
			dup2(fd[0], 0);
			close(fd[1]);
			close(fd[0]);
			close(1); // мб можно убрать
			dup2(vars->fd1, 1);
			current_pipe = current_pipe->pipe;
		}
		do_cmd(current_pipe, 1);
		dup2(vars->fd0, 0);
	}
	else
		do_cmd(vars, 0);
}