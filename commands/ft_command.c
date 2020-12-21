/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 19:43:21 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/21 19:29:39 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void error_message_rel_path(t_data *vars, int f_no_dir_and_exist, \
							int f_have_rights)
{
	if (f_no_dir_and_exist == 0)
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(vars->args[0], 1);
		ft_putstr_fd(": command not found\n", 1);
	}
	else if (f_have_rights == 0)
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(vars->args[0], 1);
		ft_putstr_fd(": Permission denied\n", 1);
	}
}

char *check_relative_main(t_data *vars, char *path_part, \
							int *f_no_dir_and_exist, int *f_have_rights)
{
	char *check_path;
	struct stat buf;
	char *path_copy;

	path_copy = ft_strdup(path_part);
	check_path = NULL;
	path_copy = add_char(path_copy, '/');
	check_path = ft_strjoin(path_copy, vars->args[0]);
	if (!((stat(check_path, &buf) == -1) || (buf.st_mode & S_IFDIR)))
	{
		*f_no_dir_and_exist = 1;
		if ((buf.st_mode & S_IXUSR))
		{
			*f_have_rights = 1;
			return (check_path);
		}
	}
	free(check_path);
	free(path_copy);
	check_path = NULL;
	return (NULL); 
}

char *check_relative(t_data *vars)
{
	char **path;
	int i;
	char *check_path;
	int f_no_dir_and_exist;
	int f_have_rights;

	f_have_rights = 0;
	f_no_dir_and_exist = 0;
	path = ft_split(get_value_from_var(vars->envp, "PATH="), ':');
	i = 0;
	while (path && path[i])
	{
		if ((check_path = check_relative_main(vars, path[i], &f_no_dir_and_exist, &f_have_rights)) != NULL)
		{
			ft_free_array(&path);
			return (check_path);
		} 
		i++;
	}
	error_message_rel_path(vars, f_no_dir_and_exist, f_have_rights);
	if (path)
		ft_free_array(&path);
	return (NULL);
}

int check_absolute(t_data *vars)
{
	struct stat buf;
	
	if (stat(vars->args[0], &buf) == -1)
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(vars->args[0], 1);
		ft_putstr_fd(": No such file or directory\n", 1);
		return (1);
	}
	if (buf.st_mode & S_IFDIR)
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(vars->args[0], 1);
		ft_putstr_fd(": is a directory\n", 1);
		return (1);
	}
	if (!(buf.st_mode & S_IXUSR))
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(vars->args[0], 1);
		ft_putstr_fd(": Permission denied\n", 1);
		return (1);
	}
	return 0;
}

int check_commands(t_data *vars)
{
	char *relative_path;
	
	if (ft_strchr(vars->args[0], '/') != NULL)
	{
		if (check_absolute(vars))
			return (1);
		else
			return (0);
	}
	if ((relative_path = check_relative(vars)))
	{
		free(vars->args[0]);
		vars->args[0] = relative_path; 
	}
	else
		return (1);
	return (0);
}

int         ft_command(t_data *vars)
{
	pid_t	pid;
	int		status;	

	status = 0;
	// check_commands(vars);
	if ((pid = fork()) < 0)
		perror(NULL); // не форкнул
	else if (pid == 0)
	{
		if (!check_commands(vars))
			execve(vars->args[0], vars->args, vars->envp);
		exit(1);
	}
	wait(&status);
	if (WIFEXITED(status) != 0)
		status = WEXITSTATUS(status);
	return (status);
}