# minishell


### Functions allowed in this project

| Function		| Manual Page		| From lib			| Description
| :--			| :--				| :--				| :--
| **printf**	| `man 3 printf`	| `<stdio.h>`		| write output to stdout
| **malloc**	| `man malloc`		| `<stdlib.h>`		| allocate dynamic memory
| **free**		| `man 3 free`		| `<stdlib.h>`		| free dynamic memory
| **read**		| `man 2 read`		| `<unistd.h>`		| read from a file descriptor
| **write**		| `man 2 write`		| `<unistd.h>`		| write to a file descriptor
| **open**		| `man 2 open`		| `<fcntl.h>`		| open and possibly create a file
| **close**		| `man 2 open`		| `<unistd.h>`		| close a file descriptor
| **fork**		| `man fork`		| `<unistd.h>`		| create a child process
| **wait**		| `man wait`		| `<sys/wait.h>`	| wait for process to change state
| **waitpid**	| `man waitpid`		| `<sys/wait.h>`	| wait for process to change state
| **wait3**		| `man wait3`		| `<sys/wait.h>`	| (obsolete) wait for process to change state, BSD style
| **wait4**		| `man wait4`		| `<sys/wait.h>`	| (obsolete) wait for process to change state, BSD style
| **signal**	| `man signal`		| `<signal.h>`		| ANSI C signal handling
| **kill**		| `man 2 kill`		| `<signal.h>`		| send signal to a process
| **exit**		| `man exit`		| `<stdlib.h>`		| cause normal process termination
| **getcwd**	| `man getcwd`		| `<unistd.h>`		| get current working directory
| **chdir**		| `man chdir`		| `<unistd.h>`		| change working directory
| **stat**		| `man 2 stat`		| `<sys/stat.h>`	| get file status by pathname
| **lstat**		| `man lstat`		| `<sys/stat.h>`	| get file status by pathname (for symlinks)
| **fstat**		| `man fstat`		| `<sys/stat.h>`	| get file status by fd
| **execve**	| `man execve`		| `<unistd.h>`		| execute program
| **dup**		| `man dup`			| `<unistd.h>`		| duplicate a file descriptor
| **dup2**		| `man dup2`		| `<unistd.h>`		| duplicate a file descriptor
| **pipe**		| `man pipe`		| `<unistd.h>`		| create pipe
| **opendir**	| `man opendir`		| `<dirent.h>`		| open a directory
| **readdir**	| `man readdir`		| `<dirent.h>`		| read a directory
| **closedir**	| `man closedir`	| `<dirent.h>`		| close a directory
| **strerror**	| `man strerror`	| `<string.h>`		| return string describing error number
| **errno**		| `man errno`		| `<errno.h>`		| number of last error
| **termcap**	| `man termcap`, `man termios`		| `<term.h>`		| direct curses interface to the terminfo capability database

---

# TO DO:

# Builtin

- echo with option ’-n’
    
    echo [-neE] [arg ...]
    Output the args, separated by spaces, followed by a newline.
    
    The return status is always 0.
    
    If -n is specified, the trailing newline is suppressed.
    
    If the  -e  option is given, interpretation of the following backslash-escaped characters is enabled.
    
    The -E option disables the interpretation of these escape characters, even on systems where they are interpreted by default. The xpg_echo shell option may be used to dynamically determine whether or not echo expands these escape  characters  by  default. echo does not interpret -- to mean the end of options.  echo interprets the following escape sequences:
    \a     alert (bell)
    \b     backspace
    \c     suppress trailing newline
    \e     an escape character
    \f     form feed
    \n     new line
    \r     carriage return
    \t     horizontal tab
    \v     vertical tab
    \\     backslash
    \0nnn  the eight-bit character whose value is the octal value nnn (zero to three octal digits)
    \xHH   the eight-bit character whose value is the hexadecimal
    
