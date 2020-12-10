/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:07:25 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/11 00:08:32 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

void test_free(char *test_fr)
{
	free(test_fr);
}

int	main(int argc, char **argv, char **envp)
{
	t_data data;

	data.envp = ft_strdup_2arr(envp);
	data.args = argv;
	
	ft_export(&data);
	ft_free_array(&data.envp);
}
