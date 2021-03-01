#include "../shell_header.h"

t_env		*find_env_env(t_env *env, char *type)
{
	int		len;

	while (env != NULL)
	{
		len = ft_strlen(type);
		if (ft_strncmp(env->type, type, len) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int			export_error(char *err, int fd, int i)
{
	if (i == 1)
	{
		ft_putstr_fd("minishell: export: `", fd);
		ft_putstr_fd(err, fd);
		ft_putstr_fd("': not a valid identifier\n", fd);
		return (1);
	}
	ft_putstr_fd("minishell: export: ", 1);
	ft_putendl_fd(strerror(errno), 1);
	return (errno);
}
