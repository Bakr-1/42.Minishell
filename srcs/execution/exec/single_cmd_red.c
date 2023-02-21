/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd_red.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:32:03 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/19 22:25:41 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_cpath(char *path);
void		check_file_pre(t_pa *pars2);
void		find_cpath(t_pa *pars2, t_exec *exec);
static void	scr_norm(void);
void		single_command_red(void);

static void	free_cpath(char *path)
{
	if (path != NULL)
		free(path);
	path = NULL;
	exec_free(g_gm.pars2, g_gm.exec);
	if (g_gm.pars2)
		free_pars2(g_gm.pars2);
	free_global();
	close_all_fd(g_gm.fd_closed);
}

/*
we check if the file is in the current directory
if not we check if the file is in the path
if not we exit
*/
void	check_file_pre(t_pa *pars2)
{
	int		fd;

	if (ft_strncmp(pars2->tokens[0], "./", 2) == 0)
	{
		fd = open(pars2->tokens[0], O_RDONLY);
		if (fd < 0)
			if (err_in_out(pars2))
				return ;
		if (execve(pars2->tokens[0], pars2->tokens, g_gm.env) == -1)
		{
			close(fd);
			exit(check_exit_message(pars2, NULL));
		}
		close(fd);
	}
}

/*
first we check for error if there is any we exit
then we check if the file is in the current directory
if not we check if the file is in the path
if not we exit
*/
void	find_cpath(t_pa *pars2, t_exec *exec)
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
		if (err_in_out(pars2))
			return (free_cpath(path), exit(g_gm.status));
	if (execve(path, pars2->tokens, g_gm.env) == -1)
	{
		close(fd);
		exit(check_exit_message(pars2, path));
	}
	free(path);
	close(fd);
}

static void	scr_norm(void)
{
	if (g_gm.exec->fd_in && g_gm.exec->error == 0)
	{
		if (dup2(g_gm.exec->fd_in, 0) < 0)
			dup2_pipe_fail(g_gm.exec, g_gm.exec);
		close(g_gm.exec->fd_in);
	}
	if (g_gm.exec->fd_out && g_gm.exec->error == 0)
	{
		if (dup2(g_gm.exec->fd_out, 1) < 0)
			dup2_pipe_fail(g_gm.exec, g_gm.exec);
		close(g_gm.exec->fd_in);
	}
}

/*
first we init the exec struct
then we check for here doc
then we set the redirections
then we fork
if we are in the child we check for builtin
if not we go into the find_cpath function
else we close all fd and free the child and exit
if we are in the parent we wait for the child
*/
void	single_command_red(void)
{
	pid_t	pid;

	init_exec(g_gm.exec);
	here_doc_exec(g_gm.pars2, g_gm.exec);
	set_redir(g_gm.pars2, g_gm.exec);
	g_gm.fd_closed = 0;
	g_gm.pid = 0;
	pid = fork_cmd_pipe();
	if (pid == 0)
	{
		scr_norm();
		if (g_gm.exec->error == 0 && check_builtin(g_gm.pars2->tokens))
			return (exec_builtin(g_gm.exec, g_gm.pars2->tokens), \
				free_the_child(NULL), exit(g_gm.status));
		else if (g_gm.exec->error == 0)
		{
			find_cpath(g_gm.pars2, g_gm.exec);
			close_all_fd(0);
		}
		else
			return (close_all_fd(0), free_the_child(NULL), exit(g_gm.status));
	}
	my_wait();
	g_gm.fd_closed = 3;
	g_gm.pid = 1;
}
