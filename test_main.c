/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:07:25 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/18 23:35:15 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	struct stat test_struct;

	char *s = "../../../mcarry/Desktop";
	
	if (stat(s, &test_struct) == -1)
		printf("FILEEEEE");

	if (test_struct.st_mode & S_IFDIR)
		printf("catalog");
	else if (test_struct.st_mode & S_IFREG)
		printf("YYYES");
	else
		printf("SHIT HAPPENS");
	
}