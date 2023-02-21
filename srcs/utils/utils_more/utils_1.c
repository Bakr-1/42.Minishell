/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 10:22:10 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/13 21:40:15 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen2d(char **str);
char	**ft_strdoubledub(char **env);
void	_read(t_parse *parse);
void	rwhitespaces(t_parse *parse);
char	*epur_str(char *str);

size_t	ft_strlen2d(char **str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	**ft_strdoubledub(char **env)
{
	int		i;
	char	**env_dup;

	i = -1;
	env_dup = calloc_minishell((ft_strlen2d(env) + 1), sizeof(char *));
	while (env[++i])
		env_dup[i] = ft_strdup(env[i]);
	env_dup[i] = NULL;
	return (env_dup);
}

void	_read(t_parse *parse)
{
	if (!parse->s_r || !parse)
		return ;
	if (parse->read >= parse->size_read)
		parse->c_char = EOF;
	else
		parse->c_char = parse->s_r[parse->read];
	parse->index = parse->read;
	parse->read += 1;
}

void	rwhitespaces(t_parse *parse)
{
	if (!parse->s_r || !parse)
		return ;
	while (parse->read <= parse->size_read && ft_isspace(parse->c_char))
	{
		if (!parse->s_r || !parse)
			return ;
		if (parse->read >= parse->size_read)
			parse->c_char = EOF;
		else
			parse->c_char = parse->s_r[parse->read];
		parse->index = parse->read;
		parse->read += 1;
	}
	parse->quoted = 0;
}

char	*epur_str(char *str)
{
	int		i;
	int		j;
	char	*result;
	int		sp;

	i = 0;
	j = 0;
	sp = -1;
	result = calloc_minishell(sizeof(char), (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
		{
			if (sp == 1)
				result[j++] = ' ';
			sp = 0;
			result[j++] = str[i];
		}
		else if (sp == 0)
			sp = 1;
		i++;
	}
	result[j] = '\0';
	return (free(str), result);
}
