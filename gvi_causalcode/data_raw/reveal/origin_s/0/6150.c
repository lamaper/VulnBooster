static bool myisam_is_supported_system_table ( const char * db , const char * table_name , bool is_sql_layer_system_table ) {
 if ( is_sql_layer_system_table ) return true ;
 return false ;
 }