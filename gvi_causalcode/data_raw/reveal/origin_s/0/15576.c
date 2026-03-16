static const char * cmd_rule_script ( cmd_parms * cmd , void * _dcfg , const char * p1 , const char * p2 ) {

 return add_rule ( cmd , ( directory_config * ) _dcfg , RULE_TYPE_LUA , filename , p2 , NULL ) ;

 return NULL ;
