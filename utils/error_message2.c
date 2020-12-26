/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 17:50:38 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/26 18:10:09 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_message_rel_path(t_data *vars, int f_no_dir_and_exist, \
							int f_have_rights)
{
	if (f_no_dir_and_exist == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(vars->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (f_have_rights == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(vars->args[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
}
