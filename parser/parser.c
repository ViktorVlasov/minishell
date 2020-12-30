/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:48:08 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/31 00:17:20 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

char		*pars_one_arg(int *i, char *line, t_data *vars)
{
	char	*buffer;
	char	*spec_symbols;

	spec_symbols = "$'\"";
	buffer = NULL;
	while (line[*i] != ' ' && line[*i] != '\0')
	{
		if (ft_strchr(spec_symbols, line[*i]) == NULL)
		{
			if (line[*i] == '\\')
				*i += 1;
			buffer = add_char(buffer, line[*i]);
		}
		else if (line[*i] == '\'')
			buffer = one_comma_worker(i, buffer, line);
		else if (line[*i] == '\"')
			buffer = two_comma_worker(i, buffer, line, vars);
		else if (line[*i] == '$')
			buffer = variable_handler(line, buffer, i, vars);
		if (line[*i] != '\0')
			*i += 1;
	}
	while (line[*i] == ' ')
		*i += 1;
	return (buffer);
}

void		parse_command(char *command, t_data *vars)
{
	int		i;
	int		command_length;
	char	*buffer;
	int		ready_array_size;

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
			vars->args = add_elem_in_arraystr(vars->args, buffer);
			free(buffer);
			ready_array_size += 1;
		}
		buffer = NULL;
	}
}

void		take_out_spaces(char **parsed_by_semicolon, int commands_amount)
{
	char	*tmp;
	int		i;

	i = 0;
	while (i < commands_amount)
	{
		tmp = parsed_by_semicolon[i];
		parsed_by_semicolon[i] = ft_strtrim(parsed_by_semicolon[i], " ");
		free(tmp);
		i++;
	}
}

void		free_structure(t_data *vars)
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

void		start(char *line, t_data *vars)
{
	char	**par_b_sem;
	int		commands_amount;
	int		counter;
	char	*tmp_for_free;

	counter = 0;
	if (error_check(line) == 1)
		return ;
	par_b_sem = semicolon(line, ';');
	commands_amount = get_amount_line(par_b_sem);
	take_out_spaces(par_b_sem, commands_amount);
	while (counter < commands_amount)
	{
		if (!pipe_handler(par_b_sem[counter], vars))
		{
			tmp_for_free = par_b_sem[counter];
			par_b_sem[counter] = redirect_handler(vars, par_b_sem[counter]);
			parse_command(par_b_sem[counter], vars);
			free(tmp_for_free);
		}
		cmd_exec(vars);
		free_structure(vars);
		counter++;
	}
	ft_free_array(&par_b_sem);
}
