#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "env_util.h"
#include "error.h"
#include "libft/libft.h"
#include "lpc.h"

int		*_last_exit_location(void);
char	**set_args(t_list *tokens);
char	*set_path(char *cmd);

static void	__attribute__((noreturn))	execute_child(t_list *tokens)
{
	char	**args;
	char	*cmd_path;

	args = set_args(tokens);
	cmd_path = set_path(args[0]);
	if (cmd_path)
	{
		execve(cmd_path, args, *g_env());
		free(cmd_path);
	}
	error_handler(args[0], 1);
	lpc_flush();
	exit(EXIT_FAILURE);
}

int	fork_pipes(t_list *tokens)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (error_handler("fork", 1));
	else if (!pid)
		execute_child(tokens);
	return (pid);
}

void	execute(t_list	*cmds)
{
	int	pid;
	int	wstatus;

	if (!cmds)
		return ;
	while (cmds)
	{
		pid = fork_pipes(cmds->content);
		waitpid(pid, &wstatus, 0);
		*_last_exit_location() = WEXITSTATUS(wstatus);
		cmds = cmds->next;
	}
}
