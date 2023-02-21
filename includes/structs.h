/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 06:28:35 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/15 00:18:30 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

typedef struct s_co
{
	int		i;
	int		j;
	int		k;
	int		g;
	int		x;
	int		y;
	int		z;
	int		ii;
	int		jj;
	int		kk;
	int		gg;
	int		xx;
	int		yy;
	int		zz;
}			t_co;

typedef struct s_token
{
	char	*token;
	int		type;
	int		quoted;
}				t_token;

typedef struct s_arrcmd
{
	int				p_type;
	int				p_size;
	t_token			**tokens;
	int				redir;
	int				t_size;
	struct s_arrcmd	**value;
}				t_arrcmd;

typedef struct s_parse
{
	char		*s_r;
	int			size_read;
	int			c_char;
	int			index;
	int			read;
	bool		quoted;
	bool		one_line;
	t_token		*next_token;
	t_token		*prev_token;
}				t_parse;

typedef struct s_exec
{
	int		saved_in;
	int		saved_out;
	int		fd_in;
	int		fd_out;
	int		read_end;
	int		write_end;
	int		i;
	int		error;
	int		here_doc;
	char	*file;
	char	**path;
	int		**fd_pipe;
	int		dead_path;
}			t_exec;

typedef struct s_redirection
{
	int		type;
	char	*file;
	int		quoted;
}					t_redirection;

typedef struct s_pa
{
	char			**tokens;
	int				tokens_size;
	int				type;
	int				n_cmds;
	int				n_redirec;
	t_redirection	*redirec;
}	t_pa;

typedef struct s_here_doc
{
	char	*read;
	char	*readed;
	char	*temp;
	int		fd;
	int		i;
}				t_here_doc;

typedef struct s_gm
{
	char		**env;
	char		**env_v2;
	char		*s_r;
	int			status;
	int			n_pipes;
	int			pid;
	int			quotes;
	int			fd_closed;
	int			error;
	int			error_pipe;
	char		*prompt;
	t_co		*c;
	t_parse		*parse;
	t_arrcmd	*arrcmd;
	t_pa		*pars2;
	t_exec		*exec;
	t_here_doc	*h_doc;
}				t_gm;

#endif