/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:48:08 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/21 21:28:23 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

int		ft_puterror(char *s)
{
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

int        error_check(char *line)
{
	int     i;
	int		first_after_space;

	i = 0;
	while (line[i] == ' ' && line[i] != '\0')
		i++;
	first_after_space = i;
	i--;
	while (line[++i] != '\0')
		if (in_commas(line, i, '\'') == 1 ||
				in_commas(line, i, '\"') == 1 || in_screening(line, i) == 1)
			continue;
		else if (line[i] == ';' && line[i + 1] == ';')
			return(ft_puterror(";;"));
		else if (line[i] == ';' && i == first_after_space)
			return(ft_puterror(";"));
		else if ((line[i] == '>' && line[i + 1] == '\0') || \
			(line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '\0') || \
			(line[i] == '<' && line[i + 1] == '\0') || \
			(line[i] == '<' && line[i + 1] == '<' && line[i + 2] == '\0'))
			return(ft_puterror("newline"));
		else if (line[i] == '|' && i == first_after_space)
			return(ft_puterror("|"));
	return (0);
}

char        *pars_one_arg(int *i, char *line, t_data *vars)
{
	char    *buffer;
	char    *spec_symbols;
	
	spec_symbols = "$'\"";
	buffer = NULL;
	while (line[*i] != ' ' && line[*i] != '\0')
	{
		if (ft_strchr(spec_symbols, line[*i]) == NULL)
		{
			if(line[*i] == '\\')
				*i += 1;
			buffer = add_char(buffer, line[*i]);
		}
		else if (line[*i] == '\'')
			buffer = one_comma_worker(i, buffer, line);
		else if (line[*i] == '\"')
			buffer = two_comma_worker(i, buffer, line ,vars);
		else if (line[*i] == '$')
			buffer = variable_handler(line, buffer, i, vars);
		if (line[*i] != '\0')
			*i += 1;
	}
	while (line[*i] == ' ')
		*i += 1;
	return (buffer);
}

void        parse_command(char *command, t_data *vars)
{
	int     i;
	int     command_length;
	char    *buffer;
	int     ready_array_size;

	i = 0;
	ready_array_size = 0;
	command_length = ft_strlen(command);
	while (i < command_length)
	{
		vars->args = ft_realloc_2arr(vars->args,\
				ready_array_size, ready_array_size + 1);
		buffer = pars_one_arg(&i, command, vars);
		if (buffer)
		{
			vars->args = add_elem_in_arrayStr(vars->args, buffer);
			free(buffer);
			ready_array_size += 1;
		}
		buffer = NULL;
	}
}


void        take_out_spaces(char **parsed_by_semicolon, int commands_amount)
{
	char    *tmp;
	int     i;

	i = 0;
	while (i < commands_amount)
	{
		tmp = parsed_by_semicolon[i];
		parsed_by_semicolon[i] = ft_strtrim(parsed_by_semicolon[i], " ");
		free(tmp);
		i++;
	}
}

void        do_cmd(t_data *vars, int is_pipe)
{
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


void	ft_pipeadd_back(t_data **lst, t_data *new)
{
	t_data	*lst_back;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		lst_back = *lst;
		while (lst_back->pipe)
			lst_back = lst_back->pipe;
		lst_back->pipe = new;
	}
	else
		*lst = new;
}


int        pipe_handler(char *command, t_data *vars)
{
	char    **parsed_by_pipe;
	int     pipe_counter;
	int     pipe_commands_ammount;
	t_data  *tmp;

	pipe_counter = 1;
	parsed_by_pipe = semicolon(command, '|');
	pipe_commands_ammount = get_amount_line(parsed_by_pipe);
	take_out_spaces(parsed_by_pipe, pipe_commands_ammount);
	while (pipe_counter < pipe_commands_ammount + 1 && pipe_commands_ammount != 1)
	{
		tmp = ft_init(vars->envp);
		parse_command(parsed_by_pipe[pipe_counter - 1], tmp);
		pipe_counter++;
		ft_pipeadd_back(&vars, tmp);
	}
	ft_free_array(&parsed_by_pipe); 
	return (pipe_counter == 1 ? 0 : 1);      
}


void	free_listof_pipes(t_data **lst)
{
	t_data	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		ft_free_array(&((*lst)->args));
		ft_free_array(&((*lst)->envp));
		tmp = *lst;
		*lst = tmp->pipe;
		free(tmp);
	}
	*lst = NULL;
}


void free_structure(t_data *vars)
{
	if (vars)
	{
		if (vars->args)
			ft_free_array(&vars->args);
		vars->args = NULL;
		free_listof_pipes(&vars->pipe);
		vars->pipe = NULL;
	}
}

void        start(char *line, t_data *vars)
{
	char    **parsed_by_semicolon;
	int     commands_amount;
	int     counter;

	counter = 0;
	if (error_check(line) == 1)
		return ;
	parsed_by_semicolon = semicolon(line, ';');
	// ft_putstr_fd("TEST final", 1);
	commands_amount = get_amount_line(parsed_by_semicolon);
	take_out_spaces(parsed_by_semicolon, commands_amount);
	while (counter < commands_amount)
	{
		if (!pipe_handler(parsed_by_semicolon[counter], vars))
			parse_command(parsed_by_semicolon[counter], vars);
		cmd_exec(vars);
		free_structure(vars);
		counter++;
	}
	ft_free_array(&parsed_by_semicolon);
}




// int i = 0;
// int count_redir = 0;
// while (args[i])
// {
//     if (args[i] == ">>" && args[i+1])
//         count_redir++;
// }

// i = 0;
// while (args[i])
// {
//     if (args[i] == ">>" && args[i + 1])
//         fd = open() // создаем файл
//         count_redir--;
//         if (count_redir == 1) // 1 or 0???
//             dup2() // перенаправляем стандартный вывод в файл
//     i++;
// }

// char **names_files;

// while (args[i])
// {
//     if (args[i] == ">>" && args[i+1])
//     {
//         names_files = ft_realloc_2arr(names_files, get_amount_line(names_files), get_amount_line(names_files) + 1);
//         names_files = add_elem_in_arrayStr(names_files, args[i+1]);
//     }
// }

