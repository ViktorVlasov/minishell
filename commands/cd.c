/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 17:42:37 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/12 20:02:52 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void change_oldpwd(t_data *data, char *old_pwd)
{   
	char *tmp;
	 
	if (find_elem_in_arrayStr(data->envp, "OLDPWD=", 1))
		data->envp = delete_elem_in_arrayStr(data->envp, "OLDPWD=", 1);
	tmp = old_pwd;
	old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	data->envp = add_elem_in_arrayStr(data->envp, old_pwd);
	free(tmp);
	free(old_pwd);
}

void change_pwd(t_data *data)
{
	char *pwd;
	char *tmp;

	pwd = getcwd(NULL, 0);
	if (find_elem_in_arrayStr(data->envp, "PWD=", 1))
		data->envp = delete_elem_in_arrayStr(data->envp, "PWD=", 1);
	tmp = pwd;
	pwd = ft_strjoin("PWD=", pwd);
	data->envp = add_elem_in_arrayStr(data->envp, pwd);
	free(pwd);
	free(tmp);
}

static int		path_error(char *path)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	return (errno);
}

int without_arguments_handler(t_data *data, char *old_pwd)
{
	char *home_path;

	home_path = get_value_from_var(data->envp, "HOME=");
	if (!home_path)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	if (ft_strlen(home_path) == 0)
		change_oldpwd(data, old_pwd);
	else if (chdir(home_path) == 0)
	{
		change_oldpwd(data, old_pwd);
		change_pwd(data);  
	}
	else
		path_error(home_path);
	return (0);
}

int minus_handler(t_data *data, char *current_pwd)
{
	char *value_of_old_pwd;

	value_of_old_pwd = get_value_from_var(data->envp, "OLDPWD=");
	if (!value_of_old_pwd)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (1);
	}
	if (ft_strlen(value_of_old_pwd) == 0)
	{
		ft_putchar_fd('\n', 1);
		change_oldpwd(data, value_of_old_pwd);
	}
	else if (chdir(value_of_old_pwd) == 0)
	{
		ft_putstr_fd(value_of_old_pwd, 1);
		ft_putstr_fd("\n", 1);
		change_oldpwd(data, current_pwd);
		change_pwd(data);
	}
	else
		path_error(value_of_old_pwd);
	return (0);
}

int ft_cd(t_data *data)
{
	char *current_pwd;
	char *home;

	current_pwd = getcwd(NULL, 0);
	if (!data->args[1])
	{
		without_arguments_handler(data, current_pwd);
	}
	if (ft_strcmp(data->args[1], "-\0"))
		return minus_handler(data, current_pwd);
	else
	{
		if (chdir(data->args[1]) == 0)
		{
			change_oldpwd(data, current_pwd);
			change_pwd(data);
		}
		else
			return (path_error(data->args[1]));
		return (0);
	}
}