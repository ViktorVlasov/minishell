/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 19:43:21 by efumiko           #+#    #+#             */
/*   Updated: 2020/12/18 23:53:55 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *check_relative(t_data *vars)
{
    char **path;
    int i;
    char *check_path;
    struct stat buf;
    
    // ПЕРЕДЕЛАТЬ
    path = ft_split(get_value_from_var(vars->envp, "PATH="), ':');
    i = 0;
    while (path && path[i])
    {
        path[i] = add_char(path[i], '/');
        check_path = ft_strjoin(path[i], vars->args[0]);
        if ((stat(check_path, &buf) == -1) || (buf.st_mode & S_IFDIR))
        {
            ft_putstr_fd("minishell: ", 1);
	        ft_putstr_fd(vars->args[0], 1);
	        ft_putstr_fd(": command not found\n", 1);
        }
        if (!(buf.st_mode & S_IXUSR))
        {
            ft_putstr_fd("minishell: ", 1);
	        ft_putstr_fd(vars->args[0], 1);
	        ft_putstr_fd(": Permission denied\n", 1);
        }
        free(check_path);    
        i++;
    }
    if (path)
        ft_free_array(&path);
    return 0;
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
    
    if (ft_strchr(vars->args[0], '/') != NULL)
    {
        if (check_absolute(vars))
            return (1);
        else
            return (0);
        
    }
        
    if (check_relative(vars))
        return (1);
    
    
    return (0);
}







// int ft_command(t_data *vars)
// {
//     char *command;

//     command = vars->args[0];
    
//     pid_t	pid;
// 	int		status;

// 	status = 0;
// 	if ((pid = fork()) < 0)
// 		perror(NULL); // не форкнул
// 	else if (pid == 0)
// 	{
// 		//execve(cmd->cmd_dir, cmd->arg, all->env);
// 		check_relative();
//         check_absolute();
//         exit(1);
// 	}
// 	else
// 	{
// 	 	wait(&status);
// 	 	if (WIFEXITED(status) != 0)
//             status = WEXITSTATUS(status);
//         if (status == 1)
//             return (1);
//         return (0);
//     }
    
// }