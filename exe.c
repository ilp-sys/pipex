#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

char	*make_abs_path(char *path, char *cmd)
{
	char *result =  (char *)malloc(strlen(path) + strlen(cmd) + 2);
	if (result)
	{
		strcpy(result, path);
		strcat(result, "/");
		strcat(result, cmd);
	}
	return (result);
}

		// binary path		- 	args		- 		env
//int execve(const char *file, char *const argv[], char *const envp[])
int main(int argc, char* argv[], char *argp[])
{
	char	*PATH;
	char	*buffer;
	char	**path;
	char	*cmd = "ls";
	pid_t	pid;
	int		i = 0;

	pid = fork();
	if (pid == 0)
	{
		PATH = getenv("PATH");
		while (1)
		{
			buffer = strtok(PATH, ":");
			if (!buffer)
				break ;
			path[i] = (char *)malloc(sizeof(char) * strlen(buffer) + 1);
			strlcpy(path[i], buffer, sizeof(path[i]));
			i++;
		}
		i = 0;
		while (access(make_abs_path(path[i++], cmd), X_OK) == -1) //access return -1 when fails	
			;
		if (path[i] == NULL)
		{
			perror("Invalid path\n");
			exit(0);
		}
		execve(path[i], NULL, NULL);
	}
	waitpid(pid, NULL, 0);
	return (0);
}
