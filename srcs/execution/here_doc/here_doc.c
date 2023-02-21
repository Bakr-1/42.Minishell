/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:08:05 by aalseri           #+#    #+#             */
/*   Updated: 2023/02/21 13:15:34 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_env(char *str, int quoted);
char	*here_doc_join(char *file, int quoted);
int		here_doc_loop(t_redirection *red, t_exec *exec);
void	here_doc(t_redirection *red, t_exec *exec);
void	here_doc_exec(t_pa *pars2, t_exec *exec);

/*
this part is to expand the environment variables in the here doc
we check if the string is empty or if it is quoted
if it is we return the string it self without expanding the environment variables
if it is not we go into the loop
in the loop we check if the character is a dollar sign
if it is we go into the env_hd function
if it is not we join the character with the temp string
*/
char	*heredoc_env(char *str, int quoted)
{
	char	*temp;

	if (ft_strlen(str) == 0 || quoted == 1)
		return (ft_strdup(str));
	temp = ft_strdup("");
	while (str[++(g_gm.c->gg)])
	{
		if (str[g_gm.c->gg] != DOLLAR)
			temp = ft_scjoin(temp, str[g_gm.c->gg]);
		else
		{
			g_gm.c->gg++;
			if (ft_isdigit(str[g_gm.c->gg]) || str[g_gm.c->gg] == '?' \
				|| env_check(str[g_gm.c->gg]))
				temp = env_hd(str, temp, 0);
			else
			{
				temp = env_hd(str, temp, 1);
				if (!str[g_gm.c->gg])
					break ;
				temp = ft_scjoin(temp, str[g_gm.c->gg]);
			}
		}
	}
	return (temp);
}

/*
the strcmp will check if the input is the same as the delimiter
if it is we return NULL and break the loop
if it is not we join the input with the delimiter and write it to the file
*/
char	*here_doc_join(char *file, int quoted)
{
	char	*str;

	if (ft_strcmp(g_gm.h_doc->read, file) == 0)
	{
		free(g_gm.h_doc->read);
		return (NULL);
	}
	g_gm.c->gg = -1;
	str = ft_strjoinee(heredoc_env(g_gm.h_doc->read, quoted), "\n", 1, 0);
	ft_fprintf(g_gm.h_doc->fd, "%s", str);
	free(str);
	free(g_gm.h_doc->read);
	return ("HELLO");
}

// fd[0] counter just as fd to save lines
/*
we take the input from the user and write it to the file
if the input is the same as the delimiter we break the loop
if the user presses ctrl + d we break the loop and delete the file
with the unlink function and free the memory
*/
int	here_doc_loop(t_redirection *red, t_exec *exec)
{
	while (1)
	{
		g_gm.pid = 1;
		g_gm.h_doc->read = readline("heredoc> ");
		g_gm.pid = 0;
		if (g_gm.h_doc->read == NULL)
		{
			ft_fprintf(g_gm.h_doc->fd, "\n");
			if (exec->file)
			{
				free(exec->file);
				exec->file = NULL;
			}
			break ;
		}
		if (!here_doc_join(red->file, red->quoted))
			break ;
	}
	return (0);
}

/*
we allocate the struct and create the file
then we loop through the input from the user and write it to the file
*/
void	here_doc(t_redirection *red, t_exec *exec)
{
	g_gm.h_doc = calloc_minishell(1, sizeof(t_here_doc));
	g_gm.h_doc->fd = creating_dump_file(exec);
	here_doc_loop(red, exec);
	close(g_gm.h_doc->fd);
	free(g_gm.h_doc);
	g_gm.h_doc = NULL;
}

/*
**	Here doc is a special case of redirection
**	Here doc is a redirection that takes input from the user
first we loop through all the redirections and find the here doc
then we create a file and write the input from the user to the file
then we change the type of the redirection to less and change the file
to the file we created
*/
void	here_doc_exec(t_pa *pars2, t_exec *exec)
{
	char	*str;

	str = NULL;
	set_c(3);
	g_gm.c->g = 0;
	while ((g_gm.c->g) < pars2->n_redirec)
	{
		if (pars2->redirec[g_gm.c->g].type == HERE_DOCC)
		{
			here_doc(&pars2->redirec[g_gm.c->g], exec);
			pars2->redirec[g_gm.c->g].type = LESSS;
			str = pars2->redirec[g_gm.c->g].file;
			pars2->redirec[g_gm.c->g].file = exec->file;
			free(str);
		}
		g_gm.c->g++;
	}
}
