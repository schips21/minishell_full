#include "shell_header.h"

void	two_quot_red(char *line, t_info *parsed, int red_i, int *i)
{
	(*i)++;
	while (line[*i] != '\"')
	{
		if (line[*i] == '\\' && (line[*i + 1] == '\\' || line[*i + 1] == '\"' || line[*i + 1] == '$'))
		{
			(*i)++;
			new_letter_red(parsed, red_i, line[(*i)++]);
		}
			//если есть доллар, то будет ошибка
		else
			new_letter_red(parsed, red_i, line[(*i)++]);
	}
	(*i)++;
}

void	parser_redir(char *line, t_info *parsed, int *i)
{
	int red_i;

	red_i = 0;
	new_word_red(parsed);
	while(parsed->redirs[red_i])
		red_i++;
	new_letter_red(parsed, red_i, line[(*i)++]);
	if (line[*i] == '>' && line[*i - 1] == '>')
		new_letter_red(parsed, red_i, line[(*i)++]);
	red_i++;
	new_word_red(parsed);
	while (line[*i] == ' ')
		(*i)++;
	while(!ft_strchr(" ;|><", line[*i]) && line[*i])
	{
		if (line[*i] == '\'')
		{
			(*i)++;
			while (line[*i] != '\'')
				new_letter_red(parsed, red_i, line[(*i)++]);
			(*i)++;
		}
		else if (line[*i] == '\"')
			two_quot_red(line, parsed, red_i, i);
//		добавить условие про доллар
		else if (line[*i] == '\\')
		{
			(*i)++;
			new_letter_red(parsed, red_i, line[(*i)++]);
		}
		else
			new_letter_red(parsed, red_i, line[(*i)++]);
	}
//		new_letter_red(parsed, red_i, line[(*i)++]);
}
