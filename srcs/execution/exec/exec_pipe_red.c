/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:18:32 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/13 19:10:45 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	norm_cer(t_exec *exec, int last_cmd, t_exec *e);
static void	child_exec_redir(t_pa *pars2, t_exec *exec, int cmd, t_exec *e);
void		execute_pipe_redir(void);

static void	norm_cer(t_exec *exec, int last_cmd, t_exec *e)
{
	if (g_gm.c->ii > 0)
	{
		if (dup2(e->fd_pipe[g_gm.c->ii - 1][0], STDIN_FILENO) < 0)
			dup2_pipe_fail(exec, e);
		close(e->fd_pipe[g_gm.c->ii - 1][0]);
	}
	if (last_cmd == 0)
	{
		if (dup2(e->fd_pipe[g_gm.c->ii][1], STDOUT_FILENO) < 0)
			dup2_pipe_fail(exec, e);
		close(e->fd_pipe[g_gm.c->ii][1]);
	}
	if (exec->fd_in && exec->error == 0)
	{
		if (dup2(exec->fd_in, 0) < 0)
			dup2_pipe_fail(exec, e);
		close(exec->fd_in);
	}
	if (exec->fd_out && exec->error == 0)
	{
		if (dup2(exec->fd_out, 1) < 0)
			dup2_pipe_fail(exec, e);
		close(exec->fd_in);
	}
	close_pipes(e->fd_pipe, g_gm.pars2->n_cmds - 1);
}

static void	child_exec_redir(t_pa *pars2, t_exec *exec, \
	int last_cmd, t_exec *e)
{
	norm_cer(exec, last_cmd, e);
	if (exec->error == 0 && pars2->tokens && check_builtin(pars2->tokens))
	{
		exec_builtin(exec, pars2->tokens);
		free_the_child(NULL);
		close (1);
		close (2);
		exit(g_gm.status);
	}
	else if (exec->error == 0 && pars2->tokens)
	{
		g_gm.status = single_command_pipe(pars2, exec);
		exit(g_gm.status);
	}
	else
		return (free_the_child(NULL), exit(g_gm.status));
}

void	execute_pipe_redir(void)
{
	pid_t	pid;

	set_c(2);
	g_gm.status = 0;
	while (g_gm.c->xx < g_gm.pars2->n_cmds)
		init_exec(&g_gm.exec[g_gm.c->xx++]);
	allocate_pipe(g_gm.pars2, g_gm.exec);
	set_redir_pipe(g_gm.pars2, g_gm.exec);
	piping(g_gm.exec->fd_pipe, g_gm.pars2->n_cmds);
	while (g_gm.c->kk < g_gm.pars2->n_cmds && g_gm.error_pipe)
	{
		g_gm.pid = 0;
		pid = fork_cmd_pipe();
		g_gm.fd_closed = 0;
		if (pid == 0)
			child_exec_redir(&(g_gm.pars2[g_gm.c->kk]), \
				&(g_gm.exec[g_gm.c->kk]), \
				(g_gm.c->kk + 1 == g_gm.pars2->n_cmds), g_gm.exec);
		g_gm.fd_closed = 3;
		g_gm.c->ii++;
		g_gm.c->kk++;
	}
	close_pipes(g_gm.exec->fd_pipe, g_gm.pars2->n_cmds - 1);
}
