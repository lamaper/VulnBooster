static int tunnel_dns ( int tun_fd , int dns_fd , int bind_fd ) {
 struct query q ;
 int read ;
 int domain_len ;
 int inside_topdomain = 0 ;
 if ( ( read = read_dns ( dns_fd , tun_fd , & q ) ) <= 0 ) return 0 ;
 if ( debug >= 2 ) {
 fprintf ( stderr , "RX: client %s, type %d, name %s\n" , format_addr ( & q . from , q . fromlen ) , q . type , q . name ) ;
 }
 domain_len = strlen ( q . name ) - strlen ( topdomain ) ;
 if ( domain_len >= 0 && ! strcasecmp ( q . name + domain_len , topdomain ) ) inside_topdomain = 1 ;
 if ( domain_len >= 1 && q . name [ domain_len - 1 ] != '.' ) inside_topdomain = 0 ;
 if ( inside_topdomain ) {
 if ( domain_len == 3 && q . type == T_A && ( q . name [ 0 ] == 'n' || q . name [ 0 ] == 'N' ) && ( q . name [ 1 ] == 's' || q . name [ 1 ] == 'S' ) && q . name [ 2 ] == '.' ) {
 handle_a_request ( dns_fd , & q , 0 ) ;
 return 0 ;
 }
 if ( domain_len == 4 && q . type == T_A && ( q . name [ 0 ] == 'w' || q . name [ 0 ] == 'W' ) && ( q . name [ 1 ] == 'w' || q . name [ 1 ] == 'W' ) && ( q . name [ 2 ] == 'w' || q . name [ 2 ] == 'W' ) && q . name [ 3 ] == '.' ) {
 handle_a_request ( dns_fd , & q , 1 ) ;
 return 0 ;
 }
 switch ( q . type ) {
 case T_NULL : case T_PRIVATE : case T_CNAME : case T_A : case T_MX : case T_SRV : case T_TXT : handle_null_request ( tun_fd , dns_fd , & q , domain_len ) ;
 break ;
 case T_NS : handle_ns_request ( dns_fd , & q ) ;
 break ;
 default : break ;
 }
 }
 else {
 if ( bind_fd ) {
 forward_query ( bind_fd , & q ) ;
 }
 }
 return 0 ;
 }