- cd with only a relative or absolute path
    
    cd [-L|-P] [dir]
    Change the current directory to dir.  The variable HOME is the default dir.  The variable CDPATH defines the search path for the directory containing dir. Alternative directory names  in CDPATH are separated by a colon (:). A null directory name in CDPATH is the same as the current directory, i.e., ``.''.  If dir begins with a slash (/), then CDPATH is not used.
    
    The -P option says to use the physical directory structure instead of following symbolic links (see also the -P option to the set builtin command);
    
    The -L option forces symbolic links to be followed.
    
    An argument of - is equivalent to $OLDPWD.  If a non-empty directory name from CDPATH is used, or if - is the first argument, and the directory change is successful, the absolute pathname of the new working directory is written to the standard output.  The  return  value  is true if the directory was successfully changed; false otherwise.
    
- pwd without any options
    
    pwd [-LP]
    Print the absolute pathname of the current working directory.  The pathname printed contains no symbolic links if the -P option is supplied or the -o physical option  to the  set  builtin  command  is  enabled.  If the -L option is used, the pathname printed may contain symbolic links.  The return status is 0 unless an error occurs while reading the name of the current directory or an invalid option is supplied.
    
- export without any options
    
    export [-fn] [name[=word]] ...
    export -p
    The supplied names are marked for automatic export to the environment of subsequently executed commands.  If the -f option is given, the names refer to functions.  If no names are given, or if the -p option is supplied, a list of all names that are exported in this shell is printed. The -n option causes the export property to be removed from each name.  If a variable name is followed by =word, the value of the variable is set to word.  export returns an exit status of  0  unless  an  invalid  option  is encountered, one of the names is not a valid shell variable name, or -f is supplied with a name that is not a function.
    
- unset without any options
    
    unset [-fv] [name ...]
    For each name, remove the corresponding variable or function. If no options are supplied, or the -v option is given, each name refers to a shell  variable. Read-only variables may not be unset.
    
    If -f is specified, each name refers to a shell function, and the function definition is removed.  Each unset variable or function is removed from the environment passed to subsequent commands. If any of RANDOM, SECONDS, LINENO, HISTCMD, FUNCNAME, GROUPS, or DIRSTACK are unset, they lose their special properties, even if they are subsequently reset.  The exit status is true unless a name is readonly.
    
- env without any options and any arguments
    
    
    env -- set environment and execute command, or print environment
    env [-iv] [-P altpath] [-S string] [-u name] [name=value ...] [utility [argument ...]]
    
    DESCRIPTION
    The env utility executes another utility after modifying the environment as specified on the command line. Each name=value option specifies the setting of an environment variable, name, with a value of value.  All such environment variables are set before the utility is executed.
    
    The options are as follows:
    - i
    
    Execute the utility with only those environment variables specified by name=value options.  The environment inherited by env is ignored completely.
    
     -P altpath
    
    Search the set of directories as specified by altpath to locate the specified utility program, instead of using the value of the PATH environment variable.
    
     -S string
    Split apart the given string into multiple strings, and process each of the resulting strings as separate arguments to the env utility.  The -S option recognizes some special character escape sequences and also supports environment-variable substitution, as described below.
    
     -u name
    f the environment variable name is in the environment, then remove it before processing the remaining options.  This is similar to the unset command in sh(1).  The value for name must not include the `=' character.
    
     -v
    
    Print verbose information for each step of processing done by the env utility.  Additional information will be printed if -v is specified multiple times.
    
    The above options are only recognized when they are specified before any name=value options.
    If no utility is specified, env prints out the names and values of the variables in the environment, with one name/value pair per line.
    
- exit without any options

Resources:
\- [_Source 1_](https://www.gnu.org/software/termutils/manual/termcap-1.3/), [_Source 2_](https://pubs.opengroup.org/onlinepubs/7908799/xbd/termios.html), [_Source 3_](https://man7.org/linux/man-pages/man3/termios.3.html)

[Notion-1](https://www.notion.so/Minishell-e856e9af377f44b588e5fe120d4b6e2a)
[Notion-2](https://www.notion.so/Shell-Shell-Scripting-6e0f0290a0304dad93a1d25ba15d92fe)
# 42.Minishell
