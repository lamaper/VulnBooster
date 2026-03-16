static struct rule * find_config_line ( struct config * config , char * command , char * subcommand ) {
 size_t i ;
 for ( i = 0 ;
 i < config -> count ;
 i ++ ) if ( line_matches ( config -> rules [ i ] , command , subcommand ) ) return config -> rules [ i ] ;
 return NULL ;
 }