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

t_data *vars;

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
	new->pid = 0;
	new->signal = 0;
	return (new);
}

void init_structure(t_data *vars)
{
    vars->fd0 = dup(0);
    vars->fd1 = dup(1);    
}

//OS_ACTIVITY_DT_MODE=enable
// char    *line = "echo tttt >> test111 >> test33 123 | echo 123 > test222 | grep \"t\" < test222";
    // char    *line = "export ;export abrakadabra; unset abrakadabra; export";
    // char    *line = "   echo abc | grep "abc";export abc=123;export sdasd; export"; //WTF????????????????????????????????????????????????
    // char    *line = "echo 1111111111111111111; echo 12abc=123';' echo12 sdasd"; 
	// char	*line = ">$abc; ls";
	// char    *line = "grep abc < test_abc >> te | echo 123 > test_out123 >> test_outf123 | env >> env.txt";

    // start(line, vars);


void	sig_int(int sig)
{
	(void)sig;
    if (vars->pid == 0)
	{
		ft_putstr_fd("\b\b  ", 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("minishell: ", 2);
		vars->err_status = 1;
	}
	else
	{
		ft_putstr_fd("\n", 2);
		vars->signal = 1;
		vars->err_status = 130;
	}
}

void	sig_quit(int code)
{
	if (vars->pid != 0)
	{
		ft_putstr_fd("Quit: ", 2);
		ft_putnbr_fd(code, 2);
		ft_putchar_fd('\n', 2);
		vars->err_status = 131;
		vars->signal = 1;
	}
	else
		ft_putstr_fd("\b\b  \b\b", 2);
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    
	char	*line;
	//char    *line = "ls -la; asd dasdasd";
    // | echo 123 > test_out123 >> test_out_f123 | env >> env.txt | export >> env.txt";
    
	// t_data  *vars;
    vars = ft_init(envp);
    init_structure(vars);
    // start(line, vars);
    int gnl_ret;
	signal(SIGQUIT, &sig_quit);
	signal(SIGINT, &sig_int);
    ft_putstr_fd("minishell: ", 1);
    while ((gnl_ret = get_next_line(0, &line)) > 0)
    {
        start(line, vars);
        free(line);
        ft_putstr_fd("minishell: ", 1);
    }
    free(line);
    if (gnl_ret == -2)
        ft_putstr_fd("exit\n", 2);
    ft_free_array(&vars->envp);
    free(vars);
}

// cclaude minishell

// void	sig_int(int code)
// {
// 	(void)code;
// 	if (g_sig.pid == 0)
// 	{
// 		ft_putstr_fd("\b\b  ", STDERR);
// 		ft_putstr_fd("\n", STDERR);
// 		ft_putstr_fd("\033[0;36m\033[1m🤬 minishell ▸ \033[0m", STDERR);
// 		g_sig.exit_status = 1;
// 	}
// 	else
// 	{
// 		ft_putstr_fd("\n", STDERR);
// 		g_sig.exit_status = 130;
// 	}
// 	g_sig.sigint = 1;
// }

// void	sig_quit(int code)
// {
// 	char	*nbr;

// 	nbr = ft_itoa(code);
// 	if (g_sig.pid != 0)
// 	{
// 		ft_putstr_fd("Quit: ", STDERR);
// 		ft_putendl_fd(nbr, STDERR);
// 		g_sig.exit_status = 131;
// 		g_sig.sigquit = 1;
// 	}
// 	else
// 		ft_putstr_fd("\b\b  \b\b", STDERR);
// 	ft_memdel(nbr);
// }

// void	sig_init(void)
// {
// 	g_sig.sigint = 0;
// 	g_sig.sigquit = 0;
// 	g_sig.pid = 0;
// 	g_sig.exit_status = 0;
// }