static void search_set_from_hostname ( void ) {
 char hostname [ HOST_NAME_MAX + 1 ] , * domainname ;
 search_postfix_clear ( ) ;
 if ( gethostname ( hostname , sizeof ( hostname ) ) ) return ;
 domainname = strchr ( hostname , '.' ) ;
 if ( ! domainname ) return ;
 search_postfix_add ( domainname ) ;
 }