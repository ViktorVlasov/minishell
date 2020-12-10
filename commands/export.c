/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 21:36:50 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/11 00:11:24 by efumiko          ###   ########.fr       */
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

int valid_arg(char *arg)
{
    int i = 0;
    if ((arg[0] == '\0') || (!ft_isalpha(arg[0]) && (arg[0] != '_')))
        return (1);
    while (arg[++i])
        if (arg[i] == '=')
            break;
        else if (arg[i] == '_' || ft_isalpha(arg[i]) || ft_isdigit(arg[i]))
            continue;
        else
            return (1);
    return (0);
}

void replace_elem_in_envp(char **src, char *name_variable, char *replace)
{
    int i;
    char *tmp_for_free;
    
    i = 0;
    while (src[i])
    {
        if (ft_strncmp(src[i], name_variable, ft_strlen(name_variable)) != 0)
            i++;
        else
        {
            tmp_for_free = src[i];
            src[i] = replace;
            free(tmp_for_free);
        }   
    }
}

char *get_name_var_from_arg(char *argument)
{
    int res_len;
    int i;
    char *name_var;

    i = 0;
    while (argument[i] != '=')
        i++;    
    name_var = malloc(sizeof(char) * (i + 2));
    i = 0;
    while (argument[i] != '=')
    {
        name_var[i] = argument[i];
        i++;
    }
    name_var[i] = argument[i];
    i++;
    name_var[i] = '\0';
    return (name_var);
}

int ft_export_with_args(t_data *data)
{
    int i;
    char *name_variable;

    i = 1;
    while (data->args[i])
    {
        if (valid_arg(data->args[i]))
        {
            ft_putstr_fd("minishell: export: `", 1);
            ft_putstr_fd(data->args[i], 1);
            ft_putstr_fd("': not a valid identifier\n", 1);
            return (1);
        }
        if (ft_strchr(data->args[i], '=') != NULL)
        {
            name_variable = get_name_var_from_arg(data->args[i]);
            if (find_elem_in_arrayStr(data->envp, name_variable, 1))
                replace_elem_in_envp(data->envp, name_variable, data->args[i]);
            else
                add_elem_in_arrayStr(data->envp, data->args[i]);
            free(name_variable);
        }
        else
            if (find_elem_in_arrayStr(data->envp, data->args[i], 0))
                add_elem_in_arrayStr(data->envp, data->args[i]);
        i++;
    }
    return (0);
}

int ft_export(t_data *data)//t_data *data)
{
    char **sorted_envp;
    
    if (!data->args[1])
    {
        sorted_envp = ft_strdup_2arr(data->envp);//data->envp);
        InsertionSort(sorted_envp, get_amount_line(sorted_envp));
        ft_print_args(sorted_envp);
        ft_free_array(&sorted_envp);
    }
    else 
        return (ft_export_with_args(data));       
    return (0);
}