/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:21:57 by mleschev          #+#    #+#             */
/*   Updated: 2025/10/20 16:47:05 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_parse.h"

t_commands *manage_input(char *str, t_exitcode *exit_code) //verifie l'input de readline et la passe en **argv et en liste chainees
{
	t_input_info *infos;
	t_token *token;
	t_commands	*cmds;

	infos = ft_malloc(sizeof(t_input_info), 0);
	infos->input = str;
	is_complete(infos);
	add_history(infos->input);
	replace_var_input(infos, exit_code);
	token = ft_token(infos->input);
	// print_tokens(token);
	cmds = ft_init_cmd(token);
	// print_redirections(cmds);
	return (cmds);

	//print_cmds(cmds);
	//free(token);
	//free(infos);
}

void	replace_backslash_double_quote(t_input_info *infos)
{
	int i;

	i = 0;
	while (infos->input[i])
	{
		if (infos->input[i] == '"')
		{
			i++;
			while (infos->input[i] != '"')
			{
				if (infos->input[i] == '\\')
				{
					if (infos->input[i + 1] == '$')
						quote_next_char(infos, i);
					else if (infos->input[i + 1] == '\'')
						erase_in_str(infos, i);
				}
				i++;
			}
		}
		i++;
	}
}

void	define_operator(t_input_info *infos)
{
	int	i;
	i = 0;

	while (infos->input[i])
	{
		if (infos->input[i] == '"')
			i = next_double_quote(infos, i, FALSE);
		else if (infos->input[i] == '\'')
			i = next_simple_quote(infos, i);
		else if ((infos->input[i] == '&' || infos->input[i] == '|' || infos->input[i] == '>' || infos->input[i] == '<') && infos->input[i - 1] != ' ')
		{
			add_space_before(infos, i);
			i++;
			while ((infos->input[i] == '&' || infos->input[i] == '|' || infos->input[i] == '>' || infos->input[i] == '<'))
				i++;
			if (infos->input[i] && infos->input[i] != ' ')
				add_space_before(infos, i);
		}
		i++;
	}
}

void	add_space_before(t_input_info *infos, int i)
{
	char *buffer;
	int	j;

	j = 0;
	buffer = ft_malloc(sizeof(char) * (ft_strlen(infos->input) + 2), 0);
	while (j < i)
	{
		buffer[j] = infos->input[j];
		j++;
	}
	buffer[j] = ' ';
	j++;
	while (infos->input[i])
	{
		buffer[j] = infos->input[i];
		j++;
		i++;
	}
	buffer[j] = '\0';
	//free(infos->input);
	infos->input = buffer;
}

int		strlen_of_args(t_input_info *infos, int arg)
{
	int	length;
	int i;
	int	current_arg;
	int j;

	j = 0;
	i = 0;
	length = 0;
	current_arg = 0;
	while (infos->input[i])
	{
		while (infos->input[i] && infos->input[i] == ' ')
			i++;
		if (infos->input[i] && infos->input[i] != ' ')
		{
			if (current_arg == arg)
			{
				while (infos->input[i] && infos->input[i] != ' ')
				{
					j = 0;
					if (infos->input[i] == '"')
					{
						j = next_double_quote(infos, i, FALSE);
						length = j - i + length - 1;
						i = j;
					}
					else if (infos->input[i] == '\'')
					{
						j = next_simple_quote(infos, i);
						length = j - i + length - 1;
						i = j;
					}
					else
						length++;
					i++;
				}
				return (length);
			}
			while (infos->input[i] && infos->input[i] != ' ')
			{
				if (infos->input[i] == '"')
					i = next_double_quote(infos, i, FALSE);
				else if (infos->input[i] == '\'')
					i = next_simple_quote(infos, i);
				i++;
			}
			current_arg++;
		}
	}
	return (length);
}

int		next_space(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == ' ')
			return (i);
		i++;
	}
	return (i);
}
void	erase_in_str(t_input_info *infos, int i)
{
	char *buffer;
	int	j;
	j = 0;

	buffer = ft_malloc(sizeof(char) * (ft_strlen(infos->input)), 0);
	while (j < i)
	{
		buffer[j] = infos->input[j];
		j++;
	}
	while (infos->input[i])
	{
		buffer[j] = infos->input[i + 1];
		j++;
		i++;
	}
	buffer[j] = '\0';
	//free(infos->input);
	infos->input = buffer;
}

int	how_many_args(t_token	*input)
{
	int	i;
	t_token	*current;

	current = input;
	i = 0;
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	return (i);
}

void	print_redirections(t_commands *cmds)
{
int			i;
t_infiles	*in;
t_outfiles	*out;
int			cmd_index;
cmd_index = 1;
while (cmds)
{
	printf("=== Commande %d ===\n", cmd_index);
	i = 0;
	while (cmds->argv && cmds->argv[i])
	{
		printf("  argv[%d]: %s\n", i, cmds->argv[i]);
		i++;
	}
	in = cmds->infiles;
	out = cmds->outfiles;
	if (!in && !out)
		printf("  (Aucune redirection)\n");
	if (in)
	{
		printf("  Infiles:\n");
		while (in)
		{
			if (in->type == FILE_HEREDOC)
				printf("    - %s (type: << // EOF: %s)\n", in->infile, in->word_eof);
			else if (in->type == FILE_REDIRECT_IN)
				printf("    - %s (type: < // EOF: %s)\n", in->infile, in->word_eof);
			in = in->next;
		}
	}
	if (out)
	{
		printf("  Outfiles:\n");
		while (out)
		{
			if (out->type == FILE_REDIRECT_APPEND)
				printf("    - %s (type: >>)\n", out->outfile);
			else if (out->type == FILE_REDIRECT_OUT)
				printf("    - %s (type: >)\n", out->outfile);
			out = out->next;
		}
	}
	printf("\n");
	cmds = cmds->next;
	cmd_index++;
}
}

