#include "../shell_header.h"

void	remove_env(t_env **pr, t_env **now, t_env **start)
{
	if (*pr == NULL)
		*start = (*now)->next;
	else
		(*pr)->next = (*now)->next;
	if ((*now)->type != NULL)
		free((*now)->type);
	if ((*now)->value != NULL)
		free((*now)->value);
	free(*now);
}

int	ft_unset(t_info *info, t_env *env)
{
	int		i;
	t_env	*pr;
	t_env	*now;

	i = 1;
	while (info->args_num != 0 && info->args[i] != NULL)
	{
		pr = NULL;
		now = env;
		while (now != NULL)
		{
			if (ft_strncmp(now->type, info->args[i], ft_strlen(info->args[i])) == 0)
			{
				remove_env(&pr, &now, &env);
				break ;
			}
			pr = now;
			now = now->next;
		}
		i++;
	}
	return (0);
}