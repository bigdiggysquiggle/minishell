/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 16:10:56 by dromansk          #+#    #+#             */
/*   Updated: 2019/06/25 16:55:05 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*read_cmd(void)
{
	char	*cmds
	char	red[BUFF_SIZE + 1];
	int		ret;

	cmds = ft_strnew(0);
	while ((ret = read(fd, red, BUFF_SIZE)) > 0)
	{
		red[ret] = '\0';
		cmds = swap_n_free(ft_strjoin(cmds, red), &cmds);
	}
	if (ret < 0)
	{
		free(cmds);
		cmd_read_error(errno);
	}
	return (cmds);
}

t_com	*split_cmds(t_com *com, char *cmds)
{
	char	**coms1;
	char	**coms2;
	char	*strip;
	int		i;

	i = 0;
	strip = ft_strtrim(cmds);
	strip = swap_n_free(ft_strwht(strip), &strip);
	coms1 = ft_strsplit(strip, ' ');
	com->cmd = coms1[0];
	while (coms[i])
		i++;
	coms2 = (char **)malloc(sizeof(char *) * i);
	i = -1;
	while (coms1[++i + 1])
		coms2[i] = coms1[i + 1];
	coms2[i] = NULL;
	com->args = coms2;
	free(coms1);
	return (com);
}

t_com	*get_cmd(void)
{
	t_com	*com;
	char	*cmds;

	com = (t_com *)malloc(sizeof(t_com));
	cmds = read_cmd();
	return (split_cmds(com, cmds));
}

int		main(void)
{

}
