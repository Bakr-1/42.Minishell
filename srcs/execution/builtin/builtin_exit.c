/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:45:15 by mealjnei          #+#    #+#             */
/*   Updated: 2023/01/15 12:37:18 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	err_exit(char *token, int i);
static void	exit_code(char *token);
static void	verify_num_token(char *token);
static void	exit_norm(char **token, int i, char *trim_para);
void		ft_exit(char **token);

static int	err_exit(char *token, int i)
{
	if (g_gm.fd_closed)
		ft_fprintf(2, "exit\n");
	if (i)
		ft_fprintf(2, "minishell: exit %s: numeric argument required\n", token);
	else
		i = 0;
	free_the_child(NULL);
	free(token);
	return (255);
}

static void	exit_code(char *token)
{
	int			i;
	long long	result;
	int			flag;

	flag = 0;
	i = 0;
	if (token[i])
	{
		while (token[i])
		{
			if (i == 0 && (token[i] == '-' || token[i] == '+'))
				i++;
			if (token[i] < '0' || token[i] > '9')
				exit(err_exit(token, 1));
			i++;
		}
	}
	result = atoi_long_exit(token, &flag);
	if (flag == 1)
		exit(err_exit(token, 1));
	err_exit(token, 0);
	exit (result);
}

static void	verify_num_token(char *token)
{
	int	i;
	int	alpha;

	i = 0;
	alpha = 0;
	while (token[i])
	{
		if (token[0] == '-' || token[0] == '+')
			i++;
		if (ft_isdigit(token[i]) == 0)
			alpha = 1;
		i++;
	}
	if (alpha == 0)
	{
		free (token);
		if (g_gm.fd_closed)
			ft_fprintf(2, "exit\n");
		ft_fprintf(2, "minishell exit: too many arguments\n");
		g_gm.status = 1;
	}
	else
		exit(err_exit(token, 1));
}

static void	exit_norm(char **token, int i, char *trim_para)
{
	if (i)
	{
		if (token == NULL || token[1] == NULL)
		{
			if (g_gm.fd_closed)
				ft_fprintf(2, "exit\n");
			free_the_child(NULL);
			exit(g_gm.status);
		}
	}
	else
	{
		if (ft_strcmp(trim_para, "-9223372036854775808") == 0)
		{
			if (g_gm.fd_closed)
				ft_fprintf(2, "exit\n");
			free(trim_para);
			free_the_child(NULL);
			exit(0);
		}
		exit_code(trim_para);
	}
}

void	ft_exit(char **token)
{
	char	*trim_para;

	exit_norm(token, 1, NULL);
	trim_para = ft_strtrim(token[1], " ");
	if (ft_strlen2d(token) > 2)
		return (verify_num_token(trim_para));
	else if (token[1])
		exit_norm(token, 0, trim_para);
	else
	{
		if (g_gm.fd_closed)
			ft_fprintf(2, "exit\n");
		free(trim_para);
		free_the_child(NULL);
		exit(g_gm.status);
	}
}
