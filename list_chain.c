st_chain.c
—--------------------------------------------
 #include "main.h"
 
/**
   * check_list_chain - checks to continue chaining based on previous status
    * @info: parameter struct
     * @buff: char buffer
      * @curr_pos: address of current position in buf
       * @index: starting position in buff
        * @length: length of buff
	 *
	  * Return: nothing
	   */
void check_list_chain(info_t *info, char *buff, size_t *curr_pos,
		size_t index, size_t length)
{
	           	size_t i = *curr_pos;
			 
			           	if (info->cmd_buff_type == AND_CMD)
						           	{
									                          	if (info->status)
														                          	{
																			                                         	buff[index] = 0;
																									                                         	i = length;
																															                          	}
													           	}
					 
					           	if (info->cmd_buff_type == OR_CMD)
								           	{
											                          	if (!info->status)
																                          	{
																					                                         	buff[index] = 0;
																											                                         	i = length;
																																	                          	}
															           	}
							 
							           	*curr_pos = i;
}
 
/**
   * is_list_chain - checks if current char in buffer is a chain delimeter
    * @info: parameter struct
     * @buff: char buffer
      * @curr_pos: address of current position in buf
       *
        * Return: 1 if chain delimeter and 0 otherwise
	 */
int is_list_chain(info_t *info, char *buff, size_t *curr_pos)
{
	           	size_t i = *curr_pos;
			 
			           	if (buff[i] == '|' && buff[i + 1] == '|')
						           	{
									                          	buff[i] = 0;
													                          	i++;
																	                          	info->cmd_buff_type = OR_CMD;
																					           	}
					           	else if (buff[i] == '&' && buff[i + 1] == '&')
								           	{
											                          	buff[i] = 0;
															                          	i++;
																			                          	info->cmd_buff_type = AND_CMD;
																							           	}
							           	else if (buff[i] == ';') /* found end of this command */
										           	{
													                          	buff[i] = 0; /* replace semicolon with null */
																	                          	info->cmd_buff_type = CHAIN_CMD;
																					           	}
									           	else
												           	{
															                          	return (0);
																			           	}
											 
											           	*curr_pos = i;
													 
													           	return (1);
}
 
/**
   * repl_alias - replaces alias in tokenized string
    * @info: parameter struct
     *
      * Return: 1 if replaced successfully and 0 otherwise
       */
int repl_alias(info_t *info)
{
	           	list_t *list;
			           	char *a;
					           	int i;
							 
							           	for (i = 0; i < 10; i++)
										           	{
													                          	list = node_prefix(info->alias, info->argv[0], '=');
																	                          	if (!list)
																						                                         	return (0);
																					 
																					                          	free(info->argv[0]);
																									                          	a = _strchr(list->dir, '=');
																													                          	if (!a)
																																		                                         	return (0);
																																	                          	a = _strdup(a + 1);
																																					                          	if (!a)
																																										                                         	return (0);
																																									 
																																									                          	info->argv[0] = a;
																																													           	}
									 
									           	return (1);
}
 
/**
   * repl_variable - replaces variables in tokenized string
    * @info: parameter struct
     *
      * Return: 1 if replaced successfully and 0 otherwise
       */
int repl_variable(info_t *info)
{
	           	int i = 0;
			           	list_t *list;
					 
					           	for (i = 0; info->argv[i]; i++)
								           	{
											                          	if (info->argv[i][0] != '$' || !info->argv[i][1])
																                                         	continue;
															                          	if (!_strcmp(info->argv[i], "$?"))
																				                          	{
																									                                         	replace_str(&(info->argv[i]),
																																	                                                        	_strdup(convert_num(info->status, 10, 0)));
																															                                         	continue;
																																					                          	}
																			                          	if (!_strcmp(info->argv[i], "$$"))
																								                          	{
																													                                         	replace_str(&(info->argv[i]),
																																					                                                        	_strdup(convert_num(getpid(), 10, 0)));
																																			                                         	continue;
																																									                          	}
																							                          	list = node_prefix(info->env, &info->argv[i][1], '=');
																											                          	if (list)
																																                          	{
																																					                                         	replace_str(&(info->argv[i]),
																																													                                                        	_strdup(_strchr(list->dir, '=') + 1));
																																											                                         	continue;
																																																	                          	}
																															                          	replace_str(&info->argv[i], _strdup(""));
																																			           	}
							 
							           	return (0);
}


