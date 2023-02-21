/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:08:35 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/19 22:56:05 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	arguments_norme(t_pa *pars2, t_arrcmd *cmd, int i);
static int	arguments(t_arrcmd *cmd, t_pa *pars2, int i);
static int	set_exec_norme(void);
int			set_exec(void);

static int	arguments_norme(t_pa *pars2, t_arrcmd *cmd, int i)
{
	set_c(2);
	if (cmd == NULL)
		return (1);
	pars2[i].n_redirec = cmd->redir;
	pars2[i].tokens_size = cmd->t_size - (pars2[i].n_redirec * 2) - 1;
	pars2[i].redirec = calloc_minishell(cmd->redir + 1, sizeof(t_redirection));
	if (pars2[i].tokens_size > 0)
		pars2[i].tokens = calloc_minishell(pars2[i].tokens_size + 1, \
			sizeof(char *));
	if (cmd->t_size - 1 == cmd->redir * 2)
		pars2[i].tokens = NULL;
	return (0);
}

/*
we set the arguments in the pars2 struct. we set the number of redirections,
the size of the tokens array and the tokens array itself.
*/
static int	arguments(t_arrcmd *cmd, t_pa *pars2, int i)
{
	if (arguments_norme(pars2, cmd, i))
		return (1);
	while (g_gm.c->ii < cmd->t_size - 1 && (cmd->tokens[g_gm.c->ii]->type \
		!= _EOF || cmd->tokens[g_gm.c->ii]->type != PIPEE))
	{
		if (cmd->tokens[g_gm.c->ii]->type == STRINGG)
			pars2[i].tokens[g_gm.c->kk++] = \
				ft_strdup(cmd->tokens[g_gm.c->ii++]->token);
		else
		{
			if (redirect_tt(cmd->tokens[++(g_gm.c->ii) - 1]->type) \
				&& g_gm.c->ii >= 1 && g_gm.c->xx < cmd->redir)
			{
				pars2[i].redirec[g_gm.c->xx].type = \
					cmd->tokens[g_gm.c->ii - 1]->type;
				pars2[i].redirec[g_gm.c->xx].quoted = \
					cmd->tokens[g_gm.c->ii]->quoted;
				pars2[i].redirec[g_gm.c->xx++].file = \
					ft_strdup(cmd->tokens[g_gm.c->ii++]->token);
			}
		}
	}
	if (g_gm.c->kk != 0)
		pars2[i].tokens[g_gm.c->kk] = NULL;
	return (0);
}

/*
we initialize the array of commands
and then we loop through the array of commands and initialize each command
*/
static int	set_exec_norme(void)
{
	g_gm.pars2[g_gm.c->jj].redirec = NULL;
	g_gm.pars2[g_gm.c->jj].n_redirec = 0;
	g_gm.pars2[g_gm.c->jj].tokens = NULL;
	g_gm.pars2[g_gm.c->jj].tokens_size = 0;
	if (arguments(g_gm.arrcmd->value[g_gm.c->i], g_gm.pars2, g_gm.c->jj))
	{
		print_nl("syntax error: unexpected end of pipe", NULL);
		g_gm.status = 258;
		free_cmd(g_gm.arrcmd, 0);
		g_gm.arrcmd = NULL;
		return (1);
	}
	return (0);
}

/*
first we allocate memory for the array of commands
then we loop through the array of commands and allocate memory for each command
then we loop through the tokens of each command and allocate memory for each token
then we loop through the tokens of each command and allocate memory for each redirection
*/
int	set_exec(void)
{
	g_gm.pars2 = calloc_minishell(g_gm.arrcmd->p_size + 1, sizeof(t_pa));
	set_c(1);
	if (g_gm.arrcmd->p_type == PIPEE_S)
	{
		while (++(g_gm.c->i) < g_gm.arrcmd->p_size && \
			g_gm.c->jj < g_gm.arrcmd->p_size)
		{
			if (set_exec_norme())
				return (0);
			if (g_gm.arrcmd->p_size >= 2 && g_gm.c->i < g_gm.arrcmd->p_size - 1)
				g_gm.pars2[g_gm.c->jj].type = PIPEE;
			else
				g_gm.pars2[g_gm.c->jj].type = _EOF;
			g_gm.c->jj++;
		}
		while (++(g_gm.c->k) < g_gm.c->jj)
			g_gm.pars2[g_gm.c->k].n_cmds = g_gm.c->jj;
	}
	free_cmd(g_gm.arrcmd, 0);
	g_gm.arrcmd = NULL;
	return (1);
}
