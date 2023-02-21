/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mealjnei <mealjnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:27:21 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/12 18:16:55 by mealjnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		env_check(char c);
char	*return_type(int i);
int		check_type(int c);

int	env_check(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (0);
	return (1);
}

char	*return_type(int i)
{
	if (i == 1)
		return (ft_strdup("|"));
	else if (i == 2)
		return (ft_strdup(">"));
	else if (i == 3)
		return (ft_strdup(">>"));
	else if (i == 4)
		return (ft_strdup("<"));
	else if (i == 5)
		return (ft_strdup("<<"));
	else if (i == 6)
		return (ft_strdup("EOF"));
	else if (i == 8)
		return (ft_strdup("input"));
	else
		return (NULL);
}

int	check_type(int c)
{
	if (c != PIPE && c != GREAT && c != LESS && c != EOF)
		return (1);
	return (0);
}
