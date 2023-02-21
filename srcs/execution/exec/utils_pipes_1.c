/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:04:37 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/19 22:29:30 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		allocate_pipe(t_pa *pars2, t_exec *exec);
void	piping(int **fd, int n_cmds);
void	dup2_pipe_fail(t_exec *exec, t_exec *e);
void	free_the_child(char *path);
pid_t	fork_cmd_pipe(void);

/*
we call the allocate_pipe function to allocate the memory needed for the pipes
*/
int	allocate_pipe(t_pa *pars2, t_exec *exec)
{
	int	i;

	i = 0;
	exec->fd_pipe = calloc_minishell(pars2->n_cmds - 1, sizeof(int *));
	while (i < pars2->n_cmds - 1)
	{
		exec->fd_pipe[i] = calloc_minishell(2, sizeof(int));
		if (!exec->fd_pipe[i])
			return (0);
		exec->fd_pipe[i][0] = -420;
		exec->fd_pipe[i][1] = -420;
		i++;
	}
	return (1);
}

/*
this function is called in the execute_pipe function to open all 
the pipes needed for the commands to be executed in the pipe function
*/
void	piping(int **fd, int n_cmds)
{
	int	i;

	i = 0;
	while (i < n_cmds - 1)
	{
		if (pipe(fd[i]) < 0)
		{
			ft_fprintf(2, "Pipe failed\n");
			g_gm.error_pipe = 0;
			break ;
		}
		if (fd[i][0] >= 10240)
		{
			ft_fprintf(2, "Pipe 0 Max failed\n");
			g_gm.error_pipe = 0;
			break ;
		}
		if (fd[i][1] >= 10240)
		{
			ft_fprintf(2, "Pipe 1 Max failed\n");
			g_gm.error_pipe = 0;
			break ;
		}
		i++;
	}
}

void	dup2_pipe_fail(t_exec *exec, t_exec *e)
{
	close_pipes(e->fd_pipe, g_gm.pars2->n_cmds - 1);
	close(e->fd_out);
	close(e->fd_in);
	ft_fprintf(2, "minishell: %s", exec->file);
	perror(" ");
	g_gm.status = 1;
	close_all_fd(0);
	free_the_child(NULL);
	exit(EXIT_FAILURE);
}

void	free_the_child(char *path)
{
	if (path != NULL)
		free(path);
	path = NULL;
	close_pipes(g_gm.exec->fd_pipe, g_gm.pars2->n_cmds - 1);
	exec_free(g_gm.pars2, g_gm.exec);
	if (g_gm.pars2)
		free_pars2(g_gm.pars2);
	free_global();
	close_all_fd(g_gm.fd_closed);
}

pid_t	fork_cmd_pipe(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_printf("Forking failed\n");
		free_global();
		exit(EXIT_FAILURE);
	}
	return (pid);
}
