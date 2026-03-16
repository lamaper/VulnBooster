static const char * cmd_request_encoding ( cmd_parms * cmd , void * _dcfg , const char * p1 ) {
 directory_config * dcfg = ( directory_config * ) _dcfg ;
 if ( dcfg == NULL ) return NULL ;
 dcfg -> request_encoding = p1 ;
 return NULL ;
 }