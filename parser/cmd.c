/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 23:59:09 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/31 15:00:30 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_commands(t_data *vars, int is_pipe)
{
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

void	do_cmd(t_data *vars, int is_pipe)
{
	if (vars->redirects)
		if ((vars->err_status = do_redirects(vars)) == 1)
		{
			free_listof_redirects(&vars->redirects);
			return ;
		}
	if (vars->args && vars->args[0])
		exec_commands(vars, is_pipe);
	free_listof_redirects(&vars->redirects);
}

void	one_command(t_data *vars)
{
	do_cmd(vars, 0);
	dup2(vars->fd0, 0);
	dup2(vars->fd1, 1);
}

void	cmd_exec(t_data *vars)
{
	int		fd[2];
	t_data	*current_pipe;

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
			close(1);
			dup2(vars->fd1, 1);
			current_pipe = current_pipe->pipe;
		}
		do_cmd(current_pipe, 1);
		dup2(vars->fd0, 0);
		dup2(vars->fd1, 1);
	}
	else
		one_command(vars);
}
