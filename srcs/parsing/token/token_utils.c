/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:08:48 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/13 21:39:29 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*invalied_string(t_parse *parse);
static char	*invalied_string2(t_parse *parse);
char		*token_env(t_parse *parse);
int			check_lines(t_parse *parse, char c);
char		*str_var(t_parse *parse);

static char	*invalied_string(t_parse *parse)
{
	char	*str;

	str = ft_strdup("a");
	str[0] = parse->c_char;
	_read(parse);
	return (str);
}

static char	*invalied_string2(t_parse *parse)
{
	char	*str;
	char	*temp;

	if (parse->c_char == '0')
		temp = ft_strdup("newline");
	else if (parse->c_char == '?')
		temp = ft_itoa(g_gm.status);
	else
		return (str_var(parse));
	_read(parse);
	str = token_str(parse, temp);
	free(temp);
	return (str);
}

char	*token_env(t_parse *parse)
{
	char	*str;
	char	*env;

	str = NULL;
	if (!parse)
		return (NULL);
	if (parse->s_r[parse->read] == '$' || parse->s_r[parse->read] == \
		'\'' || parse->s_r[parse->read] == '\"' || \
		parse->s_r[parse->read] == (char)EOF || !parse->s_r[parse->read])
		return (invalied_string(parse));
	_read(parse);
	if (ft_isdigit(parse->c_char) || parse->c_char == '?' || \
		env_check(parse->c_char))
		return (invalied_string2(parse));
	while (!env_check(parse->c_char) && parse->c_char != EOF)
	{
		str = ft_scjoin(str, parse->c_char);
		_read(parse);
	}
	env = find_in_env(g_gm.env, str, 1);
	free(str);
	if (!env)
		return (NULL);
	return (epur_str(env));
}

int	check_lines(t_parse *parse, char c)
{
	if (parse->c_char == EOF)
	{
		if (c == DQUOTE)
			print_nl("syntax error \"\n", NULL);
		else
			print_nl("syntax error \"\n", NULL);
		g_gm.status = 258;
		parse->one_line = true;
		return (1);
	}
	return (0);
}

char	*str_var(t_parse *parse)
{
	char	*str;

	if (ft_isdigit(parse->c_char))
	{
		str = ft_strdup("");
		_read(parse);
		while (parse->c_char != EOF && !ft_strchr(METAAD, parse->c_char))
		{
			str = ft_scjoin(str, parse->c_char);
			_read(parse);
		}
	}
	else
	{
		str = ft_strdup("$");
		while (parse->c_char != EOF && !ft_strchr(METAAD, parse->c_char))
		{
			str = ft_scjoin(str, parse->c_char);
			_read(parse);
		}
	}
	return (str);
}
