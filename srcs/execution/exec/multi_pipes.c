/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:22:31 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/19 22:45:26 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			single_command_pipe(t_pa *pars2, t_exec *exec);
static void	cep_norm(t_exec *exec, int last_cmd, t_exec *e);
static void	child_exec_pipe(t_pa *pars2, t_exec *exec, int cmd, t_exec *e);
static int	pipe_cmd(void);
void		execute_pipe(int i);

int	single_command_pipe(t_pa *pars2, t_exec *exec)
{
	char	*path;
	char	*tmp;
	int		fd;

	errors_exec(pars2, exec);
	check_file_pre(pars2);
	tmp = ft_strjoin("/", pars2->tokens[0]);
	path = path_pipex(tmp);
	free(tmp);
	if (!path)
		path = ft_strdup(pars2->tokens[0]);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		if (err_in_out(pars2))
		{
			free_the_child(path);
			return (127);
		}
	}
	close(fd);
	if (execve(path, pars2->tokens, g_gm.env))
		return (check_exit_message(pars2, path));
	return (-1);
}

static void	cep_norm(t_exec *exec, int last_cmd, t_exec *e)
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
	close_pipes(e->fd_pipe, g_gm.pars2->n_cmds - 1);
}

/*
we first called the cep_norm function to handle the pipes
then we check if there is an error and if there is a token
then we check if it is a builtin command
if it is we execute it and exit
if it is not we call single_command_pipe to execute the command
*/
static void	child_exec_pipe(t_pa *pars2, t_exec *exec, int last_cmd, t_exec *e)
{
	cep_norm(exec, last_cmd, e);
	if (exec->error == 0 && pars2->tokens && exec_builtin(exec, pars2->tokens))
	{
		free_the_child(NULL);
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

/*
we allocate the pipes
then we open all the pipes and store the file descriptors
in the exec struct fd_pipe
then we loop through the commands and fork
we call the child_exec_pipe function to execute the commands
with the parameters we need which is the pars2 struct, exec struct,
if it is the last command and the exec struct which contains the pipes
then we close the pipes
*/
static int	pipe_cmd(void)
{
	pid_t	pid;

	set_c(2);
	allocate_pipe(g_gm.pars2, g_gm.exec);
	piping(g_gm.exec->fd_pipe, g_gm.pars2->n_cmds);
	while (g_gm.c->xx < g_gm.pars2->n_cmds && g_gm.error_pipe)
	{
		g_gm.pid = 0;
		pid = fork_cmd_pipe();
		g_gm.fd_closed = 0;
		if (pid == 0)
			child_exec_pipe(&(g_gm.pars2[g_gm.c->xx]), \
				&(g_gm.exec[g_gm.c->xx]), (g_gm.c->xx + 1 == \
				g_gm.pars2->n_cmds), g_gm.exec);
		g_gm.c->ii++;
		g_gm.c->xx++;
	}
	close_pipes(g_gm.exec->fd_pipe, g_gm.pars2->n_cmds - 1);
	return (1);
}

/*
we loop through the commands and initialize the exec struct
then we call pipe_cmd to execute the commands
then we wait for the child processes to finish
*/
void	execute_pipe(int i)
{
	while (++i < g_gm.pars2->n_cmds)
		init_exec(&g_gm.exec[i]);
	pipe_cmd();
	my_wait();
	g_gm.pid = 1;
	g_gm.fd_closed = 3;
}
