/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_var.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 06:28:30 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/03 18:51:35 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_VAR_H
# define M_VAR_H

# include "minishell.h"

/*
 * The following variables are used to control the parsing of the shell.
*/

# define PIPE 124
# define GREAT 62
# define LESS 60
# define DQUOTE 34
# define SQUOTE 39
# define DOLLAR 36
# define BSLASH 92
# define METAA "|>< \"\'"
# define METAAD " $ \"\'><|"

# define PROMPT "🥺\033[1;34m︻╦̵̵̿╤────$>\033[0m"

# define PIPEE 1
# define GREATT 2
# define GREATERR 3
# define LESSS 4
# define HERE_DOCC 5
# define _EOF 6
# define STRINGG 7
# define INPUTT_ER 8

# define PIPEE_S 1
# define TOK_S 2

#endif