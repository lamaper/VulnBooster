libc_hidden_proto ( __printf_fp ) extern unsigned int __guess_grouping ( unsigned int intdig_max , const char * grouping , wchar_t sepchar ) ;
 ssize_t __vstrfmon_l ( char * s , size_t maxsize , __locale_t loc , const char * format , va_list ap ) {
 struct locale_data * current = loc -> __locales [ LC_MONETARY ] ;
 _IO_strfile f ;


 char * dest ;
 const char * fmt ;
 dest = s ;
 fmt = format ;
 while ( * fmt != '\0' ) {
 union {
 double dbl ;
 __long_double_t ldbl ;
 }
 fpnum ;
 int int_format ;
 int print_curr_symbol ;
 int left_prec ;
 int left_pad ;
 int right_prec ;
 int group ;
 char pad ;
 int is_long_double ;
 int p_sign_posn ;
 int n_sign_posn ;
 int sign_posn ;
 int other_sign_posn ;
 int left ;
 int is_negative ;
 int sep_by_space ;
 int other_sep_by_space ;
 int cs_precedes ;
 int other_cs_precedes ;
 const char * sign_string ;
 const char * other_sign_string ;
 int done ;
 const char * currency_symbol ;
 size_t currency_symbol_len ;
 int width ;
 char * startp ;
 const void * ptr ;
 char space_char ;
 if ( * fmt != '%' ) {
 out_char ( * fmt ++ ) ;
 continue ;
 }
 if ( fmt [ 1 ] == '%' ) {
 out_char ( * ++ fmt ) ;
 ++ fmt ;
 continue ;
 }
 int_format = 0 ;
 print_curr_symbol = 1 ;
 left_prec = - 1 ;
 right_prec = - 1 ;
 group = 1 ;
 pad = ' ' ;
 is_long_double = 0 ;
 p_sign_posn = - 1 ;
 n_sign_posn = - 1 ;
 width = - 1 ;
 left = 0 ;
 while ( 1 ) {
 switch ( * ++ fmt ) {
 case '=' : pad = * ++ fmt ;
 if ( pad == '\0' ) {
 __set_errno ( EINVAL ) ;
 return - 1 ;
 }
 continue ;
 case '^' : group = 0 ;
 continue ;
 case '+' : if ( n_sign_posn != - 1 ) {
 __set_errno ( EINVAL ) ;
 return - 1 ;
 }
 p_sign_posn = * _NL_CURRENT ( LC_MONETARY , P_SIGN_POSN ) ;
 n_sign_posn = * _NL_CURRENT ( LC_MONETARY , N_SIGN_POSN ) ;
 continue ;
 case '(' : if ( n_sign_posn != - 1 ) {
 __set_errno ( EINVAL ) ;
 return - 1 ;
 }
 p_sign_posn = 0 ;
 n_sign_posn = 0 ;
 continue ;
 case '!' : print_curr_symbol = 0 ;
 continue ;
 case '-' : left = 1 ;
 continue ;
 default : ;
 }
 break ;
 }
 if ( isdigit ( * fmt ) ) {
 width = to_digit ( * fmt ) ;
 while ( isdigit ( * ++ fmt ) ) {
 width *= 10 ;
 width += to_digit ( * fmt ) ;
 }
 if ( dest + width >= s + maxsize ) {
 __set_errno ( E2BIG ) ;
 return - 1 ;
 }
 }
 if ( * fmt == '#' ) {
 if ( ! isdigit ( * ++ fmt ) ) {
 __set_errno ( EINVAL ) ;
 return - 1 ;
 }
 left_prec = to_digit ( * fmt ) ;
 while ( isdigit ( * ++ fmt ) ) {
 left_prec *= 10 ;
 left_prec += to_digit ( * fmt ) ;
 }
 }
 if ( * fmt == '.' ) {
 if ( ! isdigit ( * ++ fmt ) ) {
 __set_errno ( EINVAL ) ;
 return - 1 ;
 }
 right_prec = to_digit ( * fmt ) ;
 while ( isdigit ( * ++ fmt ) ) {
 right_prec *= 10 ;
 right_prec += to_digit ( * fmt ) ;
 }
 }
 if ( * fmt == 'L' ) {
 ++ fmt ;
 if ( ! __ldbl_is_dbl ) is_long_double = 1 ;
 }
 char int_symbol [ 4 ] ;
 switch ( * fmt ++ ) {
 case 'i' : {
 const char * int_curr_symbol ;
 int_curr_symbol = _NL_CURRENT ( LC_MONETARY , INT_CURR_SYMBOL ) ;
 strncpy ( int_symbol , int_curr_symbol , 3 ) ;
 int_symbol [ 3 ] = '\0' ;
 currency_symbol_len = 3 ;
 currency_symbol = & int_symbol [ 0 ] ;
 space_char = int_curr_symbol [ 3 ] ;
 int_format = 1 ;
 break ;
 }
 case 'n' : currency_symbol = _NL_CURRENT ( LC_MONETARY , CURRENCY_SYMBOL ) ;
 currency_symbol_len = strlen ( currency_symbol ) ;
 space_char = ' ' ;
 int_format = 0 ;
 break ;
 default : __set_errno ( EINVAL ) ;
 return - 1 ;
 }
 if ( p_sign_posn == - 1 ) p_sign_posn = * _NL_CURRENT ( LC_MONETARY , int_format ? INT_P_SIGN_POSN : P_SIGN_POSN ) ;
 if ( n_sign_posn == - 1 ) n_sign_posn = * _NL_CURRENT ( LC_MONETARY , int_format ? INT_N_SIGN_POSN : N_SIGN_POSN ) ;
 if ( right_prec == - 1 ) {
 right_prec = * _NL_CURRENT ( LC_MONETARY , int_format ? INT_FRAC_DIGITS : FRAC_DIGITS ) ;
 if ( right_prec == CHAR_MAX ) right_prec = 2 ;
 }
 if ( group && left_prec != - 1 ) left_prec += __guess_grouping ( left_prec , _NL_CURRENT ( LC_MONETARY , MON_GROUPING ) , * _NL_CURRENT ( LC_MONETARY , MON_THOUSANDS_SEP ) ) ;
 if ( is_long_double == 1 ) {
 fpnum . ldbl = va_arg ( ap , long double ) ;
 is_negative = fpnum . ldbl < 0 ;
 if ( is_negative ) fpnum . ldbl = - fpnum . ldbl ;
 }
 else {
 fpnum . dbl = va_arg ( ap , double ) ;
 is_negative = fpnum . dbl < 0 ;
 if ( is_negative ) fpnum . dbl = - fpnum . dbl ;
 }
 if ( is_negative ) {
 sign_string = _NL_CURRENT ( LC_MONETARY , NEGATIVE_SIGN ) ;
 if ( * sign_string == '\0' ) sign_string = ( const char * ) "-" ;
 cs_precedes = * _NL_CURRENT ( LC_MONETARY , int_format ? INT_N_CS_PRECEDES : N_CS_PRECEDES ) ;
 sep_by_space = * _NL_CURRENT ( LC_MONETARY , int_format ? INT_N_SEP_BY_SPACE : N_SEP_BY_SPACE ) ;
 sign_posn = n_sign_posn ;
 other_sign_string = _NL_CURRENT ( LC_MONETARY , POSITIVE_SIGN ) ;
 other_cs_precedes = * _NL_CURRENT ( LC_MONETARY , int_format ? INT_P_CS_PRECEDES : P_CS_PRECEDES ) ;
 other_sep_by_space = * _NL_CURRENT ( LC_MONETARY , int_format ? INT_P_SEP_BY_SPACE : P_SEP_BY_SPACE ) ;
 other_sign_posn = p_sign_posn ;
 }
 else {
 sign_string = _NL_CURRENT ( LC_MONETARY , POSITIVE_SIGN ) ;
 cs_precedes = * _NL_CURRENT ( LC_MONETARY , int_format ? INT_P_CS_PRECEDES : P_CS_PRECEDES ) ;
 sep_by_space = * _NL_CURRENT ( LC_MONETARY , int_format ? INT_P_SEP_BY_SPACE : P_SEP_BY_SPACE ) ;
 sign_posn = p_sign_posn ;
 other_sign_string = _NL_CURRENT ( LC_MONETARY , NEGATIVE_SIGN ) ;
 if ( * other_sign_string == '\0' ) other_sign_string = ( const char * ) "-" ;
 other_cs_precedes = * _NL_CURRENT ( LC_MONETARY , int_format ? INT_N_CS_PRECEDES : N_CS_PRECEDES ) ;
 other_sep_by_space = * _NL_CURRENT ( LC_MONETARY , int_format ? INT_N_SEP_BY_SPACE : N_SEP_BY_SPACE ) ;
 other_sign_posn = n_sign_posn ;
 }
 if ( cs_precedes != 0 ) cs_precedes = 1 ;
 if ( other_cs_precedes != 0 ) other_cs_precedes = 1 ;
 if ( sep_by_space == CHAR_MAX ) sep_by_space = 0 ;
 if ( other_sep_by_space == CHAR_MAX ) other_sep_by_space = 0 ;
 if ( sign_posn == CHAR_MAX ) sign_posn = 1 ;
 if ( other_sign_posn == CHAR_MAX ) other_sign_posn = 1 ;
 if ( sep_by_space == 2 ) {
 if ( sign_posn == 0 || ( sign_posn == 1 && ! cs_precedes ) || ( sign_posn == 2 && cs_precedes ) ) sep_by_space = 0 ;
 }
 if ( other_sep_by_space == 2 ) {
 if ( other_sign_posn == 0 || ( other_sign_posn == 1 && ! other_cs_precedes ) || ( other_sign_posn == 2 && other_cs_precedes ) ) other_sep_by_space = 0 ;
 }
 if ( left_prec == - 1 ) {
 left_prec = 0 ;
 left_pad = 0 ;
 }
 else {
 int left_bytes = 0 ;
 int other_left_bytes = 0 ;
 if ( cs_precedes ) {
 left_bytes += currency_symbol_len ;
 if ( sep_by_space != 0 ) ++ left_bytes ;
 }
 if ( other_cs_precedes ) {
 other_left_bytes += currency_symbol_len ;
 if ( other_sep_by_space != 0 ) ++ other_left_bytes ;
 }
 if ( sign_posn == 0 && is_negative ) ++ left_bytes ;
 else if ( sign_posn == 1 ) left_bytes += strlen ( sign_string ) ;
 else if ( cs_precedes && ( sign_posn == 3 || sign_posn == 4 ) ) left_bytes += strlen ( sign_string ) ;
 if ( other_sign_posn == 0 && ! is_negative ) ++ other_left_bytes ;
 else if ( other_sign_posn == 1 ) other_left_bytes += strlen ( other_sign_string ) ;
 else if ( other_cs_precedes && ( other_sign_posn == 3 || other_sign_posn == 4 ) ) other_left_bytes += strlen ( other_sign_string ) ;
 if ( other_left_bytes > left_bytes ) left_pad = other_left_bytes - left_bytes ;
 else left_pad = 0 ;
 }

 while ( left_pad -- > 0 ) out_char ( ' ' ) ;
 if ( sign_posn == 0 && is_negative ) out_char ( left_paren ) ;
 if ( cs_precedes ) {
 if ( sign_posn != 0 && sign_posn != 2 && sign_posn != 4 && sign_posn != 5 ) {
 out_string ( sign_string ) ;
 if ( sep_by_space == 2 ) out_char ( ' ' ) ;
 }
 if ( print_curr_symbol ) out_string ( currency_symbol ) ;
 if ( sign_posn == 4 ) {
 if ( print_curr_symbol && sep_by_space == 2 ) out_char ( space_char ) ;
 out_string ( sign_string ) ;
 if ( sep_by_space == 1 ) out_char ( ' ' ) ;
 }
 else if ( print_curr_symbol && sep_by_space == 1 ) out_char ( space_char ) ;
 }
 else if ( sign_posn != 0 && sign_posn != 2 && sign_posn != 3 && sign_posn != 4 && sign_posn != 5 ) out_string ( sign_string ) ;


 _IO_JUMPS ( ( struct _IO_FILE_plus * ) & f ) = & _IO_str_jumps ;
 INTUSE ( _IO_str_init_static ) ( ( _IO_strfile * ) & f , dest , ( s + maxsize ) - dest , dest ) ;
 s [ maxsize - 1 ] = '\0' ;
 memset ( & info , '\0' , sizeof ( info ) ) ;
 info . prec = right_prec ;
 info . width = left_prec + ( right_prec ? ( right_prec + 1 ) : 0 ) ;
 info . spec = 'f' ;
 info . is_long_double = is_long_double ;
 info . group = group ;
 info . pad = pad ;
 info . extra = 1 ;
 ptr = & fpnum ;
 done = __printf_fp ( ( FILE * ) & f , & info , & ptr ) ;
 if ( done < 0 ) return - 1 ;
 if ( s [ maxsize - 1 ] != '\0' ) {
 __set_errno ( E2BIG ) ;
 return - 1 ;
 }
 dest += done ;
 if ( ! cs_precedes ) {
 if ( sign_posn == 3 ) {
 if ( sep_by_space == 1 ) out_char ( ' ' ) ;
 out_string ( sign_string ) ;
 }
 if ( print_curr_symbol ) {
 if ( ( sign_posn == 3 && sep_by_space == 2 ) || ( sign_posn == 4 && sep_by_space == 1 ) || ( sign_posn == 2 && sep_by_space == 1 ) || ( sign_posn == 1 && sep_by_space == 1 ) || ( sign_posn == 0 && sep_by_space == 1 ) ) out_char ( space_char ) ;
 out_nstring ( currency_symbol , currency_symbol_len ) ;
 }
 if ( sign_posn == 4 ) {
 if ( sep_by_space == 2 ) out_char ( ' ' ) ;
 out_string ( sign_string ) ;
 }
 }
 if ( sign_posn == 2 ) {
 if ( sep_by_space == 2 ) out_char ( ' ' ) ;
 out_string ( sign_string ) ;
 }
 if ( sign_posn == 0 && is_negative ) out_char ( right_paren ) ;
 if ( dest - startp < width ) {
 if ( left ) do out_char ( ' ' ) ;
 while ( dest - startp < width ) ;
 else {
 int dist = width - ( dest - startp ) ;
 char * cp ;
 for ( cp = dest - 1 ;
 cp >= startp ;
 -- cp ) cp [ dist ] = cp [ 0 ] ;
 dest += dist ;
 do startp [ -- dist ] = ' ' ;
 while ( dist > 0 ) ;
 }
 }
 }
 * dest = '\0' ;
 return dest - s ;
 }