/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:55:37 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/13 19:18:22 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_fd(int fd);
void	big_free_free(void);
void	big_free(int i);
void	*calloc_minishell(size_t size, size_t count);

void	close_all_fd(int fd)
{
	if (fd < 0)
		fd = 3;
	while (fd < 10240)
		close(fd++);
}

void	big_free_free(void)
{
	if (g_gm.c)
	{
		free(g_gm.c);
		g_gm.c = NULL;
	}
	if (g_gm.parse)
	{
		free_parse3(g_gm.parse);
		free(g_gm.parse);
		g_gm.parse = NULL;
	}
	if (g_gm.arrcmd)
	{
		free_cmd(g_gm.arrcmd, 0);
		g_gm.arrcmd = NULL;
	}
	if (g_gm.env)
	{
		ft_undo_alloc(g_gm.env);
		free(g_gm.env);
		g_gm.env = NULL;
	}
	close_all_fd(3);
}

void	big_free(int i)
{
	if (i == 1)
	{
		if (g_gm.exec)
		{
			exec_free(g_gm.pars2, g_gm.exec);
		}
		if (g_gm.pars2)
		{
			free_pars2(g_gm.pars2);
			g_gm.pars2 = NULL;
		}
	}
	big_free_free();
}

void	*calloc_minishell(size_t size, size_t count)
{
	void	*ptr;

	ptr = ft_calloc(size, count);
	if (!ptr)
	{
		big_free(1);
		ft_fprintf(STDERR_FILENO, "minishell: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return (ptr);
}
