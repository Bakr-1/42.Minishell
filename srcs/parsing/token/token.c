/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:08:53 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/15 01:29:54 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token			*ret_tok(t_parse *parse, int i);
t_token			*create_token(t_parse *parse, int i);
static t_token	*token_next_n(void);
t_token			*token_next(void);

t_token	*ret_tok(t_parse *parse, int i)
{
	t_token	*tok;

	if (i == GREATERR || i == HERE_DOCC)
		_read(parse);
	_read(parse);
	tok = calloc_minishell(1, sizeof(t_token));
	tok->token = return_type(i);
	tok->type = i;
	tok->quoted = parse->quoted;
	return (tok);
}

t_token	*create_token(t_parse *parse, int i)
{
	t_token	*tok;

	_read(parse);
	if (i == _EOF)
	{
		free(parse->s_r);
		parse->s_r = NULL;
	}
	tok = calloc_minishell(1, sizeof(t_token));
	tok->token = return_type(i);
	tok->type = i;
	tok->quoted = parse->quoted;
	return (tok);
}

static t_token	*token_next_n(void)
{
	if (g_gm.parse->c_char == PIPE)
		return (create_token(g_gm.parse, PIPEE));
	else if (g_gm.parse->c_char == GREAT)
	{
		if (g_gm.parse->s_r[g_gm.parse->read] == GREAT && \
			g_gm.parse->s_r[g_gm.parse->read])
			return (ret_tok(g_gm.parse, GREATERR));
		else
			return (create_token(g_gm.parse, GREATT));
	}
	else if (g_gm.parse->c_char == LESS)
	{
		if (g_gm.parse->s_r[g_gm.parse->read] == LESS && \
			g_gm.parse->s_r[g_gm.parse->read])
			return (ret_tok(g_gm.parse, HERE_DOCC));
		else
			return (create_token(g_gm.parse, LESSS));
	}
	else
		return (create_token_str(g_gm.parse));
}

/*
The next function is "token_next_n()" which is a helper function
for the main function "token_next()". It checks the current character
in "g_gm.parse->c_char", if it is a PIPE it calls the "create_token()"
function with PIPEE as the type, if it is a GREAT it checks if the next
character is also a GREAT, if it is it calls the "ret_tok()" function
with GREATERR as type, else it calls the "create_token()" function with
GREATT as type. If the current character is LESS, it checks if the next
character is also LESS and calls the "ret_tok()" function with HERE_DOCC
as type, else it calls the "create_token()" function with LESSS as type.
If the current character is none of the above,
it calls the "create_token_str()" function.

The "token_next()" function is the main function that iterates through
the input and calls "rwhitespaces()" which appears to skip any whitespaces
in the input. If the current character is not _EOF,
it calls the "token_next_n()" helper function and returns the resulting token.
If the current character is _EOF it calls the "create_token()"
function with _EOF as type and returns the resulting token
*/
t_token	*token_next(void)
{
	while (g_gm.parse->c_char != EOF && g_gm.parse->index <= \
		g_gm.parse->size_read)
	{
		rwhitespaces(g_gm.parse);
		if (g_gm.parse->c_char == EOF)
			break ;
		if (g_gm.parse->c_char != EOF)
			return (token_next_n());
	}
	return (create_token(g_gm.parse, _EOF));
}
