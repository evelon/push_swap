/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_simulator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:15:23 by jolim             #+#    #+#             */
/*   Updated: 2021/03/19 16:59:0 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ps_split_a_third(int big_pivot_value, int small_pivot_value, \
int *n_ra, int *n_rb)
{
	t_two_stacks	*two_stacks;

	two_stacks = *get_two_stacks();
	if (two_stacks->a_top->element >= big_pivot_value)
		*n_ra += ps_register_operation(so_ra); // 3
	else
	{
		ps_register_operation(so_pb); // 2 + 1
		if (two_stacks->b_top->element >= small_pivot_value)
		{
			(*n_rb)++;
			// if (two_stacks->b_top->down_node != two_stacks->b_top)
				ps_register_operation(so_rb); // 2
		}
	}
}

void	ps_sort_split_a(int list[], int top, int bottom)
{
	int				n_ra;
	int				n_rb;
	int				i;

	// usleep(1000000);
	// printf("stackAsize: >>%d %d<<\n\tbig_pivot: %d\t small_pivot: %d\n", bottom, top,list[pivot_big(top, bottom)],list[pivot_small(top,bottom)]);
	// print_ps_two_stacks(*get_two_stacks());
	if (bottom - top < 3)
	{
		ps_sort_below_three(bottom - top, STACK_A);
		return ;
	}
	n_ra = 0;
	n_rb = 0;
	i = -1;
	while (++i < bottom - top)
	{
		ps_split_a_third(list[pivot_big(top, bottom)], \
		list[pivot_small(top, bottom)], &n_ra, &n_rb);
	}
	ps_operate_n_times(min_num(n_ra, n_rb), so_rrr); // 1, 2 to top rrr
	if (n_ra > n_rb)
		ps_register_operation(so_rra);
	else if (n_ra < n_rb)
		ps_register_operation(so_rrb);
	ps_sort_split_a(list, pivot_big(top, bottom), bottom); // sort 3 from a to b
	ps_sort_split_b(list, pivot_small(top, bottom), pivot_big(top, bottom)); // sort 2 from b to a
	ps_sort_split_b(list, top, pivot_small(top, bottom)); // sort 1 from a to b
}

static void	ps_split_b_third(int big_pivot_value, int small_pivot_value, \
int *n_ra, int *n_rb)
{
	t_two_stacks	*two_stacks;

	two_stacks = *get_two_stacks();
	if (two_stacks->b_top->element < small_pivot_value)
		*n_rb += ps_register_operation(so_rb); // 1
	else
	{
		ps_register_operation(so_pa); // 3 + 2
		if (two_stacks->a_top->element < big_pivot_value)
			*n_ra += ps_register_operation(so_ra); // 2
	}
}

void	ps_sort_split_b(int list[], int top, int bottom)
{
	int				n_ra;
	int				n_rb;
	int				i;

	// usleep(1000000);
	// printf("stackBsize: >>%d %d<<\n\tbig_pivot: %d\t small_pivot: %d\n", bottom, top,list[pivot_big(top, bottom)],list[pivot_small(top,bottom)]);
	// print_ps_two_stacks(*get_two_stacks());
	if (bottom - top < 3)
	{
		ps_sort_below_three(bottom - top, STACK_B);
		return ;
	}
	n_ra = 0;
	n_rb = 0;
	i = -1;
	while (++i < bottom - top)
		ps_split_b_third(list[pivot_big(top, bottom)], \
		list[pivot_small(top, bottom)], &n_ra, &n_rb);
	ps_sort_split_a(list, pivot_big(top, bottom), bottom); // 3
	ps_operate_n_times(min_num(n_ra, n_rb), so_rrr);
	if (n_ra > n_rb)
		ps_register_operation(so_rra);
	else if (n_ra < n_rb)
		ps_register_operation(so_rrb);
	ps_sort_split_a(list, pivot_small(top, bottom), pivot_big(top, bottom) ); // 2
	ps_sort_split_b(list, top, pivot_small(top, bottom)); // 1
}