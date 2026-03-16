static off_t dnsname_to_labels ( u8 * const buf , size_t buf_len , off_t j , const char * name , const int name_len , struct dnslabel_table * table ) {
 const char * end = name + name_len ;
 int ref = 0 ;
 u16 _t ;

 if ( j + 2 > ( off_t ) buf_len ) goto overflow ;
 _t = htons ( x ) ;
 memcpy ( buf + j , & _t , 2 ) ;
 j += 2 ;
 }
 while ( 0 ) # define APPEND32 ( x ) do {
 if ( j + 4 > ( off_t ) buf_len ) goto overflow ;
 _t32 = htonl ( x ) ;
 memcpy ( buf + j , & _t32 , 4 ) ;
 j += 4 ;
 }
 while ( 0 ) if ( name_len > 255 ) return - 2 ;
 for ( ;
 ;
 ) {
 const char * const start = name ;
 if ( table && ( ref = dnslabel_table_get_pos ( table , name ) ) >= 0 ) {
 APPEND16 ( ref | 0xc000 ) ;
 return j ;
 }
 name = strchr ( name , '.' ) ;
 if ( ! name ) {
 const unsigned int label_len = end - start ;
 if ( label_len > 63 ) return - 1 ;
 if ( ( size_t ) ( j + label_len + 1 ) > buf_len ) return - 2 ;
 if ( table ) dnslabel_table_add ( table , start , j ) ;
 buf [ j ++ ] = label_len ;
 memcpy ( buf + j , start , end - start ) ;
 j += end - start ;
 break ;
 }
 else {
 const unsigned int label_len = name - start ;
 if ( label_len > 63 ) return - 1 ;
 if ( ( size_t ) ( j + label_len + 1 ) > buf_len ) return - 2 ;
 if ( table ) dnslabel_table_add ( table , start , j ) ;
 buf [ j ++ ] = label_len ;
 memcpy ( buf + j , start , name - start ) ;
 j += name - start ;
 name ++ ;
 }
 }
 if ( ! j || buf [ j - 1 ] ) buf [ j ++ ] = 0 ;
 return j ;
 overflow : return ( - 2 ) ;
 }