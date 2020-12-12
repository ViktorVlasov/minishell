/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:07:25 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/12 19:40:38 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	t_data data;

	//int i = 0;
	// printf("======TEST1======\n");
    // while (envp[i])
    // {
    //     printf("%s\n", envp[i]);
    //     i++;
    // }
	// printf("======END_TEST1======\n");

	data.envp = ft_strdup_2arr(envp);
	data.args = argv;
	
	
	ft_export(&data);

	// int k = 0;
	// printf("======TEST_add_VARIABLE======\n");
	// while (data.envp[k])
    // {
    //     printf("%s\n", data.envp[k]);
    //     k++;
    // }

	//i = 0;
	// printf("======TEST2======\n");
	// while (data.envp[i])
    // {
    //     printf("%s\n", envp[i]);
    //     i++;
    // }
	// printf("======END_TEST2======\n");
	
	char **test;
	if (argv[1])
	{
		test = malloc(sizeof(char*) * 3);
		test[0] = ft_strdup("export");	
		test[1] = ft_strdup("ABC=20");
		test[2] = NULL;
 		data.args = test;
		ft_export(&data);
	}
	ft_env(&data);
	//ft_echo(&data);
	//ft_exit(&data);
	ft_free_array(&data.envp);
	if (test)
		free(test);
}
