/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_work.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 00:10:05 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/31 00:27:51 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	check_file_names(t_data *vars)
{
	t_rdata *tmp;

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

static	int	error_message_redir(char *file_name)
{
	ft_putstr_fd("minishell: ", 2);
	perror(file_name);
	return (1);
}

static	int	work_with_redir(t_rdata *redir)
{
	if (ft_strcmp(redir->redir_type, ">") == 0)
	{
		if ((redir->red_fd = \
		open(redir->file_name, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)) == -1)
			return (error_message_redir(redir->file_name));
		dup2(redir->red_fd, 1);
	}
	if (ft_strcmp(redir->redir_type, ">>") == 0)
	{
		if ((redir->red_fd = \
		open(redir->file_name, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU)) == -1)
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
	t_rdata *tmp;

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
