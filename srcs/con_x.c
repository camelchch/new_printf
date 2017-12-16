/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:49:22 by saxiao            #+#    #+#             */
/*   Updated: 2017/12/16 02:02:55 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include "../libft/libft.h"
#include "../includes/ft_printf.h"

static	void	cast_nu_x(va_list args, t_data *data, char *format, int size)
{
	set_cast(data, format, size);
	if (data->cast == z)
		data->ori = itoa_hex(va_arg(args, size_t), 'x');
	else if (data->cast == none || data->cast == hh || data->cast == h)
		data->ori = itoa_hex(va_arg(args, unsigned int), 'x');
	else if (data->cast == l)
		data->ori = itoa_hex(va_arg(args,unsigned long), 'x');
	else if (data->cast == ll)
		data->ori = itoa_hex(va_arg(args, unsigned long long), 'x');
	else if (data->cast == j)
		data->ori = itoa_hex(va_arg(args, uintmax_t), 'x');
}

static	void	cast_nu_X(va_list args, t_data *data, char *format, int size)
{
	set_cast(data, format, size);
	if (data->cast == z)
		data->ori = itoa_hex(va_arg(args, size_t), 'X');
	else if (data->cast == none || data->cast == hh || data->cast == l)
		data->ori = itoa_hex(va_arg(args, unsigned int), 'X');
	else if (data->cast == l)
		data->ori = itoa_hex(va_arg(args,unsigned long), 'X');
	else if (data->cast == ll)
		data->ori = itoa_hex(va_arg(args, unsigned long long), 'X');
	else if (data->cast == j)
		data->ori = itoa_hex(va_arg(args, uintmax_t), 'X');
}

void	con_x(va_list args, t_data *data, char *format, int size)
{
	cast_nu_x(args, data, format, size);
	set_flags(data, format, size);
	set_print_oxu_hash(data, "0x");
}

void	con_XX(va_list args, t_data *data, char *format, int size)
{
	cast_nu_X(args, data, format, size);
	set_flags(data, format, size);
	set_print_oxu_hash(data, "0X");
}
