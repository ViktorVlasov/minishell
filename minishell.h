/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:45:02 by ddraco            #+#    #+#             */
/*   Updated: 2020/11/28 21:52:43 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define BUFFER_SIZE 5
# include "libft/libft.h"

char        **parser(char *line, t_data vars);
int			get_next_line(int fd, char **line);
char        **semicolon(char *line);

typedef struct      s_data
{
    char            **envp;
}                   t_data;

/* 
* Commands
*/

void        ft_echo(char **args);
void        ft_pwd();
void ft_env(char **envp);

#endif