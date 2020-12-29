/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 22:57:33 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/28 16:06:191 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// check_files_names (ambiguous redirect) ==> error_status = 1
// if open return -1 ==> error_status = 1

int			check_file_names(t_data *vars)
{
	r_data *tmp;
	tmp = vars->redirects;
	
	while (tmp)
	{
		if (!vars->redirects->file_name)
		{
			ft_putstr_fd("minishell: ambiguous redirect\n", 2);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int error_message_redir(char *file_name)
{
	ft_putstr_fd("minishell: ", 2);
	perror(file_name);
	return (1);
}

int		work_with_redir(r_data *redir)
{
	if (ft_strcmp(redir->redir_type, ">") == 0)
	{
		if ((redir->red_fd = open(redir->file_name, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)) == -1)
			return (error_message_redir(redir->file_name));
		dup2(redir->red_fd, 1);
	}
	if (ft_strcmp(redir->redir_type, ">>") == 0)
	{
		if ((redir->red_fd = open(redir->file_name, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU)) == -1)
			return (error_message_redir(redir->file_name));
		dup2(redir->red_fd, 1);
	}
	if (ft_strcmp(redir->redir_type, "<") == 0)
	{
		if ((redir->red_fd = open(redir->file_name, O_RDONLY, S_IRWXU)) == -1)
			return (error_message_redir(redir->file_name));
		dup2(redir->red_fd, 0);
	}
	return (0);
}

int			do_redirects(t_data *vars)
{
	r_data *tmp;
	tmp = vars->redirects;

	if (check_file_names(vars) == 1)
		return (1);
	while (tmp)
	{
		if (work_with_redir(tmp))
			return (1);
		tmp = tmp->next;
	}
	return (0);
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
	free_listof_redirects(&vars->redirects);
}

// grep "abc" < test1 >> test2 | echo 123 | echo 444
// Первый пайп:
// 1) grep "abc" тянет данные из файла test1
// 2) печатает результат в файл test2


void	cmd_exec(t_data *vars)
{
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
			dup2(fd[0], 0); // возможно close(0)
			close(fd[1]);
			close(fd[0]);
			close(1);
			dup2(vars->fd1, 1);
			current_pipe = current_pipe->pipe;
		}
		do_cmd(current_pipe, 1);
		dup2(vars->fd0, 0);
	}
	else
	{
		do_cmd(vars, 0);
		dup2(vars->fd0, 0);
		dup2(vars->fd1, 1);
	}
}


// void	redir(t_mini *mini, t_token *token, int type)
// {
// 	ft_close(mini->fdout);
// 	if (type == TRUNC)
// 		mini->fdout = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
// 	else
// 		mini->fdout = open(token->str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
// 	if (mini->fdout == -1)
// 	{
// 		ft_putstr_fd("minishell: ", STDERR);
// 		ft_putstr_fd(token->str, STDERR);
// 		ft_putendl_fd(": No such file or directory", STDERR);
// 		mini->ret = 1;
// 		mini->no_exec = 1;
// 		return ;
// 	}
// 	dup2(mini->fdout, STDOUT);
// }

// void	input(t_mini *mini, t_token *token)
// {
// 	ft_close(mini->fdin);
// 	mini->fdin = open(token->str, O_RDONLY, S_IRWXU);
// 	if (mini->fdin == -1)
// 	{
// 		ft_putstr_fd("minishell: ", STDERR);
// 		ft_putstr_fd(token->str, STDERR);
// 		ft_putendl_fd(": No such file or directory", STDERR);
// 		mini->ret = 1;
// 		mini->no_exec = 1;
// 		return ;
// 	}
// 	dup2(mini->fdin, STDIN);
// }

// int		minipipe(t_mini *mini)
// {
// 	pid_t	pid;
// 	int		pipefd[2];

// 	pipe(pipefd);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		ft_close(pipefd[1]);
// 		dup2(pipefd[0], STDIN);
// 		mini->pipin = pipefd[0];
// 		mini->pid = -1;
// 		mini->parent = 0;
// 		mini->no_exec = 0;
// 		return (2);
// 	}
// 	else
// 	{
// 		ft_close(pipefd[0]);
// 		dup2(pipefd[1], STDOUT);
// 		mini->pipout = pipefd[1];
// 		mini->pid = pid;
// 		mini->last = 0;
// 		return (1);
// 	}
// }