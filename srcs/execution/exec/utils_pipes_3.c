/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 20:50:53 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/13 21:23:43 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		close_pipes(int **fd, int i);
void		free_pipes(int **fd, int i);
static void	exec_free_2(t_pa *pars2, t_exec *exec);
void		exec_free(t_pa *pars2, t_exec *exec);

void	close_pipes(int **fd, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (fd[j][0])
			close(fd[j][0]);
		if (fd[j][1])
			close(fd[j][1]);
		j++;
	}
}

void	free_pipes(int **fd, int i)
{
	int	j;

	j = 0;
	i--;
	while (j < i)
	{
		if (fd[j])
			free(fd[j]);
		fd[j] = NULL;
		j++;
	}
	free(fd);
	fd = NULL;
}

static void	exec_free_2(t_pa *pars2, t_exec *exec)
{
	int	i;

	i = pars2->n_cmds - 1;
	while (i >= 0)
	{
		if (exec[i].fd_pipe)
			free_pipes(exec[i].fd_pipe, pars2->n_cmds);
		i--;
	}
	free(exec);
	exec = NULL;
}

void	exec_free(t_pa *pars2, t_exec *exec)
{
	if (g_gm.pars2->n_cmds == 1)
	{
		free(g_gm.exec);
		g_gm.exec = NULL;
	}
	else if (g_gm.pars2->n_cmds > 1)
		exec_free_2(pars2, exec);
}
