/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:27:27 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/15 00:19:21 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_parse(void);
t_co	*init_cc(t_co *c);
void	init_global(char **env);
void	init_cv(t_arrcmd *cmd, int i);
int		redirect_tt(int i);

void	init_parse(void)
{
	g_gm.error = 0;
	g_gm.parse->s_r = ft_strdup(g_gm.s_r);
	g_gm.parse->size_read = ft_strlen(g_gm.s_r);
	free(g_gm.s_r);
	g_gm.s_r = NULL;
	g_gm.parse->c_char = 32;
	g_gm.parse->index = 0;
	g_gm.parse->read = 0;
	g_gm.parse->next_token = NULL;
	g_gm.parse->prev_token = NULL;
}

t_co	*init_cc(t_co *c)
{
	c->i = -1;
	c->j = -1;
	c->k = -1;
	c->x = -1;
	c->g = -1;
	c->y = -1;
	c->z = -1;
	c->ii = 0;
	c->jj = 0;
	c->kk = 0;
	c->xx = 0;
	c->gg = 0;
	c->yy = 0;
	c->zz = 0;
	return (c);
}

void	init_global(char **env)
{
	g_gm.env = NULL;
	g_gm.env_v2 = NULL;
	g_gm.env = ft_strdoubledub(env);
	g_gm.env_v2 = ft_strdoubledub(env);
	g_gm.prompt = NULL;
	g_gm.status = 0;
	g_gm.n_pipes = 0;
	g_gm.pid = 1;
	g_gm.s_r = NULL;
	g_gm.c = calloc_minishell(1, sizeof(t_co));
	g_gm.parse = NULL;
	g_gm.pars2 = NULL;
	g_gm.exec = NULL;
	g_gm.arrcmd = NULL;
	g_gm.h_doc = NULL;
}

void	init_cv(t_arrcmd *cmd, int i)
{
	cmd->p_type = i;
	cmd->p_size = 1;
	cmd->value = NULL;
	cmd->tokens = NULL;
	cmd->t_size = 0;
	cmd->redir = 0;
}

int	redirect_tt(int i)
{
	if (i == GREATT || i == GREATERR || i == LESSS || i == HERE_DOCC)
		return (1);
	return (0);
}
