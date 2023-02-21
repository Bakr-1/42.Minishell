/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe_red_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:08:21 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/11 21:00:15 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_in(t_pa *pars2, t_exec *exec, int i);
static void	set_out(t_pa *pars2, t_exec *exec, int i);
void		set_redir_pipe(t_pa *pars2, t_exec *exec);

static void	set_in(t_pa *pars2, t_exec *exec, int i)
{
	int	fd;

	fd = open(pars2->redirec[i].file, O_RDONLY);
	if (fd < 0)
		return (failed_open(exec, pars2->redirec[i].file));
	exec->fd_in = fd;
}

static void	set_out(t_pa *pars2, t_exec *exec, int i)
{
	int	fd;

	fd = 0;
	if (pars2->redirec[i].type == GREATT)
	{
		fd = open(pars2->redirec[i].file, \
			O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
		if (fd < 0)
			return (failed_open(exec, pars2->redirec[i].file));
	}
	else if (pars2->redirec[i].type == GREATERR)
	{
		fd = open(pars2->redirec[i].file, \
			O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
		if (fd < 0)
			return (failed_open(exec, pars2->redirec[i].file));
	}
	exec->fd_out = fd;
}

void	set_redir_pipe(t_pa *pars2, t_exec *exec)
{
	int	i;
	int	j;

	i = 0;
	while (i < pars2->n_cmds)
	{
		j = 0;
		here_doc_exec(&pars2[i], &exec[i]);
		while (j < pars2[i].n_redirec)
		{
			if (pars2[i].redirec[j].type == LESSS)
				set_in(&pars2[i], &exec[i], j);
			if (!exec->error && (pars2[i].redirec[j].type == GREATERR \
				|| pars2[i].redirec[j].type == GREATT))
				set_out(&pars2[i], &exec[i], j);
			j++;
		}
		i++;
	}
}
