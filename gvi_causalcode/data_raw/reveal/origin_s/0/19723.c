static void net_init_slirp_configs ( const StringList * fwd , int flags ) {
 while ( fwd ) {
 struct slirp_config_str * config ;
 config = g_malloc0 ( sizeof ( * config ) ) ;
 pstrcpy ( config -> str , sizeof ( config -> str ) , fwd -> value -> str ) ;
 config -> flags = flags ;
 config -> next = slirp_configs ;
 slirp_configs = config ;
 fwd = fwd -> next ;
 }
 }