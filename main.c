/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 00:35:02 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/31 13:03:59 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

t_data		*g_vars;

t_data		*ft_init(char **content)
{
	t_data	*new;

	new = (t_data*)malloc(sizeof(t_data));
	if (new == NULL)
		return (NULL);
	new->args = NULL;
	new->envp = ft_strdup_2arr((char **)content);
	new->pipe = NULL;
	new->redirects = NULL;
	new->err_status = 0;
	new->pid = 0;
	new->signal = 0;
	return (new);
}

void		init_structure(t_data *g_vars)
{
	g_vars->fd0 = dup(0);
	g_vars->fd1 = dup(1);
}

void		sig_int(int sig)
{
	(void)sig;
	if (g_vars->pid == 0)
	{
		ft_putstr_fd("\b\b  ", 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("minishell: ", 2);
		g_vars->err_status = 1;
	}
	else
	{
		ft_putstr_fd("\n", 2);
		g_vars->signal = 1;
		g_vars->err_status = 130;
	}
}

void		sig_quit(int code)
{
	if (g_vars->pid != 0)
	{
		ft_putstr_fd("Quit: ", 2);
		ft_putnbr_fd(code, 2);
		ft_putchar_fd('\n', 2);
		g_vars->err_status = 131;
		g_vars->signal = 1;
	}
	else
		ft_putstr_fd("\b\b  \b\b", 2);
}

int			main(int argc, char **argv, char **envp)
{
	int		gnl_ret;
	char	*line;

	(void)argc;
	(void)argv;
	g_vars = ft_init(envp);
	init_structure(g_vars);
	signal(SIGQUIT, &sig_quit);
	signal(SIGINT, &sig_int);
	ft_putstr_fd("minishell: ", 1);
	while ((gnl_ret = get_next_line(0, &line)) > 0)
	{
		start(line, g_vars);
		free(line);
		ft_putstr_fd("minishell: ", 1);
	}
	free(line);
	if (gnl_ret == -2)
		ft_putstr_fd("exit\n", 2);
	ft_free_array(&g_vars->envp);
	free(g_vars);
}
