static int _find_update_object_in_list ( void * x , void * key ) {
 slurmdb_update_object_t * object = ( slurmdb_update_object_t * ) x ;
 slurmdb_update_type_t type = * ( slurmdb_update_type_t * ) key ;
 if ( object -> type == type ) return 1 ;
 return 0 ;
 }