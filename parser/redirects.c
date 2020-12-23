/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 23:01:49 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/24 00:18:53 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_redadd_back(r_data **lst, r_data *new)
{
	r_data	*lst_back;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		lst_back = *lst;
		while (lst_back->next)
			lst_back = lst_back->next;
		lst_back->next = new;
	}
	else
		*lst = new;
}

r_data	*ft_init_red(void)
{
	r_data *new;

	new = (r_data*)malloc(sizeof(r_data));
	if (new == NULL)
		return (NULL);
    new->file_name = NULL;
	new->next = NULL;
	new->redir_type = NULL;
	return (new);
}

int			check_for_all(char *line, int i)
{
	if (in_commas(line, i, '\'') == 0 &&\
         in_commas(line, i, '\"') == 0 &&\
            in_screening(line, i) == 0)
		return (0);
	return (1);
}

void		ft_one_red(int *i, r_data *tmp_red, char *line)
{
	int		iterator;
	char	*tmp;
	iterator = *i;
	tmp_red->redir_type = add_char(tmp_red->redir_type, line[iterator]);
	iterator++;
	while (line[iterator] == ' ')
		iterator++;
	while (line[iterator] != ' ')
	{
		tmp_red->file_name = add_char(tmp_red->file_name, line[iterator]);
		iterator++;
	}
	tmp = tmp_red->file_name; //почистить???
	// tmp_red->file_name = pars_one_arg() надо обработать переменные в имени файла??
	*i = iterator;
}

void		ft_two_red()
{
	
}

void		ft_red_worker(r_data *tmp_red, char *line, int *i)
{
	if (check_for_all(line, *i) == 0)
	{
		if (check_for_all(line, *i + 1) == 0)
			ft_two_red();
		else
			ft_one_red(i, tmp_red, line);
	}
}

void redirect_handler(t_data *vars, char *line)
{
	int     redirect_counter;
	int     pipe_commands_ammount;
	r_data  *tmp_red;
	char	*result;
	int		i;
	int		flag_quote;

	i = 0;
	flag_quote = 0;
	result = NULL;
	while (line[i] != '\0')
	{		
		if (line[i] == '>' || line[i] == '<')
		{
			tmp_red = ft_init_red();
			ft_red_worker(tmp_red, line, &i);
			ft_redadd_back(&vars->redirects, tmp_red);
		}
		result = add_char(result, line[i]);
		i++;
	}
	return (result); 
}