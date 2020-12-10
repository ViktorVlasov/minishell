/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:07:25 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/10 15:10:05 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int	main(int argc, char *argv[], char *envp[])
{
	int i;

	i = 0;
	while (i != 10)
	{
		if (i == 7)
		{
			i += 2;
			continue;
		}
		i++;
	}
	return (0);
}
