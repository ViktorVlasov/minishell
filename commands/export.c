/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 21:36:50 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/10 16:04:28 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

/**
 * Два случая - 1) есть аргументы, 2) нет аргументов
 * 2) Нет Аргументов:
 * 1. дублируем список envp
 * 2. сортируем его (функция сортировки)
 * 3. выводим, перед выводом приписываем declare -x (функция вывода)
 * 
 * 1)
 * 
 * 
*/

void InsertionSort(char **mass, int n)
{
    char *newElement;
    int location;
    int i;

    i = 1;
    while (i < n)
    {
        newElement = mass[i];
        location = i - 1;
        while (location >= 0 && (ft_strcmp(mass[location], newElement) >= 0))
        {
            mass[location+1] = mass[location];
            location = location - 1;
        }
        mass[location+1] = newElement;
        i++;
    }
}

int ft_print_args(char **sorted_envp)
{
    int i;

    i = 0;
    while (sorted_envp[i])
    {
        ft_putstr_fd("declare -x ", 1);
        ft_putstr_fd(sorted_envp[i], 1);
        ft_putstr_fd("\n", 1);
        i++;
    }
    return (0);
}



int ft_export(t_data *data)//t_data *data)
{
    char **sorted_envp;
    
    if (!data->args[1])
    {
        write(1, "1\n", 2);
        sorted_envp = ft_strdup_2arr(data->envp);//data->envp);
        write(1, "2\n", 2);
        InsertionSort(sorted_envp, get_amount_line(sorted_envp));
        write(1, "3\n", 2);
        ft_print_args(sorted_envp);
    }
    else 
    {
        ft_export_with_args();
    }
        
    return (0);
}