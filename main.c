/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:48:24 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/17 04:21:17 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/lib_parse.h"
#include "include/lib_exec.h"

void	manage_ctrlc(int sig)
{
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	prompt_loop(t_env *env_s)
{
	t_commands	*cmds;
	char		*input;
	char		*buffer;
	t_exitcode	*exit_code;

	exit_code = ft_malloc(sizeof(t_exitcode), 0);
	exit_code->last_cmd = 0;
	env_s->exitcode = exit_code;
	while (1)
	{
		input = readline(prompt_sentence(env_s));
		if (!input)
		{
			write(1, "^D\n", 3);
			ft_exit(env_s, NULL, 240);
		}
		cmds = manage_input(input, exit_code);
		if (cmds)
			exec_main(cmds, env_s, exit_code);
	}
}

void	clean_prompt(char *prompt)
{
	if (prompt[0] == '/')
		ft_memmove(prompt, &prompt[1], ft_strlen(prompt));
}

char	*prompt_sentence(t_env *env)
{
	char	*result;
	char	*prompt;
	int		i;

	i = 0;
	prompt = ft_malloc(sizeof(char) * (ft_strlen(env->pwd) + 1), 0);
	ft_strlcpy(prompt, env->pwd, ft_strlen(env->pwd) + 1);
	clean_prompt(prompt);
	result = ft_malloc(sizeof(char) * (ft_strlen(BCYAN)
				+ ft_strlen(BWHITE) + ft_strlen(prompt) + 5), 0);
	ft_strlcpy(result, BCYAN, ft_strlen(BCYAN) + 1);
	ft_strlcat(result, prompt, ft_strlen(BCYAN) + ft_strlen(prompt) + 2);
	ft_strlcat(result, "> ", ft_strlen(BCYAN) + ft_strlen(prompt) + 4);
	ft_strlcat(result, BWHITE, ft_strlen(BCYAN) + ft_strlen(BWHITE)
		+ ft_strlen(prompt) + 5);
	return (result);
}

int	main(int argc, char **argv, char **environt)
{
	int					exit_status;
	t_env				*env_s;
	struct sigaction	*ctrlc;

	env_s = ft_malloc(sizeof(t_env), 0);
	env_s->global = ft_env(environt, env_s);
	ctrlc = ft_malloc(sizeof(struct sigaction), 0);
	env_s->signal = ctrlc;
	ctrlc->sa_handler = manage_ctrlc;
	sigemptyset(&ctrlc->sa_mask);
	ctrlc->sa_flags = SA_RESTART;
	sigaction(SIGINT, ctrlc, NULL);
	signal(SIGQUIT, SIG_IGN);
	prompt_loop(env_s);
	return (0);
}
