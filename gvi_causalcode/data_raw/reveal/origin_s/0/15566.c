static void initialize_readline ( char * name ) {
 rl_readline_name = name ;

 rl_completion_entry_function = ( rl_compentry_func_t * ) & no_completion ;
 rl_add_defun ( "magic-space" , ( rl_command_func_t * ) & fake_magic_space , - 1 ) ;


 rl_completion_entry_function = & no_completion ;
 rl_add_defun ( "magic-space" , ( Function * ) & fake_magic_space , - 1 ) ;

 rl_completion_entry_function = & no_completion ;
