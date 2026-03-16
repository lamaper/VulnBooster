static void config_destroy_func ( void * data ) {
 ConfigData * config = ( ConfigData * ) data ;
 TSfree ( config ) ;
 return ;
 }