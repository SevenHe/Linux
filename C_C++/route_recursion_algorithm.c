#include<stdio.h>

void iterate_next_node(int node, int end, int** &links, int* result_node, int current_cost, int level,
		int* v_sub, int v_sub_length, int max_length, int has_v_sub_num, int* &final_result)
{
	int i = 0;
	// avoid getting the end before iteration completion
	if(level < max_length && node == end) return;
	// if having duplicate nodes
	for( ; i<max_length; i++)
	{
		if(result_node[i] == node)
			return;
		else if(result_node[i] == -1)
			break;
	}
	// if node is in v_sub, count + 1
	if(exists_in_v_sub(node, v_sub, v_sub_length)) has_v_sub_num ++;
	// then add a new node
	result_node[level] = node;
	// iteration exit
	if(has_v_sub_num == v_sub_length && links[node][end] != 0)
	{
		result_node[level+1] = end;
		current_cost += links[node][end];
		if(lowest_cost == 0)
		{
			lowest_cost = current_cost; 
			memcpy(final_result, result_node, sizeof(int)*max_length);
			return;
		}   
		else if(lowest_cost != 0 && current_cost < lowest_cost)
		{
			lowest_cost = current_cost;
			memcpy(final_result, result_node, sizeof(int)*max_length);
			return;
		}   
	}   
	else if(has_v_sub_num < v_sub_length && level < max_length)
	{
		int index = -1;
		while((index = get_next_child(links[node], index, max_length)) != -1)
		{
			//  clean the result_node influence due to the last final_result assignment
			if(result_node[level+1] != -1)
				memset(result_node+(level+1), -1, sizeof(int)*(max_length-level+1));
			iterate_next_node(index, end, links, result_node, current_cost+links[node][index], level+1,
					v_sub, v_sub_length, max_length, has_v_sub_num, final_result);
		}
	}
}

