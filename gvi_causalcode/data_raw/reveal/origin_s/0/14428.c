static size_t my_setstacksize ( pthread_attr_t * attr , size_t stacksize ) {
 size_t guard_size __attribute__ ( ( unused ) ) = 0 ;




 size_t real_stack_size = 0 ;
 if ( pthread_attr_getstacksize ( attr , & real_stack_size ) == 0 && real_stack_size > guard_size ) {
 real_stack_size -= guard_size ;
 if ( real_stack_size < stacksize ) {
 if ( global_system_variables . log_warnings ) sql_print_warning ( "Asked for %zu thread stack, but got %zu" , stacksize , real_stack_size ) ;
 stacksize = real_stack_size ;
 }
 }
 }


 }