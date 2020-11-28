/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:48:08 by ddraco            #+#    #+#             */
/*   Updated: 2020/11/28 22:25:59 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_realloc(void *ptr, size_t newsize)
{
	char	*newptr;
	size_t	cursize;

	if (ptr == 0)
		return (malloc(newsize));
	cursize = sizeof(ptr);
	if (newsize <= cursize)
		return (ptr);
	newptr = malloc(newsize);
	ft_memcpy(ptr, newptr, cursize);
	free(ptr);
	return (newptr);
}

int		get_amount_line(char **lines)
{
	int i;

	i = 0;
	if (!lines || !(*lines))
		return (0);
	while (lines[i])
		i++;
	return (i);
}

char        **parser(char *line, t_data vars)
{
    char    **parsed_by_semicolon;
    char    **parsed_args;
    char    *spec_symbols = " $'\"";
    int     i;
    int     j;

    i = 0;

    parsed_by_semicolon = semicolon(line);
    // parsed_args = (char**)malloc(get_amount_line(line) * sizeof(char*));
    // while (i < argc)
    // {
    //     j = 0;
    //     while (j < ft_strlen(argv[i]))
    //     {
    //         if (ft_strchr(spec_symbols, argv[i][j]) == NULL)
    //             just_add();
    //         else if (ft_strchr(spec_symbols, argv[i][j]) == '\'')
    //             one_comma_worker();
    //         else if (ft_strchr(spec_symbols, argv[i][j]) == '\"')
    //             two_comma_worker();
    //         j++;
    //     }
    //     i++;
    // }
        
}