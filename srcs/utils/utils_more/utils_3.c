/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:27:25 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/13 14:50:49 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
first if | |
second if >> or | alone
*/
int		abnormal_case(t_parse *parse);
void	set_c(int i);
char	*find_in_env(char **env, char *str, int flag);
void	set_for_read(void);

int	abnormal_case(t_parse *parse)
{
	if (parse->prev_token->type == PIPEE && parse->next_token->type == PIPEE)
	{
		print_nl("syntax error near unexpected token 1", \
			parse->next_token->token);
		g_gm.status = 258;
		return (1);
	}
	if (parse->prev_token->type == PIPEE && parse->next_token->type == _EOF \
		&& parse->next_token->type && parse->prev_token->type)
	{
		print_nl("syntax error: unexpected end of pipe", NULL);
		g_gm.status = 258;
		return (1);
	}
	if ((redirect_tt(parse->prev_token->type) && \
		parse->next_token->type == _EOF)
		|| (parse->next_token->type == PIPEE && \
			parse->next_token->type == _EOF))
	{
		print_nl("syntax error near unexpected token", \
			parse->prev_token->token);
		g_gm.status = 258;
		return (1);
	}
	return (0);
}

void	set_c(int i)
{
	if (i == 1)
	{
		g_gm.c->i = -1;
		g_gm.c->jj = 0;
		g_gm.c->k = -1;
	}
	else if (i == 2)
	{
		g_gm.c->ii = 0;
		g_gm.c->xx = 0;
		g_gm.c->kk = 0;
	}
	else if (i == 3)
	{
		g_gm.c->gg = -1;
		g_gm.c->yy = -1;
		g_gm.c->zz = -1;
	}
}

char	*find_in_env(char **env, char *str, int flag)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		tmp = ft_strjoin(str, "=");
		if (ft_strncmp(env[i], tmp, ft_strlen(tmp)) == 0)
		{
			free(tmp);
			if (flag == 1)
				return (ft_strdup(env[i] + ft_strlen(str) + 1));
			else
				return (env[i]);
		}
		free(tmp);
		i++;
	}
	return (NULL);
}

void	set_for_read(void)
{
	g_gm.parse->c_char = 32;
	g_gm.parse->index = 0;
	g_gm.parse->read = 0;
	g_gm.parse->one_line = false;
}
