;;/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 22:28:08 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/28 18:27:14 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			error_message_unset(char *invalid_arg)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(invalid_arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

int			error_message_exp(char *invalid_arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(invalid_arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

int			path_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

static int	ft_puterror(char *s)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

int			error_check(char *line)
{
	int	i;
	int	first_after_space;

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
			return (ft_puterror(";;"));
		else if (line[i] == ';' && i == first_after_space)
			return (ft_puterror(";"));
		else if ((line[i] == '>' && line[i + 1] == '\0') || \
			(line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '\0') || \
			(line[i] == '<' && line[i + 1] == '\0') || \
			(line[i] == '<' && line[i + 1] == '<' && line[i + 2] == '\0'))
			return (ft_puterror("newline"));
		else if (line[i] == '|' && i == first_after_space)
			return (ft_puterror("|"));
	return (0);
}
