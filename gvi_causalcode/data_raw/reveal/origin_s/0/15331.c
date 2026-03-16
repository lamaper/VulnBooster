int reg_replace ( char * * buf_p , int * buf_len_p , char * pattern , char * replace , char * string , int icase ) {
 my_regex_t r ;
 my_regmatch_t * subs ;
 char * replace_end ;
 char * buf = * buf_p ;
 int len ;
 int buf_len , need_buf_len ;
 int cflags = REG_EXTENDED ;
 int err_code ;
 char * res_p , * str_p , * str_end ;
 buf_len = * buf_len_p ;
 len = strlen ( string ) ;
 str_end = string + len ;
 need_buf_len = len * 2 + 1 ;
 res_p = buf ;
 SECURE_REG_BUF if ( icase ) cflags |= REG_ICASE ;
 if ( ( err_code = my_regcomp ( & r , pattern , cflags , & my_charset_latin1 ) ) ) {
 check_regerr ( & r , err_code ) ;
 return 1 ;
 }
 subs = ( my_regmatch_t * ) my_malloc ( sizeof ( my_regmatch_t ) * ( r . re_nsub + 1 ) , MYF ( MY_WME + MY_FAE ) ) ;
 * res_p = 0 ;
 str_p = string ;
 replace_end = replace + strlen ( replace ) ;
 while ( ! err_code ) {
 err_code = my_regexec ( & r , str_p , r . re_nsub + 1 , subs , ( str_p == string ) ? REG_NOTBOL : 0 ) ;
 if ( err_code && err_code != REG_NOMATCH ) {
 check_regerr ( & r , err_code ) ;
 my_regfree ( & r ) ;
 return 1 ;
 }
 if ( ! err_code ) {
 char * expr_p = replace ;
 int c ;
 need_buf_len = ( res_p - buf ) + ( int ) subs [ 0 ] . rm_so ;
 while ( expr_p < replace_end ) {
 int back_ref_num = - 1 ;
 c = * expr_p ;
 if ( c == '\\' && expr_p + 1 < replace_end ) {
 back_ref_num = ( int ) ( expr_p [ 1 ] - '0' ) ;
 }
 if ( back_ref_num >= 0 && back_ref_num <= ( int ) r . re_nsub ) {
 regoff_t start_off , end_off ;
 if ( ( start_off = subs [ back_ref_num ] . rm_so ) > - 1 && ( end_off = subs [ back_ref_num ] . rm_eo ) > - 1 ) {
 need_buf_len += ( int ) ( end_off - start_off ) ;
 }
 expr_p += 2 ;
 }
 else {
 expr_p ++ ;
 need_buf_len ++ ;
 }
 }
 need_buf_len ++ ;
 SECURE_REG_BUF if ( subs [ 0 ] . rm_so ) {
 memcpy ( res_p , str_p , ( size_t ) subs [ 0 ] . rm_so ) ;
 res_p += subs [ 0 ] . rm_so ;
 }
 expr_p = replace ;
 while ( expr_p < replace_end ) {
 int back_ref_num = - 1 ;
 c = * expr_p ;
 if ( c == '\\' && expr_p + 1 < replace_end ) {
 back_ref_num = expr_p [ 1 ] - '0' ;
 }
 if ( back_ref_num >= 0 && back_ref_num <= ( int ) r . re_nsub ) {
 regoff_t start_off , end_off ;
 if ( ( start_off = subs [ back_ref_num ] . rm_so ) > - 1 && ( end_off = subs [ back_ref_num ] . rm_eo ) > - 1 ) {
 int block_len = ( int ) ( end_off - start_off ) ;
 memcpy ( res_p , str_p + start_off , block_len ) ;
 res_p += block_len ;
 }
 expr_p += 2 ;
 }
 else {
 * res_p ++ = * expr_p ++ ;
 }
 }
 if ( subs [ 0 ] . rm_so == subs [ 0 ] . rm_eo ) {
 if ( str_p + subs [ 0 ] . rm_so >= str_end ) break ;
 str_p += subs [ 0 ] . rm_eo ;
 * res_p ++ = * str_p ++ ;
 }
 else {
 str_p += subs [ 0 ] . rm_eo ;
 }
 }
 else {
 int left_in_str = str_end - str_p ;
 need_buf_len = ( res_p - buf ) + left_in_str ;
 SECURE_REG_BUF memcpy ( res_p , str_p , left_in_str ) ;
 res_p += left_in_str ;
 str_p = str_end ;
 }
 }
 my_free ( subs ) ;
 my_regfree ( & r ) ;
 * res_p = 0 ;
 * buf_p = buf ;
 * buf_len_p = buf_len ;
 return 0 ;
 }