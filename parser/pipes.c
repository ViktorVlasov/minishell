/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 22:54:33 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/26 15:17:31 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	t_data  *tmp_pipe;
	char	*tmp_for_free;

	pipe_counter = 1;
	parsed_by_pipe = semicolon(command, '|');
	pipe_commands_ammount = get_amount_line(parsed_by_pipe);
	take_out_spaces(parsed_by_pipe, pipe_commands_ammount);
	while (pipe_counter < pipe_commands_ammount + 1 && pipe_commands_ammount != 1)
	{
		tmp_pipe = ft_init(vars->envp);
		
		tmp_for_free = parsed_by_pipe[pipe_counter - 1];
		parsed_by_pipe[pipe_counter - 1] = redirect_handler(tmp_pipe, parsed_by_pipe[pipe_counter - 1]); 
		parse_command(parsed_by_pipe[pipe_counter - 1], tmp_pipe);
		pipe_counter++;
		ft_pipeadd_back(&vars, tmp_pipe);
		free(tmp_for_free);
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