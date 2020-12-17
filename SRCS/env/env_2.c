/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:41:15 by dskittri          #+#    #+#             */
/*   Updated: 2020/11/26 17:41:16 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell_header.h"

t_env		*get_env_type_value(char **envp, int count)
{
	char	*i;
	t_env	*env;
	char	*type;
	char	*value;

	type = ft_strdup_sp(envp[count], '=');
	i = ft_strchr(envp[count], '=') + 1;
	value = ft_strdup(i);
	env = ft_envnew(type, value, 1);
	return (env);
}

t_env		*get_env(char **envp, t_env *first)
{
	t_env	*env;
	int		count;

	count = 0;
	first = get_env_type_value(envp, count);
	if (first == NULL)
		return (NULL);
	count++;
	while (envp[count] != NULL)
	{
		env = get_env_type_value(envp, count);
		if (env == NULL)
			return (free_env(first));
		ft_lstenv_back(&first, env);
		count++;
	}
	return (first);
}