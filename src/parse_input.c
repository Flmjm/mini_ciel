/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:21:57 by mleschev          #+#    #+#             */
/*   Updated: 2025/10/14 14:41:59 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_parse.h"

void manage_input(char *str) //verifie l'input de readline et la passe en **argv et en liste chainees
{
	t_input_info *infos;
	t_token *token;
	t_commands	*cmds;

	infos = ft_malloc(sizeof(t_input_info), 0);
	infos->input = str;
	is_complete(infos);
	add_history(infos->input);
	replace_var_input(infos);
	token = ft_token(infos->input);
	print_tokens(token);
	cmds = ft_init_cmd(token);
	print_redirections(cmds);
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

t_commands	*sep_cmd(t_token *input)
{
	int	i;
	int	j;
	t_token		*current;
	t_commands	*commands;
	t_commands	*new;
	int nbr;

	current = input;
	commands = NULL;
	new = NULL;
	nbr = 1;
	i = 0;
	while (current)
	{
		if ((current->type == TOKEN_WORD || current->type == TOKEN_REDIRECT_IN) && (i == 0))
		{
			j = 0;
			new = ft_malloc(sizeof(t_commands), 0);
			nbr = how_many_args(current) + 1;
			new->argv = ft_malloc(sizeof(char *) * nbr, 0);
			new->argv[j] = current->value;
			i = 1;
		}
		if (!current->next && new)
		{
			if (current->type == TOKEN_PIPE)
				new->argv[j] = NULL;
			else
			{
				new->argv[j] = current->value;
				new->argv[j + 1] = NULL;
			}
			add_node_cmds(&commands, new);
			i = 0;
		}
		else if ((current->type != TOKEN_PIPE) && (i = 1) && new)
			new->argv[j] = current->value;
		else if ((current->type == TOKEN_PIPE) && new)
		{
			new->argv[j] = NULL;
			add_node_cmds(&commands, new);
			i = 0;
		}
		j++;
		current = current->next;
	}
	return (commands);
}

void	print_test(t_commands **cmds)
{
	int	i;
	t_commands	*test;

	test = *cmds;
	int j;
	i = 0;
	j = 0;
	while (test)
	{
		while (test->argv[i])
		{
			printf("%d: %s\n", i, test->argv[i]);
			i++;
		}
		if (test->next)
			printf("\nNEXT\n\n");
		test = test->next;
		i = 0;
		j++;
	}
}

void	add_node_cmds(t_commands **commands, t_commands	*new)
{
	t_commands	*current;

	current = *commands;
	if (!current)
	{
		new->next = NULL;
		*commands = new;
		return ;	
	}
	new->next = NULL;
	while (current->next)
		current = current->next;
	current->next = new;
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

void print_cmds(t_commands *cmds) {
    printf("\n=== TOKENS ===\n");
    t_commands *current = cmds;
    int index = 0;
	int j = 0;

    while (current) {


        printf("[%d] %d: '%s'\n",index,j,current->argv[j]);
		current = current->next;
		index++;
    }
    printf("\n");
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

