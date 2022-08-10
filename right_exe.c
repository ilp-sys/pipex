#include "pipe.h"
​
int	main(void)
{
	pid_t pid1;
	pid_t pid2;
	pid_t pid3;
	pid_t pid4;
	int	openfile;
	
	int	outfile;
	int	fd[2];
	int	fd2[2];
	int	fd3[2];
	char	*cmd[2] = {"/bin/cat", NULL};
	char	*cmd2[2] = {"/bin/dog", NULL};
//  < test.txt cat | cat | cat | cat > test1.txt
	pipe(fd);
	pid1 = fork();
	if (pid1 == 0)
	{
		close(fd[0]);
		openfile = open("test.txt", O_RDONLY);
		dup2(openfile, 0);
		dup2(fd[1], 1);
		close(fd[1]);
		close(openfile);
		execve(cmd[0], cmd, NULL);
		exit(1);
	}
	pipe(fd2);
	pid2 = fork();
	if (pid2 == 0)
	{
		close(fd[1]);
		close(fd2[0]);
		dup2(fd[0], 0);
		dup2(fd2[1], 1);
		close(fd[0]);
		close(fd2[1]);
		execve(cmd[0], cmd, NULL);
		exit(1);
	}
	close(fd[0]);
	close(fd[1]);
	pipe(fd3);
	pid3 = fork();
	if (pid3 == 0)
	{
		close(fd2[1]);
		close(fd3[0]);
		dup2(fd2[0], 0);
		dup2(fd3[1], 1);
		close(fd2[0]);
		close(fd3[1]);
		execve(cmd[0], cmd, NULL);
		exit(1);
	}
	close(fd2[0]);
	close(fd2[1]);
	pid4 = fork();
	if (pid4 == 0)
	{
		close(fd3[1]);
		outfile = open("test1.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
		dup2(outfile, 1);
		dup2(fd3[0], 0);
		close(fd3[0]);
		execve(cmd2[0], cmd2, NULL);
		exit(127);
	}
	int	status1, status2, status3, status4;
	close(fd3[0]);
	close(fd3[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	waitpid(pid3, &status3, 0);
	if (waitpid(pid4, &status4, 0))
	{
		if (WIFEXITED(status4))
		{
			exit(WEXITSTATUS(status4));
		}
		else if (WIFSIGNALED(status4))
		{
			exit(128 + WTERMSIG(status4));
		}
	}
	return (0);
}
