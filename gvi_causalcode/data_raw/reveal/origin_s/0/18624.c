static int _nss_nis_parse_aliasent ( const char * key , char * alias , struct aliasent * result , char * buffer , size_t buflen , int * errnop ) {
 char * first_unused = buffer + strlen ( alias ) + 1 ;
 size_t room_left = buflen - ( buflen % __alignof__ ( char * ) ) - strlen ( alias ) - 2 ;
 char * line ;
 char * cp ;
 result -> alias_members_len = 0 ;
 * first_unused = '\0' ;
 first_unused ++ ;
 strcpy ( first_unused , key ) ;
 if ( first_unused [ room_left - 1 ] != '\0' ) {
 no_more_room : * errnop = ERANGE ;
 return - 1 ;
 }
 result -> alias_name = first_unused ;
 cp = strpbrk ( alias , "#\n" ) ;
 if ( cp != NULL ) * cp = '\0' ;
 first_unused += strlen ( result -> alias_name ) + 1 ;
 first_unused += __alignof__ ( char * ) - 1 ;
 first_unused -= ( ( first_unused - ( char * ) 0 ) % __alignof__ ( char * ) ) ;
 result -> alias_members = ( char * * ) first_unused ;
 line = alias ;
 while ( * line != '\0' ) {
 while ( isspace ( * line ) ) line ++ ;
 if ( * line == '\0' ) break ;
 if ( room_left < sizeof ( char * ) ) goto no_more_room ;
 room_left -= sizeof ( char * ) ;
 result -> alias_members [ result -> alias_members_len ] = line ;
 while ( * line != '\0' && * line != ',' ) line ++ ;
 if ( line != result -> alias_members [ result -> alias_members_len ] ) {
 * line = '\0' ;
 line ++ ;
 result -> alias_members_len ++ ;
 }
 }
 return result -> alias_members_len == 0 ? 0 : 1 ;
 }