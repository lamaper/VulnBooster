static const char * cmd_sensor_id ( cmd_parms * cmd , void * _dcfg , const char * p1 ) {
 directory_config * dcfg = ( directory_config * ) _dcfg ;
 dcfg -> sensor_id = p1 ;
 return NULL ;
 }