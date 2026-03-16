static const char * cmd_collection_timeout ( cmd_parms * cmd , void * _dcfg , const char * p1 ) {
 directory_config * dcfg = ( directory_config * ) _dcfg ;
 dcfg -> col_timeout = atoi ( p1 ) ;
 if ( ( dcfg -> col_timeout >= 0 ) && ( dcfg -> col_timeout <= 2592000 ) ) return NULL ;
 return apr_psprintf ( cmd -> pool , "ModSecurity: Invalid value for SecCollectionTimeout: %s" , p1 ) ;
 }