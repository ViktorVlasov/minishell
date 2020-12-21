/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 22:28:08 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/21 19:49:01 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		error_message_unset(char *invalid_arg)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(invalid_arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

int		error_message_exp(char *invalid_arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(invalid_arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

int	path_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	return (1);
}
