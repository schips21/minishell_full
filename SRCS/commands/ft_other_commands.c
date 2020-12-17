#include "../shell_header.h"

int			error_errno(int err, int fd)
{
	ft_putendl_fd(strerror(err), fd);
	return (-1);
}

void		free_arr(char **array)
{
	int		i;

	i = 0;
	if (array != NULL)
	{
		while (array[i] != NULL)
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

/*в каком виде принимает полностью*/ 

int			env_len_class_1(t_env *env)
{
	int i;

	i = 0;
	while (env != NULL)
	{
		if (env->class == 1)
			i++;
		env = env->next;
	}
	return (i);
}

char		**from_env_to_array(t_env *env)
{
	char	**envp;
	int		i;

	envp = malloc((sizeof(char **)) * (env_len_class_1(env) + 1));
	if (envp == NULL)
		return (NULL);
	while (env != NULL)
	{
		if (env->class == 1)
		{
			if (env->value == NULL)
				envp[i] = ft_strjoin_path(env->type, "");
			else
				envp[i] = ft_strjoin_path(env->type, env->type);
			if (envp[i] == NULL)
			{
				free_arr(envp);
				return (NULL);
			}
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

int			excex_command(char *command, t_env *env, t_info *info)
{
	pid_t	pid;
	int		ret;
	char	**envp;

	//envp = from_env_to_array(env);
	ret = 1;
	printf("%s\n", command);
	pid = fork();
	if (pid == 0)
	{
		if ((execve(command, info->args, info->envp)) == -1)
		{
			printf("execvve\n");
			return (-1);
		}
		exit(ret);
	}
	else if (pid < 0)
		return (-1);
	else
	{
		//родительский процесс
		ret = 1;
		waitpid(pid, &ret, 0);
	}
	
	printf("%s\n", command);
	return (0);
}

int					if_file_here(t_info *info, DIR *new)
{
	struct dirent	*files;
	int				len;

	while ((files = readdir(new))!= NULL && errno == 0)
	{
		len = ft_strlen(info->args[0]); 
		if (len == files->d_namlen && (ft_strncmp(files->d_name, info->args[0], len)) == 0)
		{
			closedir(new);
			return (1);
		}
	}
	closedir(new);
	return (0);
}

int			ft_other_commands_2(t_info *info, t_env *env, char **path_arr)
{
	int				i;
	DIR				*new;
	char			*full_path;

	i = 0;
	while ((path_arr[i]) && (new = opendir(path_arr[i])) && errno == 0) //closedir
	{
		if ((if_file_here(info, new)) == 1)
		{
			if ((full_path = ft_strjoin_path(path_arr[i], info->args[0])) == NULL)	//malloc
				return (-1);
			i = excex_command(full_path, env, info);
			free(full_path);
			return (i);
		}
		i++;
	}
	if (errno != 0)
		return (-1);
	printf("no directory in path\n");
	return (excex_command(info->args[0], env, info));
}

int			ft_other_commands(t_info *info, t_env *env)
{
	char	*path;
	char	**path_arr;
	int		res;

	path = find_env(env, "PATH");
	if (path == NULL)
		return (excex_command(info->args[0], env, info));
	path_arr = ft_split(path, ':');
	if (path_arr == NULL)
		return (error_errno(errno, 1));
	res = ft_other_commands_2(info, env, path_arr);
	free_arr(path_arr);
	if (errno != 0)
		return (error_errno(errno, 1));
	return (res);
}