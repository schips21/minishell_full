/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 13:02:44 by dskittri          #+#    #+#             */
/*   Updated: 2020/12/04 15:42:30 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_header.h"

void		redirect_processing_out(t_info *info, int i)
{
	if (info->out != 1)
		close(info->out);
	if (info->redirs[i][1] == '\0')
		info->out = open(info->redirs[i+1], O_RDWR | O_TRUNC | O_CREAT,
			S_IREAD | S_IWRITE);
	else
		info->out = open(info->redirs[i+1], O_RDWR | O_CREAT | O_APPEND,
			S_IREAD | S_IWRITE);
}

void		redirect_processing_in(t_info *info, int i)
{
	if (info->in != 0)
		close(info->in);
	info->in = open(info->redirs[i+1], O_RDWR);
}

int			redirect_processing(t_info *info)
{
	int		i;

	i = 0;
	while (info->redirs != NULL && info->redirs[i] != NULL)
	{
		if (info->redirs[i][0] == '>')
			redirect_processing_out(info, i);
		else if (info->redirs[i][0] == '<')
			redirect_processing_in(info, i);
		else
			ft_putendl_fd("Something is wrong with redirect array", 1); //после отладки можно убрать условие
		i = i+2;
		if (errno != 0 && info->redirs[i] != NULL)
		{
			ft_putstr_fd(info->redirs[i+1], 1);
			ft_putstr_fd(": ", 1);
			ft_putendl_fd(strerror(errno), 1);
			return (-1);
		}
	}
	return (0);
}