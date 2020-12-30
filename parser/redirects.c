/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 23:01:49 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/31 00:27:59 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			check_for_all(char *line, int i)
{
	if (in_commas(line, i, '\'') == 0 &&\
			in_commas(line, i, '\"') == 0 &&\
				in_screening(line, i) == 0)
		return (0);
	return (1);
}

void		ft_red_parse(int *i, t_rdata *tmp_red, char *line, t_data *vars)
{
	int		iterator;
	char	*tmp_name;
	int		zero;

	zero = 0;
	iterator = *i;
	tmp_name = NULL;
	while (line[iterator] == ' ')
		iterator++;
	while (line[iterator] != ' ' && line[iterator] != '\0')
	{
		tmp_name = add_char(tmp_name, line[iterator]);
		iterator++;
	}
	*i = iterator;
	tmp_red->file_name = pars_one_arg(&zero, tmp_name, vars);
	free(tmp_name);
}

void		ft_red_worker(t_rdata *tmp_red, char *line, int *i, t_data *vars)
{
	if (check_for_all(line, *i) == 0)
	{
		tmp_red->redir_type = add_char(tmp_red->redir_type, line[*i]);
		if (line[*i] == '>' && line[*i + 1] == '>' \
							&& check_for_all(line, *i + 1) == 0)
		{
			tmp_red->redir_type = add_char(tmp_red->redir_type, line[*i + 1]);
			*i += 1;
		}
		*i += 1;
		ft_red_parse(i, tmp_red, line, vars);
	}
}

char		*redirect_handler(t_data *vars, char *line)
{
	t_rdata	*tmp_red;
	char	*result;
	int		i;
	char	*tmp_for_free;

	i = 0;
	result = NULL;
	while (line[i] != '\0')
	{
		if (line[i] == '>' || line[i] == '<')
		{
			tmp_red = ft_init_red();
			ft_red_worker(tmp_red, line, &i, vars);
			ft_redadd_back(&vars->redirects, tmp_red);
		}
		if (line[i] != '\0')
		{
			result = add_char(result, line[i]);
			i++;
		}
	}
	tmp_for_free = result;
	result = ft_strtrim(result, " ");
	free(tmp_for_free);
	return (result);
}
