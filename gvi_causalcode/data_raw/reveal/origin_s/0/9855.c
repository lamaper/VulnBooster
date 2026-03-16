static ngx_int_t parse_status_line ( ngx_http_request_t * r , passenger_context_t * context ) {
 u_char ch ;
 u_char * pos ;
 ngx_http_upstream_t * u ;
 enum {
 sw_start = 0 , sw_H , sw_HT , sw_HTT , sw_HTTP , sw_first_major_digit , sw_major_digit , sw_first_minor_digit , sw_minor_digit , sw_status , sw_space_after_status , sw_status_text , sw_almost_done }
 state ;
 u = r -> upstream ;
 state = r -> state ;
 for ( pos = u -> buffer . pos ;
 pos < u -> buffer . last ;
 pos ++ ) {
 ch = * pos ;
 switch ( state ) {
 case sw_start : switch ( ch ) {
 case 'H' : state = sw_H ;
 break ;
 default : return NGX_HTTP_SCGI_PARSE_NO_HEADER ;
 }
 break ;
 case sw_H : switch ( ch ) {
 case 'T' : state = sw_HT ;
 break ;
 default : return NGX_HTTP_SCGI_PARSE_NO_HEADER ;
 }
 break ;
 case sw_HT : switch ( ch ) {
 case 'T' : state = sw_HTT ;
 break ;
 default : return NGX_HTTP_SCGI_PARSE_NO_HEADER ;
 }
 break ;
 case sw_HTT : switch ( ch ) {
 case 'P' : state = sw_HTTP ;
 break ;
 default : return NGX_HTTP_SCGI_PARSE_NO_HEADER ;
 }
 break ;
 case sw_HTTP : switch ( ch ) {
 case '/' : state = sw_first_major_digit ;
 break ;
 default : return NGX_HTTP_SCGI_PARSE_NO_HEADER ;
 }
 break ;
 case sw_first_major_digit : if ( ch < '1' || ch > '9' ) {
 return NGX_HTTP_SCGI_PARSE_NO_HEADER ;
 }
 state = sw_major_digit ;
 break ;
 case sw_major_digit : if ( ch == '.' ) {
 state = sw_first_minor_digit ;
 break ;
 }
 if ( ch < '0' || ch > '9' ) {
 return NGX_HTTP_SCGI_PARSE_NO_HEADER ;
 }
 break ;
 case sw_first_minor_digit : if ( ch < '0' || ch > '9' ) {
 return NGX_HTTP_SCGI_PARSE_NO_HEADER ;
 }
 state = sw_minor_digit ;
 break ;
 case sw_minor_digit : if ( ch == ' ' ) {
 state = sw_status ;
 break ;
 }
 if ( ch < '0' || ch > '9' ) {
 return NGX_HTTP_SCGI_PARSE_NO_HEADER ;
 }
 break ;
 case sw_status : if ( ch == ' ' ) {
 break ;
 }
 if ( ch < '0' || ch > '9' ) {
 return NGX_HTTP_SCGI_PARSE_NO_HEADER ;
 }
 context -> status = context -> status * 10 + ch - '0' ;
 if ( ++ context -> status_count == 3 ) {
 state = sw_space_after_status ;
 context -> status_start = pos - 2 ;
 }
 break ;
 case sw_space_after_status : switch ( ch ) {
 case ' ' : state = sw_status_text ;
 break ;
 case '.' : state = sw_status_text ;
 break ;
 case CR : state = sw_almost_done ;
 break ;
 case LF : goto done ;
 default : return NGX_HTTP_SCGI_PARSE_NO_HEADER ;
 }
 break ;
 case sw_status_text : switch ( ch ) {
 case CR : state = sw_almost_done ;
 break ;
 case LF : goto done ;
 }
 break ;
 case sw_almost_done : context -> status_end = pos - 1 ;
 switch ( ch ) {
 case LF : goto done ;
 default : return NGX_HTTP_SCGI_PARSE_NO_HEADER ;
 }
 }
 }
 u -> buffer . pos = pos ;
 r -> state = state ;
 return NGX_AGAIN ;
 done : u -> buffer . pos = pos + 1 ;
 if ( context -> status_end == NULL ) {
 context -> status_end = pos ;
 }
 r -> state = sw_start ;
 return NGX_OK ;
 }