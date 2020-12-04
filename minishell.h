/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <ddraco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:45:02 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/04 19:19:03 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define BUFFER_SIZE 5
# include "libft/libft.h"

typedef struct      s_data
{
    char            **envp;
}                   t_data;

char        **parser(char *line, t_data vars);
int			get_next_line(int fd, char **line);
char        **semicolon(char *line);



/* 
* Commands
*/

void        ft_echo(char **args);
void        ft_pwd();
void ft_env(char **envp);

#endif