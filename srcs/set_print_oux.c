/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:49:22 by saxiao            #+#    #+#             */
/*   Updated: 2017/12/16 02:02:52 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include "../libft/libft.h"
#include "../includes/ft_printf.h"

static	void	set_oxu(t_data *data, char *pre_fix)
{
	if (data->precison == -1)
		data->no_pre = 1;
	if (data->precison < (int)ft_strlen(data->ori))
		data->precison = ft_strlen(data->ori);
	if (data->ori[0] != '0' && ft_strchr(data->flags, '#'))
	{
		data->len = max_3(data->width, ft_strlen(data->ori) + ft_strlen(pre_fix), data->precison);
		data->blank = data->len - data->precison - ft_strlen(pre_fix);
	}
	else
	{
		data->len = max_3(data->width, ft_strlen(data->ori), data->precison);
		data->blank = data->len - data->precison;
	}
}

static	void	go_right(t_data *data, char *pre_fix)
{
	if (!ft_strchr(data->flags, '-'))
	{
		if (ft_strchr(data->flags, '#') && data->no_pre)
		{
			if (ft_strchr(data->flags, '0'))
			{
			ft_putstr(pre_fix);
			ft_putnchar('0', data->len - ft_strlen(pre_fix) - ft_strlen(data->ori));
			ft_putstr(data->ori);
			}
			else
			{
			ft_putnchar(' ', data->len - ft_strlen(pre_fix) - ft_strlen(data->ori));
			ft_putstr(pre_fix);
			ft_putstr(data->ori);
			}
		}
		else
		{
			ft_putnchar(' ', data->blank);
			if (ft_strchr(data->flags, '#'))
				ft_putstr(pre_fix);
			ft_putnchar('0', data->precison - ft_strlen(data->ori));
			ft_putstr(data->ori);
		}
	}
}

static	void	put_zero(t_data *data)
{
	if (data->no_pre)
		ft_putnchar('0', data->len);
	else
		ft_putnchar(' ', data->len);
}

void	set_print_oxu_hash(t_data *data, char *pre_fix)
{
	set_oxu(data, pre_fix);
	if (!(!data->len && data->ori[0] == '0'))
	{
		if (data->ori[0] == '0')
			put_zero(data);
		else
		{
			if (!ft_strchr(data->flags, '-'))
				go_right(data, pre_fix);
			else
			{
				if (ft_strchr(data->flags, '#'))
					ft_putstr(pre_fix);
				ft_putnchar('0', data->precison - ft_strlen(data->ori));
				ft_putstr(data->ori);
				ft_putnchar(' ', data->blank);
			}
		}
	}
	else
	{
		data->len = 0;
		if (ft_strchr(data->flags, '#') && pre_fix[0] == 'o')
		ft_putchar('0');
	}
}
