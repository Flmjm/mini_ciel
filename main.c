/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:48:24 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/07 21:29:11 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_parse.h"
#include "exec/pipex_bonus.h"

void manage_ctrlc(int sig)
{
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay(); 
}

int	main(int argc, char **argv, char **environt)
{
	int	exit_status;
	t_env *env_s;
	struct sigaction *ctrlc;

	env_s = ft_malloc(sizeof(t_env), 0);
	env_s->export = ft_env(environt, env_s);
	env_s->local_env = ft_env(environt, env_s);	//sert a init la struct et a avoir une copie des variables d'environnement
	ctrlc = ft_malloc(sizeof(struct sigaction), 0);
	env_s->signal = ctrlc;
	ctrlc->sa_handler = manage_ctrlc;
	sigemptyset(&ctrlc->sa_mask);
	ctrlc->sa_flags = SA_RESTART;
	sigaction(SIGINT, ctrlc, NULL);
	signal(SIGQUIT, SIG_IGN);
	prompt_loop(env_s); //la boucle principal du shell
	return (0);
}

void	prompt_loop(t_env *env_s)
{
	t_commands *cmds;
	char 		*input;
	char 		*buffer;
	t_exitcode *exit_code;

	exit_code = ft_malloc(sizeof(t_exitcode), 0);
	exit_code->last_cmd = 0;

	while (1)
	{
		input = readline(prompt_sentence(env_s));
		if (!input)
		{	
			write(1, "^D\n",3);
			ft_exit(env_s, 240);
		}
		cmds = manage_input(input, exit_code);	//j'ai mis ft_token a l'interieur
		if (cmds)
			exec_main(cmds, env_s, exit_code);
	}
}

char	*prompt_sentence(t_env *env)
{
	char	*result;
	int		i;
	//char	*bblue;

	i = 0;
	result = ft_malloc(sizeof(char) * (ft_strlen(env->pwd) + 2 + 1), 0);
	while(env->pwd[i])
	{
		result[i] = env->pwd[i];
		i++;
	}
	result[i++] = '~';
	result[i++] = '>';
	result[i] = '\0';
	//bblue = ft_malloc(sizeof(char) * (ft_strlen(result) + 20), 0);
	return(result);
}
