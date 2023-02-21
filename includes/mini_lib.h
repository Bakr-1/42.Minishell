/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_lib.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 06:28:25 by aalseri           #+#    #+#             */
/*   Updated: 2023/01/09 00:31:40 by aalseri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_LIB_H
# define MINI_LIB_H

# include "../libft/includes/libft.h"
# include "m_var.h"
# include "structs.h"
# include "utils.h"
# include "err.h"
# include "parse.h"
# include "exec.h"
# include "sig.h"
# include "builtin.h"

// signal, sigaction, sigemptyset, sigaddset, kill
# include <signal.h>

// opendir, readdir, closedir
# include <dirent.h>

//wait, waitpid, wait3, wait4
# include <sys/wait.h>

// stat, lstat, fstat
# include <sys/stat.h>

// ioctl
# include <sys/ioctl.h>

//  tcsetattr, tcgetattr
# include <termios.h>

//readline, rl_on_new_line, rl_replace_line
# include <readline/readline.h>

//rl_clear_history, add_history, rl_redisplay
# include <readline/history.h>

// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <term.h>

// errno
# include <errno.h>

#endif