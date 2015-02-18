/*
** xfunctions.h for 42sh in /u/all/bereng_p/cu/public/42group/current/headers/lib_headers
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sun Mar 14 10:57:18 2010 philippe berenguel
** Last update Wed Apr 28 11:29:06 2010 cerisier mickael
*/

#ifndef		_XFUNCTIONS_H_
# define	_XFUNCTIONS_H_

# ifndef	_SYS_STAT_H
#  include <sys/stat.h>
# endif		/* _SYS_STAT_H */
# ifndef	_FCNTL_H_
#  include <fcntl.h>
# endif		/* _FCNTL_H_ */
# ifndef	_UNISTD_H_
#  include <unistd.h>
# endif		/* _UNISTD_H_ */
# ifndef	_SIGNAL_H_
#  include <signal.h>
# endif		/* _SIGNAL_H_ */
# ifndef	_TERMIOS_H_
#  include <termios.h>
# endif		/* _TERMIOS_H_ */
# ifndef	_SYS_TYPES_H_
#  include <sys/types.h>
# endif		/* _SYS_TYPES_H_ */
# ifndef	_DIRENT_H_
#  include <dirent.h>
# endif		/* _TERMIOS_H_ */
# ifndef	_GLOB_H_
#  include <glob.h>
# endif		/* _GLOB_H_ */
# ifndef	_SYS_TYPES_H
#  include <sys/wait.h>
# endif		/* _SYS_TYPES_H */

typedef		void(*sighandler_t)(int);

void		*xmalloc(size_t size);
int		xopen(const char *pathname, int flags, mode_t mode);
DIR		*xopendir(const char *name);
ssize_t		xread(int fd, void *buf, size_t count);
struct dirent	*xreaddir(DIR *dirp);
int		xclose(int fd);
int		xchdir(const char *path);
pid_t		xfork(void);
pid_t		xwaitpid(pid_t pid, int *status, int options);
char		*xgetcwd(char *buf, size_t size);
int		xglob(const char *pattern, int flags,
		     int (*errfunc) (const char *epath, int eerrno),
		     glob_t *pglob);
sighandler_t	xsignal(int signum, sighandler_t handler);
int		xkill(pid_t pid, int sig);
int		xkillpg(int pgrp, int sig);
int		xpipe(int pipefd[2]);
int		xdup(int oldfd);
int		xdup2(int oldfd, int newfd);
char		*xtgetstr(char *id, char **area);
int		xtgetent(char *bp, const char *name);
int		xioctl(int d, unsigned long request, void *term);
int		xtputs(const char *str, int affcnt, int (*putc)(int));
ssize_t		xwrite(int fd, const void *buf, size_t count);
int		xlseek(int fildes, int offset, int whence);
int		xexecve(const char *filename, char *const argv[],
			char *const envp[]);
int		xtcsetpgrp(int fd, pid_t pgrp);
int		xsetpgid(pid_t pid, pid_t pgid);
int		xstat(const char *path, struct stat *buf);
int		xclosedir(DIR *dirp);

#endif		/* _XFUNCTIONS_H_ */
