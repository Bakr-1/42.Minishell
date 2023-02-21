/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:08:51 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/15 13:22:48 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*token_back2(char *str, t_parse *parse, int i, int j);
char			*token_str(t_parse *parse, char *str);
static char		*token_quoted_string(t_parse *parse, char *str, int i, \
					char type);
static char		*qoute_first(t_parse *parse, char *str, char *str2);
t_token			*create_token_str(t_parse *parse);

static t_token	*token_back2(char *str, t_parse *parse, int i, int j)
{
	t_token	*token;

	if (i == _EOF)
	{
		free(parse->s_r);
		parse->s_r = NULL;
	}
	token = calloc_minishell(1, sizeof(t_token));
	if (j)
	{
		if (str)
			token->token = ft_strdup(str);
		else
			token->token = NULL;
	}
	else
		token->token = NULL;
	free(str);
	token->type = i;
	token->quoted = parse->quoted;
	return (token);
}

char	*token_str(t_parse *parse, char *str)
{
	char	*temp;

	temp = ft_strdup(str);
	while (parse->c_char != EOF && !ft_strchr(METAA, parse->c_char))
	{
		while (parse->c_char == SPACE && parse->c_char != EOF)
			_read(parse);
		if (parse->c_char == DOLLAR)
			temp = ft_strjoin_gnl_extra(temp, token_env(parse));
		else if (parse->c_char == EOF)
			return (temp);
		else
		{
			temp = ft_scjoin(temp, parse->c_char);
			_read(parse);
		}
	}
	return (temp);
}

static char	*token_quoted_string(t_parse *parse, char *str, int i, char type)
{
	_read(parse);
	str = ft_strdup("");
	while (parse->c_char != type && parse->c_char != EOF)
	{
		if (parse->c_char == DOLLAR && i)
			str = ft_strjoin_gnl_extra(str, token_env(parse));
		else
		{
			str = ft_scjoin(str, parse->c_char);
			_read(parse);
		}
	}
	if (check_lines(parse, type))
	{
		free(str);
		return (NULL);
	}
	parse->quoted = 1;
	_read(parse);
	return (str);
}

static char	*qoute_first(t_parse *parse, char *str, char *str2)
{
	if (parse->c_char == 34)
		str2 = token_quoted_string(parse, NULL, 1, DQUOTE);
	else if (parse->c_char == 39)
		str2 = token_quoted_string(parse, NULL, 0, SQUOTE);
	if (!str && !str2)
		g_gm.status = 127;
	return (str2);
}

t_token	*create_token_str(t_parse *parse)
{
	char	*str;
	char	*str1;
	char	*str2;

	str = ft_strdup("");
	while (parse->index <= parse->size_read && check_type(parse->c_char))
	{
		str1 = ft_strdup("");
		str2 = str1;
		if (parse->c_char == DQUOTE || parse->c_char == SQUOTE)
			str1 = qoute_first(parse, str, NULL);
		else
			str1 = token_str(parse, str1);
		if (!str1 && parse->one_line)
		{
			free(str2);
			return (token_back2(str, parse, INPUTT_ER, 0));
		}
		str = ft_strjoin_gnl_extra(str, str1);
		free(str2);
		if (parse->c_char == ' ')
			return (token_back2(str, parse, STRINGG, 1));
	}
	return (token_back2(str, parse, STRINGG, 1));
}
