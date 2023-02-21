/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 18:25:10 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/19 22:21:10 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	single_cmd_norm(void);
void		single_command(void);


/*
the single_cmd_norm function is called in the single_command function. first we
check for the fd_in if there are no errors. if there are not we duplicate the file descriptor 
and close the file descriptor. then we check the fd_out if there are no errors. 
if not we duplicate the file descriptor and close the file descriptor. 
then we check if there are no errors.

-the idea from above is to redirect the input and output of the g_gm.exec->fd 
to the file descriptors of the input and output of the g_gm.exec->fd.
	using the dup2 function to redirect the file descriptor for standard output
	(STDOUT_FILENO) to the file descriptor for the output of the g_gm.exec process.
	If the dup2 call fails, the dup2_pipe_fail function is called with the g_gm.exec
	process as an argument. Finally, the file descriptor for the input of the g_gm.exec 
	process is closed.

if there are no errors we go into the find_cpath function. if there are
errors we free the child and exit the process.
*/
static void	single_cmd_norm(void)
{
	if (g_gm.exec->fd_in && g_gm.exec->error == 0)
	{
		if (dup2(g_gm.exec->fd_in, STDIN_FILENO) < 0)
			dup2_pipe_fail(g_gm.exec, g_gm.exec);
		close(g_gm.exec->fd_in);
	}
	if (g_gm.exec->fd_out && g_gm.exec->error == 0)
	{
		if (dup2(g_gm.exec->fd_out, STDOUT_FILENO) < 0)
			dup2_pipe_fail(g_gm.exec, g_gm.exec);
		close(g_gm.exec->fd_in);
	}
	if (g_gm.exec->error == 0)
		find_cpath(g_gm.pars2, g_gm.exec);
	else
		return (free_the_child(NULL), exit(g_gm.status));
}

/*
first we initialize the exec struct. then we check if the command is a builtin
if it is we execute the builtin. if it is not we set the redirections. then we
fork the process. if the pid is 0 which is the child process we go into 
the single_cmd_norm function. if the pid is not 0 which is the parent process we
go into the my_wait function.
*/
void	single_command(void)
{
	pid_t	pid;

	init_exec(g_gm.exec);
	if (g_gm.exec->error == 0 && check_builtin(g_gm.pars2->tokens))
	{
		exec_builtin(g_gm.exec, g_gm.pars2->tokens);
		return ;
	}
	set_redir(g_gm.pars2, g_gm.exec);
	g_gm.fd_closed = 0;
	g_gm.pid = 0;
	pid = fork_cmd_pipe();
	if (pid == 0)
		single_cmd_norm();
	my_wait();
	g_gm.fd_closed = 3;
	g_gm.pid = 1;
}
