/*
** jobs.h for 42 in /home/snap/projects/42sh/current
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Sat May  8 16:33:28 2010 botton vivien
** Last update Sat May  8 16:33:28 2010 botton vivien
*/

#ifndef			_JOBS_H_
# define		_JOBS_H_

# ifndef		_PARSER_H_
#  include "parser.h"
# endif			/* _PARSER_H_ */

# define		TERMINATED -3
# define		STOPPED -2
# define		RUNNING -1
# define		FOREGROUND 0
# define		BACKGROUND 1
# define		MAX_LEN_CMD 60

# define		NORMAL_PRINT 1
# define		PRINT_PID 2
# define		PRINT_RUNNING 4
# define		PRINT_STOPPED 8

typedef struct		s_jobs
{
  int			pgid;
  t_lpid		*pids;
  int			id;
  int			background;
  int			status;
  int			last;
  char			*cmd;
  struct s_jobs		*next;
}			t_jobs;

/*fg.c*/
void			change_last(int change, int pid);
int			update_process(t_jobs *cpy, int background);
t_jobs			*get_process(t_jobs *jobs, const char *arg);

/* jobslist.c*/
void			add_job(int pid, char *cmd, t_exec *exec);
void			set_job(int pid, int arg);
void			update_pipe(t_lpid *pids, char *cmd);
void			del_job(t_lpid *lpid, int bg);

/* term_jobs.c*/
void			free_jobs(t_jobs *jobs);
void			print_job(t_jobs *jobs, int showpid);
void			print_term_jobs(int verbose);

#endif			/* _JOBS_H_ */
