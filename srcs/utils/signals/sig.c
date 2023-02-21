/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:08:43 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/15 01:47:10 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_g(void);
void		free_global(void);
static void	norm_sig(int sig);
static void	sig(int sig);
void		signals_hand(void);

static void	free_g(void)
{
	if (g_gm.env)
	{
		ft_undo_alloc(g_gm.env);
		free(g_gm.env);
		g_gm.env = NULL;
	}
	if (g_gm.env_v2)
	{
		ft_undo_alloc(g_gm.env_v2);
		free(g_gm.env_v2);
		g_gm.env_v2 = NULL;
	}
}

void	free_global(void)
{
	free_g();
	if (g_gm.parse)
	{
		free(g_gm.parse);
		g_gm.parse = NULL;
	}
	if (g_gm.s_r)
	{
		free(g_gm.s_r);
		g_gm.pars2 = NULL;
	}
	if (g_gm.c)
	{
		free(g_gm.c);
		g_gm.c = NULL;
	}
	close_all_fd(3);
}

static void	norm_sig(int sig)
{
	if (sig == SIGQUIT)
		ft_fprintf(STDERR_FILENO, "Quit: %d\n", SIGQUIT);
	else if (sig == SIGINT)
		ft_fprintf(STDERR_FILENO, "\n");
}

/*
** void rl_replace_line (const char *text, int clear_undo)
** Replace the contents of rl_line_buffer with text. The point and mark are 
** preserved, if possible.If clear_undo is non-zero,
** the undo list associated with the current line is cleared.
*/
/*
** int rl_on_new_line (void)
** Tell the update functions that we have moved onto
** a new (empty) line, usually after outputting a newline.
*/
/*
** void rl_redisplay (void) Change what's displayed
** on the screen to reflect the current contents of rl_line_buffer.
*/
static void	sig(int sig)
{
	if (g_gm.pid == 0)
		norm_sig(sig);
	else if (sig == SIGSEGV)
	{
		ft_fprintf(2, RED"BOOO!\n");
		free_global();
		exit(EXIT_FAILURE);
	}
	else
	{
		if (sig == SIGINT)
		{
			g_gm.status = 1;
			ft_fprintf(STDIN_FILENO, "\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		else if (sig == SIGQUIT)
			rl_redisplay();
	}
}

void	signals_hand(void)
{
	signal(SIGINT, sig);
	signal(SIGQUIT, sig);
	signal(SIGSEGV, sig);
}
