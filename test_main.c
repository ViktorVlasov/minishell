/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:07:25 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/12 22:55:28 by efumiko          ###   ########.fr       */
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

	ft_cd(&data);
	ft_pwd();

	// char **test;
	// if (argv[1])
	// {
	// 	test = malloc(sizeof(char*) * 4);
	// 	test[0] = ft_strdup("export");	
	// 	test[1] = ft_strdup("COLORTERM=123");
	// 	test[2] = NULL;
	// 	test[3] = NULL;
 	// 	data.args = test;
	// 	ft_export(&data);
		
	// 	test[1] = ft_strdup("HOME=5555");
	// 	data.args = test;
	// 	ft_export(&data);
		
	// 	test[1] = NULL;
	// 	data.args = test;
	// 	ft_export(&data);
	// }
	
	// printf("\n\n");
	// test[0] = ft_strdup("unset");
	// test[1] = ft_strdup("Apple_PubSub_Socket_Render");
	// test[2] = ft_strdup("COLORTERM");
	// data.args = test;
	// ft_unset(&data);
	
	// test[0] = ft_strdup("export");
	// test[1] = NULL;
	// test[2] = NULL;
	// data.args = test;
	// ft_export(&data);

	
	// ft_export(&data);

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
	
	
	// ft_env(&data);
	//ft_echo(&data);
	//ft_exit(&data);
	ft_free_array(&data.envp);
	// if (test)
	// 	free(test);
}
