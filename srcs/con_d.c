/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:49:22 by saxiao            #+#    #+#             */
/*   Updated: 2017/12/19 10:40:05 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include "../libft/libft.h"
#include "../includes/ft_printf.h"

static	void	cast_nu_d(va_list args, t_data *data, char *format, int size)
{
	set_cast(data, format, size);
	if (data->cast == z)
		data->ori = ft_itoa_max(va_arg(args, size_t));
	else	if (data->cast == none)
		data->ori = ft_itoa(va_arg(args, int));
	else	if (data->cast == hh)
		data->ori = ft_itoa_signchar(va_arg(args, int));
	else	if (data->cast == h)
		data->ori = ft_itoa_short(va_arg(args, int));
	else	if (data->cast == l)
		data->ori = ft_itoa_max(va_arg(args,long int));
	else	if (data->cast == ll)
		data->ori = ft_itoa_max(va_arg(args, long long int));
	else	if (data->cast == j)
		data->ori = ft_itoa_max(va_arg(args, intmax_t));
}
/*
   static	void	set_d(t_data *data)
   {
   if (data->precison == -1)
   data->no_pre = 1;
   if (!(data->ori[0] == '0' && !data->precison) && data->precison < (int)ft_strlen(data->ori))
   data->precison = ft_strlen(data->ori);
   if ((ft_strchr(data->flags, '+') || ft_strchr(data->flags, ' ')) && !(!data->ori[0] && !data->precison) && data->ori[0] != '-')
   {
   data->len = max_3(data->width, ft_strlen(data->ori) + 1, data->precison);
   data->blank = data->len - data->precison - 1;
   }
   else
   {
   if (!(data->ori[0] == '0' && !data->precison))
   {
   data->len = max_3(data->width, ft_strlen(data->ori), data->precison);
   data->blank = data->len - data->precison;
   }
   }
   }
   */
static	void	set_d(t_data *data)
{
	if (data->precison == -1)
		data->no_pre = 1;
	if (!(data->ori[0] == '0' && !data->precison))
	{
		if (data->ori[0] != '-' && data->precison < (int)ft_strlen(data->ori))

			data->precison = ft_strlen(data->ori);
		else if (data->ori[0] == '-' && data->precison < (int)ft_strlen(data->ori) -1)
			data->precison = ft_strlen(data->ori) - 1;
	}
	if (!(data->ori[0] == '0' && !data->precison))
	{
		if (data->ori[0] != '-')
		{
			data->len = max_3(data->width, ft_strlen(data->ori), data->precison);
			data->blank = data->len - data->precison;
			if (ft_strchr(data->flags, ' ') || ft_strchr(data->flags, '+'))
			{
				if (data->len == data->precison)
					data->len++;
				else
					data->blank--;
			}
		}
		else
		{
			data->len = max_2(data->width, data->precison);
			data->blank = data->len - data->precison;
			if (data->len == (int)ft_strlen(data->ori) - 1)
				data->len++;
			else
				data->blank--;
		}
	}
	else
		data->len = data->width;
}

static	void	plus_blank(t_data *data)
{
	if (data->ori[0] != '-')
	{
		if (ft_strchr(data->flags, '+'))
			ft_putchar('+');
		else if (ft_strchr(data->flags, ' '))
			ft_putchar(' ');
	}
	else
		ft_putchar('-');
}

static	void	go_right(t_data *data)
{
	if (ft_strchr(data->flags, '0') && data->no_pre)
	{
		plus_blank(data);
		ft_putnchar('0', data->blank);
		if (data->ori[0] == '-')
			ft_putstr(data->ori + 1);
		else
			ft_putstr(data->ori);

	}
	else
	{
		ft_putnchar(' ', data->blank);
		plus_blank(data);
		if (data->ori[0] == '-')
		{
			ft_putnchar('0', data->precison - ft_strlen(data->ori) + 1);
			ft_putstr(data->ori + 1);
		}
		else
		{
			ft_putnchar('0', data->precison - ft_strlen(data->ori));
			ft_putstr(data->ori);
		}
	}
}

static	void	put_zero(t_data *data)
{
	if (ft_strchr(data->flags, '0') && data->no_pre)
	{
		if (ft_strchr(data->flags, '+'))
		{
			ft_putchar('+');
			ft_putnchar('0', data->len - 2);
		}
		else if (ft_strchr(data->flags, ' '))
		{
			ft_putchar(' ');
			ft_putnchar('0', data->len - 2);
		}
		else
			ft_putnchar('0', data->len - 1);
		ft_putchar('0');
	}
	else
	{
		if (ft_strchr(data->flags, '+'))
		{
			ft_putchar('+');
			data->blank = data->len - 1;
		}
		else if (ft_strchr(data->flags, ' '))
		{
			ft_putchar(' ');
			data->blank = data->len - 1;
		}
		else
		data->blank = data->len;
		ft_putnchar(' ', data->blank);
	}
}




static	void	set_print_d(t_data *data)
{
	set_d(data);
	//if (!((data->precison == 0 && data->ori[0] == '0') && !ft_strchr(data->flags, ' ') && !ft_strchr(data->flags, '+')))
	if (data->len && !(data->ori[0] == '0' && !data->precison))
	{
		/*if (data->ori[0] == '0' && !data->precison)
		  plus_blank(data);
		  else
		  {
		  */
		if (!ft_strchr(data->flags, '-'))
			go_right(data);
		else
		{
			plus_blank(data);
			if (data->ori[0] == '-')
				ft_putnchar('0', data->precison - ft_strlen(data->ori) + 1);
			else
				ft_putnchar('0', data->precison - ft_strlen(data->ori));
			if (data->ori[0] == '-')
				ft_putstr(data->ori + 1);
			else
				ft_putstr(data->ori);
			ft_putnchar(' ', data->blank);
		}
	}
	else if (data->len && data->ori[0] == '0')
		put_zero(data);
}

void	con_d(va_list args, t_data *data, char *format, int size)
{
	cast_nu_d(args, data, format, size);
	set_flags(data, format, size);
	set_print_d(data);
}

void	con_D(va_list args, t_data *data, char *format, int size)
{
	set_cast(data, format, size);
	data->ori = ft_itoa_max(va_arg(args,long int));
	set_flags(data, format, size);
	set_print_d(data);
}
