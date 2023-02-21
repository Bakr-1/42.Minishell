/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 10:35:25 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/10 22:33:12 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_arrcmd	*parse_more(void);
static int		init_cmd(t_arrcmd *cmd);
static t_arrcmd	*parse2(void);
static void		parse_next_norme(void);
int				parse_next(void);

static t_arrcmd	*parse_more(void)
{
	t_arrcmd	*cmd;

	cmd = calloc_minishell(1, sizeof(t_arrcmd));
	init_cv(cmd, TOK_S);
	cmd->tokens = calloc_minishell(2, sizeof(t_token *));
	cmd->tokens[0] = g_gm.parse->next_token;
	cmd->tokens[1] = NULL;
	if (!cmd->t_size)
	{
		if (g_gm.parse->next_token->type == PIPEE)
		{
			print_nl("syntax error 2", g_gm.parse->next_token->token);
			g_gm.status = 258;
			free_parse3(g_gm.parse);
			free_cmd(cmd, 0);
			return (NULL);
		}
		cmd->t_size++;
	}
	return (cmd);
}

static int	init_cmd(t_arrcmd *cmd)
{
	cmd->t_size++;
	if (cmd->p_type == 2)
		cmd->tokens = token_realloc(cmd, cmd->t_size);
	else
		cmd->tokens = NULL;
	g_gm.parse->prev_token = g_gm.parse->next_token;
	g_gm.parse->next_token = token_next();
	cmd->tokens[cmd->t_size - 1] = verify_token(g_gm.parse, cmd);
	if (!cmd->tokens[cmd->t_size - 1])
		return (1);
	return (0);
}

/*

*/
static t_arrcmd	*parse2(void)
{
	t_arrcmd	*cmd;

	cmd = parse_more();
	if (!cmd)
		return (NULL);
	while (g_gm.parse->next_token->type != _EOF)
	{
		if (init_cmd(cmd))
			return (free_cmd(cmd, 0));
		if (cmd->tokens[cmd->t_size - 1]->type == PIPEE)
		{
			g_gm.parse->prev_token = g_gm.parse->next_token;
			g_gm.parse->next_token = token_next();
			break ;
		}
		if (cmd->tokens[cmd->t_size - 1]->type == _EOF)
			break ;
	}
	if (abnormal_case(g_gm.parse))
	{
		if (cmd)
			free_cmd(cmd, 0);
		return (NULL);
	}
	return (cmd);
}

/*
this function will be called when there is a pipe in the command line
we will re allocate the array of commands and add the new command
*/
static void	parse_next_norme(void)
{
	if (g_gm.parse->prev_token->type == PIPEE)
	{
		g_gm.arrcmd->p_size++;
		if (g_gm.arrcmd->p_type == PIPEE_S)
			g_gm.arrcmd->value = cmd_realloc1(g_gm.arrcmd, \
				g_gm.arrcmd->p_size + 1);
		else
			g_gm.arrcmd->value = NULL;
	}
}

/*
in this function we will keep parsing to the next pipe or redirection
*/
int	parse_next(void)
{
	g_gm.arrcmd = calloc_minishell(1, sizeof(t_arrcmd));
	init_cv(g_gm.arrcmd, PIPEE_S);
	g_gm.arrcmd->value = calloc_minishell(2, sizeof(t_arrcmd *));
	g_gm.arrcmd->p_size = 1;
	g_gm.arrcmd->value[g_gm.arrcmd->p_size] = NULL;
	while (g_gm.parse->next_token->type != _EOF)
	{
		g_gm.arrcmd->value[g_gm.arrcmd->p_size - 1] = parse2();
		if (g_gm.arrcmd->value[g_gm.arrcmd->p_size - 1] == NULL)
		{
			free_parse2(g_gm.parse);
			free_cmd(g_gm.arrcmd, 0);
			return (0);
		}
		parse_next_norme();
	}
	free_parse1(g_gm.parse);
	return (1);
}
