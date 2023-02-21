/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:04:41 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/19 22:38:49 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		creating_dump_file(t_exec *exec);
char	*invalied_env_hd(char *str, int i);
char	*env_hd(char *str, char *temp, int i);

/*
here we are just creating a file in the tmp folder
we are using the file descriptor to write to the file
the idea was to make i static and every time it would increment
but it was not working so i just eneded up not using it and 
unlink the file after i am done with it.
*/
int	creating_dump_file(t_exec *exec)
{
	int		i;
	char	*str[2];
	int		fd;

	i = 0;
	str[0] = ft_itoa(i);
	str[1] = ft_strjoin_gnl_extra(ft_strdup("/tmp/minishell_dump_"), str[0]);
	str[1] = ft_strjoin_gnl_extra(str[1], ft_strdup(".txt"));
	exec->file = str[1];
	fd = open(exec->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_fprintf(2, "minishell: %s", exec->file);
		close_all_fd(3);
		perror(" ");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

char	*invalied_env_hd(char *str, int i)
{
	char	*temp;

	temp = ft_strdup("");
	if (str[i] == '?')
		temp = ft_strjoin_gnl_extra(temp, ft_itoa(g_gm.status));
	else
	{
		i++;
		while (str[i] != '\0' && str[i] != ' ')
		{
			temp = ft_scjoin(temp, str[i]);
			i++;
		}
	}
	return (temp);
}

/*
this function is used to handle the env variables in the here doc
for the first part if i was 0 then it will return the invalied env
and join it with the temp string
for the second part if i was 1 then it will return the env variable
and join it with the temp string and free the env variable
*/
char	*env_hd(char *str, char *temp, int i)
{
	char	*str2;
	char	*env;

	if (!i)
	{
		str2 = invalied_env_hd(str, g_gm.c->gg);
		g_gm.c->gg += ft_strlen(str2) - 1;
		return (ft_strjoin_gnl_extra(temp, str2));
	}
	else
	{
		env = ft_strdup("");
		while (str[g_gm.c->gg] != '\0' && !env_check(str[g_gm.c->gg]))
		{
			env = ft_scjoin(env, str[g_gm.c->gg]);
			g_gm.c->gg++;
		}
		temp = ft_strjoin_gnl_extra(temp, find_in_env(g_gm.env, env, 1));
		free(env);
		return (temp);
	}
	return (NULL);
}
