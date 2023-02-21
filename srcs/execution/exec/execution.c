/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:27:17 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/19 22:56:30 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		init_exec(t_exec *exec);
static int	check_redir(void);
static void	multi_cmd(void);
int			executing(void);

void	init_exec(t_exec *exec)
{
	g_gm.error_pipe = 1;
	g_gm.error = 0;
	g_gm.pid = 1;
	exec->saved_out = 1;
	exec->saved_in = 0;
	exec->fd_in = 0;
	exec->fd_out = 0;
	exec->here_doc = 0;
	exec->file = NULL;
	exec->fd_pipe = NULL;
	exec->error = 0;
}

/*
the check_redir function is called in the multi_cmd function to check if there
are redirections in the command. if there are redirections we return 1 else we
return 0.
*/
static int	check_redir(void)
{
	int	i;

	i = -1;
	while (++i < g_gm.pars2->n_cmds)
		if (g_gm.pars2[i].n_redirec != 0)
			return (1);
	return (0);
}

/*
the multi_cmd function is called when we have a multi command. we check if
there are redirections in the command if not we go into the execute_pipe
function. if there are redirections we go into the execute_pipe_redir function
*/
static void	multi_cmd(void)
{
	if (check_redir() == 0)
		return (execute_pipe(-1));
	else
	{
		execute_pipe_redir();
		g_gm.pid = 1;
		my_wait();
	}
}

/*
in the execution function, we check if the command is a single command or a
single command with redirections or a multi command. and then we call the
exec_free function to free the allocated memory of g_gm.exec.
*/
int	executing(void)
{
	g_gm.exec = calloc_minishell(g_gm.pars2->n_cmds, sizeof(t_exec));
	if (g_gm.pars2->type == _EOF && g_gm.pars2->n_redirec == 0)
		single_command();
	else if (g_gm.pars2->type == _EOF && g_gm.pars2->n_redirec > 0)
		single_command_red();
	else
		multi_cmd();
	exec_free(g_gm.pars2, g_gm.exec);
	return (1);
}
