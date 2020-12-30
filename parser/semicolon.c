/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 21:40:45 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/30 11:24:18 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		in_commas(char *line, int symb_id, char comma_type)
{
	int	check1;
	int	check2;
	int	i;
	int	line_len;

	i = 0;
	check1 = -1;
	check2 = -1;
	line_len = ft_strlen(line);
	while (i < line_len)
	{
		if (line[i] == comma_type && check1 != -1)
			check2 = i;
		else if (line[i] == comma_type)
			check1 = i;
		if (check1 != -1 && check2 != -1)
		{
			if (symb_id > check1 && symb_id < check2)
				return (1);
			check1 = -1;
			check2 = -1;
		}
		i++;
	}
	return (0);
}

int		in_screening(char *line, int symb_id)
{
	if (line[symb_id - 1] == '\\')
		return (1);
	return (0);
}

void	semicolon_realloc(sem_data *for_semicolon, int counter, int i)
{
	if (counter == 0)
	{
		if ((for_semicolon->parsed_by_semicolon[counter] = (char *)malloc(i + 1)) == NULL)
			return ;
		ft_strlcpy(for_semicolon->parsed_by_semicolon[counter], \
							for_semicolon->line, i + 1);
	}
	else
	{
		if ((for_semicolon->parsed_by_semicolon[counter] = (char *)malloc(i - for_semicolon->previous_semicolon_position)) == NULL)
			return ;
		ft_strlcpy(for_semicolon->parsed_by_semicolon[counter], \
			for_semicolon->line + \
			for_semicolon->previous_semicolon_position + 1, \
				i - for_semicolon->previous_semicolon_position);
	}
}

void	when_sem_met(sem_data *for_sem, int i, int *counter, char parse_symb)
{
	if (for_sem->line[i] == parse_symb)
	{
		if (in_commas(for_sem->line, i, '\'') == 0 && \
				in_commas(for_sem->line, i, '\"') == 0 && \
				in_screening(for_sem->line, i) == 0)
		{
			semicolon_realloc(for_sem, *counter, i);
			for_sem->previous_semicolon_position = i;
			*counter += 1;
		}
	}
}

int		args_counter(int str_len, char parse_symb, char *line)
{
	int	i;
	int	args_amount;

	i = 0;
	args_amount = 0;
	while (i < str_len)
	{
		if (line[i] == parse_symb)
		{
			if (in_commas(line, i, '\'') == 0 && \
				in_commas(line, i, '\"') == 0 && \
				in_screening(line, i) == 0)
			{
				args_amount++;
			}
		}
		i++;
	}
	return (args_amount);
}

char	**semicolon(char *line, char parse_symb)
{
	sem_data	for_semicolon;
	int			i;
	int			counter;
	int			line_len;
	int			args_amount;

	line_len = ft_strlen(line);
	args_amount = args_counter(line_len, parse_symb, line);
	for_semicolon.previous_semicolon_position = 0;
	for_semicolon.line = line;
	counter = 0;
	i = 0;
	for_semicolon.parsed_by_semicolon = (char **)malloc(sizeof(char *)\
				* (args_amount + 2));
	for_semicolon.parsed_by_semicolon[args_amount + 1] = NULL;
	while (i < line_len)
	{
		when_sem_met(&for_semicolon, i, &counter, parse_symb);
		i++;
	}
	semicolon_realloc(&for_semicolon, counter, i);
	return (for_semicolon.parsed_by_semicolon);
}
