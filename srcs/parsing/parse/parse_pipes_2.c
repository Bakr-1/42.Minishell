/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 10:39:56 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/13 15:13:48 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token		**token_realloc(t_arrcmd *cmd, int i);
t_arrcmd	**cmd_realloc1(t_arrcmd *cmd, int i);
char		*quoted_(char *str, int *i, t_parse *parse);
static char	*get_limiter(t_parse *parse);
t_token		*verify_token(t_parse *parse, t_arrcmd *cmd);

t_token	**token_realloc(t_arrcmd *cmd, int i)
{
	t_token	**token;
	int		x;

	x = 0;
	token = calloc_minishell(i + 1, sizeof(t_token *));
	while (x < i - 1)
	{
		token[x] = cmd->tokens[x];
		x++;
	}
	token[x] = NULL;
	free(cmd->tokens);
	cmd->tokens = NULL;
	return (token);
}

t_arrcmd	**cmd_realloc1(t_arrcmd *cmd, int i)
{
	t_arrcmd	**cmd1;
	int			x;

	x = 0;
	cmd1 = calloc_minishell(i, sizeof(t_arrcmd *));
	while (x < i - 1)
	{
		cmd1[x] = cmd->value[x];
		x++;
	}
	cmd1[x] = NULL;
	free(cmd->value);
	cmd->value = NULL;
	return (cmd1);
}

char	*quoted_(char *str, int *i, t_parse *parse)
{
	char	*temp;
	int		x;

	temp = NULL;
	x = *i;
	while (str[*i] != ' ' && str[*i] != '<')
		(*i)--;
	if (str[*i + 1] == DQUOTE || str[*i + 1] == SQUOTE)
		*i += 2;
	if (str[*i] == DOLLAR)
	{
		while (str[*i] && (*i < x) && (str[*i] != DQUOTE || str[*i] != SQUOTE))
		{
			temp = ft_scjoin(temp, str[*i]);
			(*i)++;
		}
	}
	else
		temp = ft_strdup(parse->next_token->token);
	return (temp);
}

static char	*get_limiter(t_parse *parse)
{
	int		i;
	char	*limiter;
	char	*tmp;

	i = parse->index - 1;
	limiter = ft_strdup(parse->s_r);
	if (!parse->next_token->quoted)
	{
		while (limiter[i] != ' ' && limiter[i] != '<')
			i--;
		i++;
		tmp = ft_substr(limiter, i, parse->index - i);
	}
	else
		tmp = quoted_(limiter, &i, parse);
	free(limiter);
	return (tmp);
}

t_token	*verify_token(t_parse *parse, t_arrcmd *cmd)
{
	char	*free_tmp;

	if (parse->next_token->type == INPUTT_ER)
		return (NULL);
	if (abnormal_case(parse))
		return (NULL);
	if (redirect_tt(parse->prev_token->type))
	{
		if (parse->next_token->type != STRINGG)
		{
			print_nl("syntax error near unexpected token ", \
				parse->next_token->token);
			g_gm.status = 258;
			return (NULL);
		}
		cmd->redir++;
		if (parse->prev_token->type == HERE_DOCC)
		{
			free_tmp = parse->next_token->token;
			parse->next_token->token = get_limiter(parse);
			free(free_tmp);
		}
	}
	return (parse->next_token);
}
