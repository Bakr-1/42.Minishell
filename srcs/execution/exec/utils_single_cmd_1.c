/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_single_cmd_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:29:24 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/19 22:28:16 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		errors_exec(t_pa *pars2, t_exec *exec);
void		failed_open(t_exec *exec, char *file);
static void	set_outfiles(t_pa *pars2, t_exec *exec, int i);
static void	set_infiles(t_pa *pars2, t_exec *exec, int i);
void		set_redir(t_pa *pars2, t_exec *exec);

/*
we check if there are errors in the command and if there are we print the
appropriate error message and exit the child process with the right status
*/
void	errors_exec(t_pa *pars2, t_exec *exec)
{
	if (pars2->tokens == NULL)
	{
		free_the_child(NULL);
		exit(g_gm.status);
	}
	else if (exec->error != 0)
	{
		ft_fprintf(2, "minishell: %s: command not found\n", pars2->tokens[0]);
		free_the_child(NULL);
		g_gm.status = 1;
		exit(g_gm.status);
	}
	else if (!ft_strlen(pars2->tokens[0]))
	{
		ft_fprintf(2, "minishell: %s: command not found\n", pars2->tokens[0]);
		free_the_child(NULL);
		g_gm.status = 1;
		exit(g_gm.status);
	}
}

void	failed_open(t_exec *exec, char *file)
{
	exec->error = 1;
	ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", file, strerror(errno));
	g_gm.status = 1;
}

/*
we chcek if the redirection is a > or >> and if there is a file
if there is, we open it and set the fd to the right place
with the right premissions and flags for > and >> respectively
*/
static void	set_outfiles(t_pa *pars2, t_exec *exec, int i)
{
	int	fd;

	if (pars2->redirec[i].type == GREATT && exec->error == 0)
	{
		fd = open(pars2->redirec[i].file, \
			O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
		if (fd < 0)
			failed_open(exec, pars2->redirec[i].file);
	}
	if (pars2->redirec[i].type == GREATERR && exec->error == 0)
	{
		fd = open(pars2->redirec[i].file, \
			O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
		if (fd < 0)
			failed_open(exec, pars2->redirec[i].file);
	}
	exec->fd_out = fd;
}

/*
we chcek if the redirection is a < and if there is a file
if there is, we open it and set the fd to the right place
with the right premissions and flags for > and >> respectively
*/
static void	set_infiles(t_pa *pars2, t_exec *exec, int i)
{
	int	fd;

	if (pars2->redirec[i].type == LESSS && pars2->redirec[i].file)
	{
		fd = open(pars2->redirec[i].file, O_RDONLY);
		if (fd < 0)
			failed_open(exec, pars2->redirec[i].file);
		exec->fd_in = fd;
	}
}

/*
as many as there are redirections, we check if there is a file
and if there is, we open it and set the fd to the right place
*/
void	set_redir(t_pa *pars2, t_exec *exec)
{
	int	i;

	i = 0;
	while (i < pars2->n_redirec)
	{
		if (pars2->redirec[i].type == LESSS && pars2->redirec[i].file)
			set_infiles(pars2, exec, i);
		if (!exec->error && (pars2->redirec[i].type == GREATERR \
			|| pars2->redirec[i].type == GREATT) && !exec->error \
			&& pars2->redirec[i].file)
			set_outfiles(pars2, exec, i);
		i++;
	}
}
