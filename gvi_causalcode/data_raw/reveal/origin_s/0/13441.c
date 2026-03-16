static void _InterpretPS ( IO * wrapper , EntityChar * ec , RetStack * rs ) {
 SplinePointList * cur = NULL , * head = NULL ;
 DBasePoint current , temp ;
 int tok , i , j ;
 struct psstack stack [ 100 ] ;
 real dval ;
 unsigned sp = 0 ;
 SplinePoint * pt ;
 RefChar * ref , * lastref = NULL ;
 real transform [ 6 ] , t [ 6 ] ;
 struct graphicsstate {
 real transform [ 6 ] ;
 DBasePoint current ;
 real linewidth ;
 int linecap , linejoin ;
 Color fore ;
 DashType dashes [ DASH_MAX ] ;
 SplineSet * clippath ;
 }
 gsaves [ 30 ] ;
 int gsp = 0 ;
 int ccnt = 0 ;
 GrowBuf gb ;
 struct pskeydict dict ;
 struct pskeyval * kv ;
 Color fore = COLOR_INHERITED ;
 int linecap = lc_inherited , linejoin = lj_inherited ;
 real linewidth = WIDTH_INHERITED ;
 DashType dashes [ DASH_MAX ] ;
 int dash_offset = 0 ;
 Entity * ent ;
 int warned = 0 ;
 struct garbage tofrees ;
 SplineSet * clippath = NULL ;
 char * tokbuf ;
 const int tokbufsize = 2 * 65536 + 10 ;
 tokbuf = malloc ( tokbufsize ) ;
 locale_t tmplocale ;
 locale_t oldlocale ;
 switch_to_c_locale ( & tmplocale , & oldlocale ) ;
 memset ( & gb , '\0' , sizeof ( GrowBuf ) ) ;
 memset ( & dict , '\0' , sizeof ( dict ) ) ;
 tofrees . cnt = 0 ;
 tofrees . next = NULL ;
 transform [ 0 ] = transform [ 3 ] = 1.0 ;
 transform [ 1 ] = transform [ 2 ] = transform [ 4 ] = transform [ 5 ] = 0 ;
 current . x = current . y = 0 ;
 dashes [ 0 ] = 0 ;
 dashes [ 1 ] = DASH_INHERITED ;
 if ( ec -> fromtype3 ) {
 stack [ 0 ] . type = stack [ 1 ] . type = ps_num ;
 stack [ 0 ] . u . val = stack [ 1 ] . u . val = 0 ;
 sp = 2 ;
 }
 while ( ( tok = nextpstoken ( wrapper , & dval , tokbuf , tokbufsize ) ) != pt_eof ) {
 if ( endedstopped ( wrapper ) ) {
 if ( sp < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 stack [ sp ] . type = ps_bool ;
 stack [ sp ++ ] . u . tf = false ;
 }
 }
 if ( sp > sizeof ( stack ) / sizeof ( stack [ 0 ] ) * 4 / 5 ) {
 sp = forgetstack ( stack , sizeof ( stack ) / sizeof ( stack [ 0 ] ) / 3 , sp ) ;
 }
 if ( ccnt > 0 ) {
 if ( tok == pt_closecurly ) -- ccnt ;
 else if ( tok == pt_opencurly ) ++ ccnt ;
 if ( ccnt > 0 ) AddTok ( & gb , tokbuf , tok == pt_namelit ) ;
 else {
 if ( sp < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 stack [ sp ] . type = ps_instr ;
 if ( gb . pt == NULL ) stack [ sp ++ ] . u . str = copy ( "" ) ;
 else {
 * gb . pt = '\0' ;
 gb . pt = gb . base ;
 stack [ sp ++ ] . u . str = copy ( ( char * ) gb . base ) ;
 }
 }
 }
 }
 else if ( tok == pt_unknown && ( kv = lookup ( & dict , tokbuf ) ) != NULL ) {
 if ( kv -> type == ps_instr ) pushio ( wrapper , NULL , copy ( kv -> u . str ) , 0 ) ;
 else if ( sp < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 stack [ sp ] . type = kv -> type ;
 stack [ sp ++ ] . u = kv -> u ;
 if ( kv -> type == ps_instr || kv -> type == ps_lit || kv -> type == ps_string ) stack [ sp - 1 ] . u . str = copy ( stack [ sp - 1 ] . u . str ) ;
 else if ( kv -> type == ps_array || kv -> type == ps_dict ) {
 copyarray ( & stack [ sp - 1 ] . u . dict , & stack [ sp - 1 ] . u . dict , & tofrees ) ;
 if ( stack [ sp - 1 ] . u . dict . is_executable ) sp = aload ( sp , stack , sizeof ( stack ) / sizeof ( stack [ 0 ] ) , & tofrees ) ;
 }
 }
 }
 else {
 if ( tok == pt_unknown ) {
 if ( strcmp ( tokbuf , "Cache" ) == 0 ) tok = pt_setcachedevice ;
 else if ( strcmp ( tokbuf , "SetWid" ) == 0 ) {
 tok = pt_setcharwidth ;
 if ( sp < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 stack [ sp ] . type = ps_num ;
 stack [ sp ++ ] . u . val = 0 ;
 }
 }
 else if ( strcmp ( tokbuf , "rrcurveto" ) == 0 ) {
 if ( sp >= 6 ) {
 stack [ sp - 4 ] . u . val += stack [ sp - 6 ] . u . val ;
 stack [ sp - 3 ] . u . val += stack [ sp - 5 ] . u . val ;
 stack [ sp - 2 ] . u . val += stack [ sp - 4 ] . u . val ;
 stack [ sp - 1 ] . u . val += stack [ sp - 3 ] . u . val ;
 tok = pt_rcurveto ;
 }
 }
 else if ( strcmp ( tokbuf , "FillStroke" ) == 0 ) {
 if ( sp > 0 ) -- sp ;
 tok = linewidth != WIDTH_INHERITED ? pt_stroke : pt_fill ;
 if ( wrapper -> top != NULL && wrapper -> top -> ps != NULL && linewidth != WIDTH_INHERITED ) linewidth /= 10.0 ;
 }
 else if ( strcmp ( tokbuf , "SG" ) == 0 ) {
 if ( linewidth != WIDTH_INHERITED && sp > 1 ) stack [ sp - 2 ] . u . val = stack [ sp - 1 ] . u . val ;
 if ( sp > 0 ) -- sp ;
 if ( sp > 0 ) stack [ sp - 1 ] . u . val = ( stack [ sp - 1 ] . u . val + 99 ) / 198.0 ;
 tok = pt_setgray ;
 }
 else if ( strcmp ( tokbuf , "ShowInt" ) == 0 ) {
 if ( ( ! wrapper -> top -> fogns && sp > 0 && stack [ sp - 1 ] . type == ps_num && stack [ sp - 1 ] . u . val >= 0 && stack [ sp - 1 ] . u . val <= 255 ) || ( wrapper -> top -> fogns && sp > 6 && stack [ sp - 7 ] . type == ps_num && stack [ sp - 7 ] . u . val >= 0 && stack [ sp - 7 ] . u . val <= 255 ) ) {
 ref = RefCharCreate ( ) ;
 memcpy ( ref -> transform , transform , sizeof ( ref -> transform ) ) ;
 if ( wrapper -> top -> fogns ) {
 sp -= 6 ;
 t [ 0 ] = stack [ sp + 0 ] . u . val ;
 t [ 1 ] = stack [ sp + 1 ] . u . val ;
 t [ 2 ] = stack [ sp + 2 ] . u . val ;
 t [ 3 ] = stack [ sp + 3 ] . u . val ;
 t [ 4 ] = stack [ sp + 4 ] . u . val ;
 t [ 5 ] = stack [ sp + 5 ] . u . val ;
 MatMultiply ( t , ref -> transform , ref -> transform ) ;
 wrapper -> top -> fogns = false ;
 }
 ref -> orig_pos = stack [ -- sp ] . u . val ;
 ref -> next = ec -> refs ;
 ec -> refs = ref ;
 continue ;
 }
 }
 else if ( strcmp ( tokbuf , "togNS_" ) == 0 ) {
 wrapper -> top -> fogns = ! wrapper -> top -> fogns ;
 continue ;
 }
 }
 switch ( tok ) {
 case pt_number : if ( sp < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 stack [ sp ] . type = ps_num ;
 stack [ sp ++ ] . u . val = dval ;
 }
 break ;
 case pt_string : if ( sp < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 stack [ sp ] . type = ps_string ;
 stack [ sp ++ ] . u . str = copyn ( tokbuf + 1 , strlen ( tokbuf ) - 2 ) ;
 }
 break ;
 case pt_true : case pt_false : if ( sp < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 stack [ sp ] . type = ps_bool ;
 stack [ sp ++ ] . u . tf = tok == pt_true ;
 }
 break ;
 case pt_opencurly : ++ ccnt ;
 break ;
 case pt_closecurly : -- ccnt ;
 if ( ccnt < 0 ) {
 goto done ;
 }
 break ;
 case pt_count : if ( sp < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 stack [ sp ] . type = ps_num ;
 stack [ sp ] . u . val = sp ;
 ++ sp ;
 }
 break ;
 case pt_pop : if ( sp > 0 ) {
 -- sp ;
 if ( stack [ sp ] . type == ps_string || stack [ sp ] . type == ps_instr || stack [ sp ] . type == ps_lit ) free ( stack [ sp ] . u . str ) ;
 else if ( stack [ sp ] . type == ps_array || stack [ sp ] . type == ps_dict ) dictfree ( & stack [ sp ] . u . dict ) ;
 }
 break ;
 case pt_clear : while ( sp > 0 ) {
 -- sp ;
 if ( stack [ sp ] . type == ps_string || stack [ sp ] . type == ps_instr || stack [ sp ] . type == ps_lit ) free ( stack [ sp ] . u . str ) ;
 else if ( stack [ sp ] . type == ps_array || stack [ sp ] . type == ps_dict ) dictfree ( & stack [ sp ] . u . dict ) ;
 }
 break ;
 case pt_dup : if ( sp > 0 && sp < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 stack [ sp ] = stack [ sp - 1 ] ;
 if ( stack [ sp ] . type == ps_string || stack [ sp ] . type == ps_instr || stack [ sp ] . type == ps_lit ) stack [ sp ] . u . str = copy ( stack [ sp ] . u . str ) ;
 else if ( stack [ sp ] . type == ps_array ) copyarray ( & stack [ sp ] . u . dict , & stack [ sp ] . u . dict , & tofrees ) ;
 ++ sp ;
 }
 break ;
 case pt_copy : if ( sp > 0 ) {
 int n = stack [ -- sp ] . u . val ;
 if ( n + sp < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 int i ;
 for ( i = 0 ;
 i < n ;
 ++ i ) {
 stack [ sp ] = stack [ sp - n ] ;
 if ( stack [ sp ] . type == ps_string || stack [ sp ] . type == ps_instr || stack [ sp ] . type == ps_lit ) stack [ sp ] . u . str = copy ( stack [ sp ] . u . str ) ;
 else if ( stack [ sp ] . type == ps_array ) copyarray ( & stack [ sp ] . u . dict , & stack [ sp ] . u . dict , & tofrees ) ;
 ++ sp ;
 }
 }
 }
 break ;
 case pt_exch : if ( sp > 1 ) {
 struct psstack temp ;
 temp = stack [ sp - 1 ] ;
 stack [ sp - 1 ] = stack [ sp - 2 ] ;
 stack [ sp - 2 ] = temp ;
 }
 break ;
 case pt_roll : sp = rollstack ( stack , sp ) ;
 break ;
 case pt_index : if ( sp > 0 ) {
 i = stack [ -- sp ] . u . val ;
 if ( i >= 0 && sp > ( unsigned ) i ) {
 stack [ sp ] = stack [ sp - i - 1 ] ;
 if ( stack [ sp ] . type == ps_string || stack [ sp ] . type == ps_instr || stack [ sp ] . type == ps_lit ) stack [ sp ] . u . str = copy ( stack [ sp ] . u . str ) ;
 else if ( stack [ sp ] . type == ps_array ) copyarray ( & stack [ sp ] . u . dict , & stack [ sp ] . u . dict , & tofrees ) ;
 ++ sp ;
 }
 }
 break ;
 case pt_add : if ( sp >= 2 && stack [ sp - 1 ] . type == ps_num && stack [ sp - 2 ] . type == ps_num ) {
 stack [ sp - 2 ] . u . val += stack [ sp - 1 ] . u . val ;
 -- sp ;
 }
 break ;
 case pt_sub : if ( sp >= 2 && stack [ sp - 1 ] . type == ps_num && stack [ sp - 2 ] . type == ps_num ) {
 stack [ sp - 2 ] . u . val -= stack [ sp - 1 ] . u . val ;
 -- sp ;
 }
 break ;
 case pt_mul : if ( sp >= 2 && stack [ sp - 1 ] . type == ps_num && stack [ sp - 2 ] . type == ps_num ) {
 stack [ sp - 2 ] . u . val *= stack [ sp - 1 ] . u . val ;
 -- sp ;
 }
 break ;
 case pt_div : if ( sp >= 2 && stack [ sp - 1 ] . type == ps_num && stack [ sp - 2 ] . type == ps_num ) {
 if ( stack [ sp - 1 ] . u . val == 0 ) LogError ( _ ( "Divide by zero in postscript code.\n" ) ) ;
 else stack [ sp - 2 ] . u . val /= stack [ sp - 1 ] . u . val ;
 -- sp ;
 }
 break ;
 case pt_idiv : if ( sp >= 2 && stack [ sp - 1 ] . type == ps_num && stack [ sp - 2 ] . type == ps_num ) {
 if ( stack [ sp - 1 ] . u . val == 0 ) LogError ( _ ( "Divide by zero in postscript code.\n" ) ) ;
 else stack [ sp - 2 ] . u . val = ( ( int ) stack [ sp - 2 ] . u . val ) / ( ( int ) stack [ sp - 1 ] . u . val ) ;
 -- sp ;
 }
 break ;
 case pt_mod : if ( sp >= 2 && stack [ sp - 1 ] . type == ps_num && stack [ sp - 2 ] . type == ps_num ) {
 if ( stack [ sp - 1 ] . u . val == 0 ) LogError ( _ ( "Divide by zero in postscript code.\n" ) ) ;
 else stack [ sp - 2 ] . u . val = ( ( int ) stack [ sp - 2 ] . u . val ) % ( ( int ) stack [ sp - 1 ] . u . val ) ;
 -- sp ;
 }
 break ;
 case pt_max : if ( sp >= 2 && stack [ sp - 1 ] . type == ps_num && stack [ sp - 2 ] . type == ps_num ) {
 if ( stack [ sp - 2 ] . u . val < stack [ sp - 1 ] . u . val ) stack [ sp - 2 ] . u . val = stack [ sp - 1 ] . u . val ;
 -- sp ;
 }
 break ;
 case pt_min : if ( sp >= 2 && stack [ sp - 1 ] . type == ps_num && stack [ sp - 2 ] . type == ps_num ) {
 if ( stack [ sp - 2 ] . u . val > stack [ sp - 1 ] . u . val ) stack [ sp - 2 ] . u . val = stack [ sp - 1 ] . u . val ;
 -- sp ;
 }
 break ;
 case pt_neg : if ( sp >= 1 ) {
 if ( stack [ sp - 1 ] . type == ps_num ) stack [ sp - 1 ] . u . val = - stack [ sp - 1 ] . u . val ;
 }
 break ;
 case pt_abs : if ( sp >= 1 ) {
 if ( stack [ sp - 1 ] . type == ps_num ) if ( stack [ sp - 1 ] . u . val < 0 ) stack [ sp - 1 ] . u . val = - stack [ sp - 1 ] . u . val ;
 }
 break ;
 case pt_round : if ( sp >= 1 ) {
 if ( stack [ sp - 1 ] . type == ps_num ) stack [ sp - 1 ] . u . val = rint ( stack [ sp - 1 ] . u . val ) ;
 }
 break ;
 case pt_floor : if ( sp >= 1 ) {
 if ( stack [ sp - 1 ] . type == ps_num ) stack [ sp - 1 ] . u . val = floor ( stack [ sp - 1 ] . u . val ) ;
 }
 break ;
 case pt_ceiling : if ( sp >= 1 ) {
 if ( stack [ sp - 1 ] . type == ps_num ) stack [ sp - 1 ] . u . val = ceil ( stack [ sp - 1 ] . u . val ) ;
 }
 break ;
 case pt_truncate : if ( sp >= 1 ) {
 if ( stack [ sp - 1 ] . type == ps_num ) {
 if ( stack [ sp - 1 ] . u . val < 0 ) stack [ sp - 1 ] . u . val = ceil ( stack [ sp - 1 ] . u . val ) ;
 else stack [ sp - 1 ] . u . val = floor ( stack [ sp - 1 ] . u . val ) ;
 }
 }
 break ;
 case pt_ne : case pt_eq : if ( sp >= 2 ) {
 if ( stack [ sp - 2 ] . type != stack [ sp - 1 ] . type ) stack [ sp - 2 ] . u . tf = false ;
 else if ( stack [ sp - 2 ] . type == ps_num ) stack [ sp - 2 ] . u . tf = ( stack [ sp - 2 ] . u . val == stack [ sp - 1 ] . u . val ) ;
 else if ( stack [ sp - 2 ] . type == ps_bool ) stack [ sp - 2 ] . u . tf = ( stack [ sp - 2 ] . u . tf == stack [ sp - 1 ] . u . tf ) ;
 else stack [ sp - 2 ] . u . tf = strcmp ( stack [ sp - 2 ] . u . str , stack [ sp - 1 ] . u . str ) == 0 ;
 stack [ sp - 2 ] . type = ps_bool ;
 if ( tok == pt_ne ) stack [ sp - 2 ] . u . tf = ! stack [ sp - 2 ] . u . tf ;
 -- sp ;
 }
 break ;
 case pt_gt : case pt_le : case pt_lt : case pt_ge : if ( sp >= 2 ) {
 if ( stack [ sp - 2 ] . type != stack [ sp - 1 ] . type ) stack [ sp - 2 ] . u . tf = false ;
 else if ( stack [ sp - 2 ] . type == ps_array ) LogError ( _ ( "Can't compare arrays\n" ) ) ;
 else {
 int cmp ;
 if ( stack [ sp - 2 ] . type == ps_num ) cmp = ( stack [ sp - 2 ] . u . val > stack [ sp - 1 ] . u . val ) ? 1 : ( stack [ sp - 2 ] . u . val == stack [ sp - 1 ] . u . val ) ? 0 : - 1 ;
 else if ( stack [ sp - 2 ] . type == ps_bool ) cmp = ( stack [ sp - 2 ] . u . tf - stack [ sp - 1 ] . u . tf ) ;
 else cmp = strcmp ( stack [ sp - 2 ] . u . str , stack [ sp - 1 ] . u . str ) ;
 if ( tok == pt_gt ) stack [ sp - 2 ] . u . tf = cmp > 0 ;
 else if ( tok == pt_lt ) stack [ sp - 2 ] . u . tf = cmp < 0 ;
 else if ( tok == pt_le ) stack [ sp - 2 ] . u . tf = cmp <= 0 ;
 else stack [ sp - 2 ] . u . tf = cmp >= 0 ;
 }
 stack [ sp - 2 ] . type = ps_bool ;
 -- sp ;
 }
 break ;
 case pt_not : if ( sp >= 1 ) {
 if ( stack [ sp - 1 ] . type == ps_bool ) stack [ sp - 1 ] . u . tf = ! stack [ sp - 1 ] . u . tf ;
 }
 break ;
 case pt_and : if ( sp >= 2 ) {
 if ( stack [ sp - 2 ] . type == ps_num ) stack [ sp - 2 ] . u . val = ( ( int ) stack [ sp - 2 ] . u . val ) & ( int ) stack [ sp - 1 ] . u . val ;
 else if ( stack [ sp - 2 ] . type == ps_bool ) stack [ sp - 2 ] . u . tf &= stack [ sp - 1 ] . u . tf ;
 -- sp ;
 }
 break ;
 case pt_or : if ( sp >= 2 ) {
 if ( stack [ sp - 2 ] . type == ps_num ) stack [ sp - 2 ] . u . val = ( ( int ) stack [ sp - 2 ] . u . val ) | ( int ) stack [ sp - 1 ] . u . val ;
 else if ( stack [ sp - 2 ] . type == ps_bool ) stack [ sp - 2 ] . u . tf |= stack [ sp - 1 ] . u . tf ;
 -- sp ;
 }
 break ;
 case pt_xor : if ( sp >= 2 ) {
 if ( stack [ sp - 2 ] . type == ps_num ) stack [ sp - 2 ] . u . val = ( ( int ) stack [ sp - 2 ] . u . val ) ^ ( int ) stack [ sp - 1 ] . u . val ;
 else if ( stack [ sp - 2 ] . type == ps_bool ) stack [ sp - 2 ] . u . tf ^= stack [ sp - 1 ] . u . tf ;
 -- sp ;
 }
 break ;
 case pt_exp : if ( sp >= 2 && stack [ sp - 1 ] . type == ps_num && stack [ sp - 2 ] . type == ps_num ) {
 stack [ sp - 2 ] . u . val = pow ( stack [ sp - 2 ] . u . val , stack [ sp - 1 ] . u . val ) ;
 -- sp ;
 }
 break ;
 case pt_sqrt : if ( sp >= 1 && stack [ sp - 1 ] . type == ps_num ) {
 stack [ sp - 1 ] . u . val = sqrt ( stack [ sp - 1 ] . u . val ) ;
 }
 break ;
 case pt_ln : if ( sp >= 1 && stack [ sp - 1 ] . type == ps_num ) {
 stack [ sp - 1 ] . u . val = log ( stack [ sp - 1 ] . u . val ) ;
 }
 break ;
 case pt_log : if ( sp >= 1 && stack [ sp - 1 ] . type == ps_num ) {
 stack [ sp - 1 ] . u . val = log10 ( stack [ sp - 1 ] . u . val ) ;
 }
 break ;
 case pt_atan : if ( sp >= 2 && stack [ sp - 1 ] . type == ps_num && stack [ sp - 2 ] . type == ps_num ) {
 stack [ sp - 2 ] . u . val = atan2 ( stack [ sp - 2 ] . u . val , stack [ sp - 1 ] . u . val ) * 180 / 3.1415926535897932 ;
 -- sp ;
 }
 break ;
 case pt_sin : if ( sp >= 1 && stack [ sp - 1 ] . type == ps_num ) {
 stack [ sp - 1 ] . u . val = sin ( stack [ sp - 1 ] . u . val * 3.1415926535897932 / 180 ) ;
 }
 break ;
 case pt_cos : if ( sp >= 1 && stack [ sp - 1 ] . type == ps_num ) {
 stack [ sp - 1 ] . u . val = cos ( stack [ sp - 1 ] . u . val * 3.1415926535897932 / 180 ) ;
 }
 break ;
 case pt_if : if ( sp >= 2 ) {
 if ( ( ( stack [ sp - 2 ] . type == ps_bool && stack [ sp - 2 ] . u . tf ) || ( stack [ sp - 2 ] . type == ps_num && strstr ( stack [ sp - 1 ] . u . str , "setcachedevice" ) != NULL ) ) && stack [ sp - 1 ] . type == ps_instr ) pushio ( wrapper , NULL , stack [ sp - 1 ] . u . str , 0 ) ;
 if ( stack [ sp - 1 ] . type == ps_string || stack [ sp - 1 ] . type == ps_instr || stack [ sp - 1 ] . type == ps_lit ) free ( stack [ sp - 1 ] . u . str ) ;
 sp -= 2 ;
 }
 else if ( sp == 1 && stack [ sp - 1 ] . type == ps_instr ) {
 if ( strstr ( stack [ sp - 1 ] . u . str , "setcachedevice" ) != NULL || strstr ( stack [ sp - 1 ] . u . str , "setcharwidth" ) != NULL ) pushio ( wrapper , NULL , stack [ sp - 1 ] . u . str , 0 ) ;
 free ( stack [ sp - 1 ] . u . str ) ;
 sp = 0 ;
 }
 break ;
 case pt_ifelse : if ( sp >= 3 ) {
 if ( stack [ sp - 3 ] . type == ps_bool && stack [ sp - 3 ] . u . tf ) {
 if ( stack [ sp - 2 ] . type == ps_instr ) pushio ( wrapper , NULL , stack [ sp - 2 ] . u . str , 0 ) ;
 }
 else {
 if ( stack [ sp - 1 ] . type == ps_instr ) pushio ( wrapper , NULL , stack [ sp - 1 ] . u . str , 0 ) ;
 }
 if ( stack [ sp - 1 ] . type == ps_string || stack [ sp - 1 ] . type == ps_instr || stack [ sp - 1 ] . type == ps_lit ) free ( stack [ sp - 1 ] . u . str ) ;
 if ( stack [ sp - 2 ] . type == ps_string || stack [ sp - 2 ] . type == ps_instr || stack [ sp - 2 ] . type == ps_lit ) free ( stack [ sp - 2 ] . u . str ) ;
 sp -= 3 ;
 }
 break ;
 case pt_for : if ( sp >= 4 ) {
 real init , incr , limit ;
 char * func ;
 int cnt ;
 if ( stack [ sp - 4 ] . type == ps_num && stack [ sp - 3 ] . type == ps_num && stack [ sp - 2 ] . type == ps_num && stack [ sp - 1 ] . type == ps_instr ) {
 init = stack [ sp - 4 ] . u . val ;
 incr = stack [ sp - 3 ] . u . val ;
 limit = stack [ sp - 2 ] . u . val ;
 func = stack [ sp - 1 ] . u . str ;
 sp -= 4 ;
 cnt = 0 ;
 if ( incr > 0 ) {
 while ( init <= limit ) {
 ++ cnt ;
 init += incr ;
 }
 }
 else if ( incr < 0 ) {
 while ( init >= limit ) {
 ++ cnt ;
 init += incr ;
 }
 }
 pushio ( wrapper , NULL , func , cnt ) ;
 free ( func ) ;
 }
 }
 break ;
 case pt_loop : if ( sp >= 1 ) {
 char * func ;
 int cnt ;
 if ( stack [ sp - 1 ] . type == ps_instr ) {
 cnt = 0x7fffffff ;
 func = stack [ sp - 1 ] . u . str ;
 -- sp ;
 pushio ( wrapper , NULL , func , cnt ) ;
 free ( func ) ;
 }
 }
 break ;
 case pt_repeat : if ( sp >= 2 ) {
 char * func ;
 int cnt ;
 if ( stack [ sp - 2 ] . type == ps_num && stack [ sp - 1 ] . type == ps_instr ) {
 cnt = stack [ sp - 2 ] . u . val ;
 func = stack [ sp - 1 ] . u . str ;
 sp -= 2 ;
 pushio ( wrapper , NULL , func , cnt ) ;
 free ( func ) ;
 }
 }
 break ;
 case pt_exit : ioescapeloop ( wrapper ) ;
 break ;
 case pt_stopped : if ( sp >= 1 ) {
 char * func ;
 if ( stack [ sp - 1 ] . type == ps_instr ) {
 func = stack [ sp - 1 ] . u . str ;
 -- sp ;
 pushio ( wrapper , NULL , func , - 1 ) ;
 free ( func ) ;
 }
 }
 break ;
 case pt_stop : sp = ioescapestopped ( wrapper , stack , sp , sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) ;
 break ;
 case pt_load : if ( sp >= 1 && stack [ sp - 1 ] . type == ps_lit ) {
 kv = lookup ( & dict , stack [ sp - 1 ] . u . str ) ;
 if ( kv != NULL ) {
 free ( stack [ sp - 1 ] . u . str ) ;
 stack [ sp - 1 ] . type = kv -> type ;
 stack [ sp - 1 ] . u = kv -> u ;
 if ( kv -> type == ps_instr || kv -> type == ps_lit ) stack [ sp - 1 ] . u . str = copy ( stack [ sp - 1 ] . u . str ) ;
 }
 else stack [ sp - 1 ] . type = ps_instr ;
 }
 break ;
 case pt_def : sp = AddEntry ( & dict , stack , sp ) ;
 break ;
 case pt_bind : break ;
 case pt_setcachedevice : if ( sp >= 6 ) {
 ec -> width = stack [ sp - 6 ] . u . val ;
 ec -> vwidth = stack [ sp - 5 ] . u . val ;
 sp -= 6 ;
 }
 break ;
 case pt_setcharwidth : if ( sp >= 2 ) ec -> width = stack [ sp -= 2 ] . u . val ;
 break ;
 case pt_translate : if ( sp >= 1 && stack [ sp - 1 ] . type == ps_array ) sp = DoMatOp ( tok , sp , stack ) ;
 else if ( sp >= 2 ) {
 transform [ 4 ] += stack [ sp - 2 ] . u . val * transform [ 0 ] + stack [ sp - 1 ] . u . val * transform [ 2 ] ;
 transform [ 5 ] += stack [ sp - 2 ] . u . val * transform [ 1 ] + stack [ sp - 1 ] . u . val * transform [ 3 ] ;
 sp -= 2 ;
 }
 break ;
 case pt_scale : if ( sp >= 1 && stack [ sp - 1 ] . type == ps_array ) sp = DoMatOp ( tok , sp , stack ) ;
 else if ( sp >= 2 ) {
 transform [ 0 ] *= stack [ sp - 2 ] . u . val ;
 transform [ 1 ] *= stack [ sp - 2 ] . u . val ;
 transform [ 2 ] *= stack [ sp - 1 ] . u . val ;
 transform [ 3 ] *= stack [ sp - 1 ] . u . val ;
 sp -= 2 ;
 }
 break ;
 case pt_rotate : if ( sp >= 1 && stack [ sp - 1 ] . type == ps_array ) sp = DoMatOp ( tok , sp , stack ) ;
 else if ( sp >= 1 ) {
 -- sp ;
 t [ 0 ] = t [ 3 ] = cos ( stack [ sp ] . u . val ) ;
 t [ 1 ] = sin ( stack [ sp ] . u . val ) ;
 t [ 2 ] = - t [ 1 ] ;
 t [ 4 ] = t [ 5 ] = 0 ;
 MatMultiply ( t , transform , transform ) ;
 }
 break ;
 case pt_concat : if ( sp >= 1 ) {
 if ( stack [ sp - 1 ] . type == ps_array ) {
 if ( stack [ sp - 1 ] . u . dict . cnt == 6 && stack [ sp - 1 ] . u . dict . entries [ 0 ] . type == ps_num ) {
 -- sp ;
 t [ 5 ] = stack [ sp ] . u . dict . entries [ 5 ] . u . val ;
 t [ 4 ] = stack [ sp ] . u . dict . entries [ 4 ] . u . val ;
 t [ 3 ] = stack [ sp ] . u . dict . entries [ 3 ] . u . val ;
 t [ 2 ] = stack [ sp ] . u . dict . entries [ 2 ] . u . val ;
 t [ 1 ] = stack [ sp ] . u . dict . entries [ 1 ] . u . val ;
 t [ 0 ] = stack [ sp ] . u . dict . entries [ 0 ] . u . val ;
 dictfree ( & stack [ sp ] . u . dict ) ;
 MatMultiply ( t , transform , transform ) ;
 }
 }
 }
 break ;
 case pt_transform : if ( sp >= 1 && stack [ sp - 1 ] . type == ps_array ) {
 if ( sp >= 3 ) {
 DoMatTransform ( tok , sp , stack ) ;
 -- sp ;
 }
 }
 else if ( sp >= 2 ) {
 double x = stack [ sp - 2 ] . u . val , y = stack [ sp - 1 ] . u . val ;
 stack [ sp - 2 ] . u . val = transform [ 0 ] * x + transform [ 1 ] * y + transform [ 4 ] ;
 stack [ sp - 1 ] . u . val = transform [ 2 ] * x + transform [ 3 ] * y + transform [ 5 ] ;
 }
 break ;
 case pt_itransform : if ( sp >= 1 && stack [ sp - 1 ] . type == ps_array ) {
 if ( sp >= 3 ) {
 DoMatTransform ( tok , sp , stack ) ;
 -- sp ;
 }
 }
 else if ( sp >= 2 ) {
 double x = stack [ sp - 2 ] . u . val , y = stack [ sp - 1 ] . u . val ;
 MatInverse ( t , transform ) ;
 stack [ sp - 2 ] . u . val = t [ 0 ] * x + t [ 1 ] * y + t [ 4 ] ;
 stack [ sp - 1 ] . u . val = t [ 2 ] * x + t [ 3 ] * y + t [ 5 ] ;
 }
 break ;
 case pt_dtransform : if ( sp >= 1 && stack [ sp - 1 ] . type == ps_array ) {
 if ( sp >= 3 ) {
 DoMatTransform ( tok , sp , stack ) ;
 -- sp ;
 }
 }
 else if ( sp >= 2 ) {
 double x = stack [ sp - 2 ] . u . val , y = stack [ sp - 1 ] . u . val ;
 stack [ sp - 2 ] . u . val = transform [ 0 ] * x + transform [ 1 ] * y ;
 stack [ sp - 1 ] . u . val = transform [ 2 ] * x + transform [ 3 ] * y ;
 }
 break ;
 case pt_idtransform : if ( sp >= 1 && stack [ sp - 1 ] . type == ps_array ) {
 if ( sp >= 3 ) {
 DoMatTransform ( tok , sp , stack ) ;
 -- sp ;
 }
 }
 else if ( sp >= 2 ) {
 double x = stack [ sp - 2 ] . u . val , y = stack [ sp - 1 ] . u . val ;
 MatInverse ( t , transform ) ;
 stack [ sp - 2 ] . u . val = t [ 0 ] * x + t [ 1 ] * y ;
 stack [ sp - 1 ] . u . val = t [ 2 ] * x + t [ 3 ] * y ;
 }
 break ;
 case pt_namelit : if ( strcmp ( tokbuf , "CharProcs" ) == 0 && ec != NULL ) {
 HandleType3Reference ( wrapper , ec , transform , tokbuf , tokbufsize ) ;
 }
 else if ( sp < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 stack [ sp ] . type = ps_lit ;
 stack [ sp ++ ] . u . str = copy ( tokbuf ) ;
 }
 break ;
 case pt_exec : if ( sp > 0 && stack [ sp - 1 ] . type == ps_lit ) {
 ref = RefCharCreate ( ) ;
 ref -> sc = ( SplineChar * ) stack [ -- sp ] . u . str ;
 memcpy ( ref -> transform , transform , sizeof ( transform ) ) ;
 if ( ec -> refs == NULL ) ec -> refs = ref ;
 else lastref -> next = ref ;
 lastref = ref ;
 }
 break ;
 case pt_newpath : SplinePointListsFree ( head ) ;
 head = NULL ;
 cur = NULL ;
 break ;
 case pt_lineto : case pt_rlineto : case pt_moveto : case pt_rmoveto : if ( sp >= 2 || tok == pt_newpath ) {
 if ( tok == pt_rlineto || tok == pt_rmoveto ) {
 current . x += stack [ sp - 2 ] . u . val ;
 current . y += stack [ sp - 1 ] . u . val ;
 sp -= 2 ;
 }
 else if ( tok == pt_lineto || tok == pt_moveto ) {
 current . x = stack [ sp - 2 ] . u . val ;
 current . y = stack [ sp - 1 ] . u . val ;
 sp -= 2 ;
 }
 pt = chunkalloc ( sizeof ( SplinePoint ) ) ;
 Transform ( & pt -> me , & current , transform ) ;
 pt -> noprevcp = true ;
 pt -> nonextcp = true ;
 if ( tok == pt_moveto || tok == pt_rmoveto ) {
 SplinePointList * spl = chunkalloc ( sizeof ( SplinePointList ) ) ;
 spl -> first = spl -> last = pt ;
 if ( cur != NULL ) cur -> next = spl ;
 else head = spl ;
 cur = spl ;
 }
 else {
 if ( cur != NULL && cur -> first != NULL && ( cur -> first != cur -> last || cur -> first -> next == NULL ) ) {
 CheckMake ( cur -> last , pt ) ;
 SplineMake3 ( cur -> last , pt ) ;
 cur -> last = pt ;
 }
 }
 }
 else sp = 0 ;
 break ;
 case pt_curveto : case pt_rcurveto : if ( sp >= 6 ) {
 if ( tok == pt_rcurveto ) {
 stack [ sp - 1 ] . u . val += current . y ;
 stack [ sp - 3 ] . u . val += current . y ;
 stack [ sp - 5 ] . u . val += current . y ;
 stack [ sp - 2 ] . u . val += current . x ;
 stack [ sp - 4 ] . u . val += current . x ;
 stack [ sp - 6 ] . u . val += current . x ;
 }
 current . x = stack [ sp - 2 ] . u . val ;
 current . y = stack [ sp - 1 ] . u . val ;
 if ( cur != NULL && cur -> first != NULL && ( cur -> first != cur -> last || cur -> first -> next == NULL ) ) {
 temp . x = stack [ sp - 6 ] . u . val ;
 temp . y = stack [ sp - 5 ] . u . val ;
 Transform ( & cur -> last -> nextcp , & temp , transform ) ;
 cur -> last -> nonextcp = false ;
 pt = chunkalloc ( sizeof ( SplinePoint ) ) ;
 temp . x = stack [ sp - 4 ] . u . val ;
 temp . y = stack [ sp - 3 ] . u . val ;
 Transform ( & pt -> prevcp , & temp , transform ) ;
 Transform ( & pt -> me , & current , transform ) ;
 pt -> nonextcp = true ;
 CheckMake ( cur -> last , pt ) ;
 SplineMake3 ( cur -> last , pt ) ;
 cur -> last = pt ;
 }
 sp -= 6 ;
 }
 else sp = 0 ;
 break ;
 case pt_arc : case pt_arcn : if ( sp >= 5 ) {
 real cx , cy , r , a1 , a2 ;
 cx = stack [ sp - 5 ] . u . val ;
 cy = stack [ sp - 4 ] . u . val ;
 r = stack [ sp - 3 ] . u . val ;
 a1 = stack [ sp - 2 ] . u . val ;
 a2 = stack [ sp - 1 ] . u . val ;
 sp -= 5 ;
 temp . x = cx + r * cos ( a1 / 180 * 3.1415926535897932 ) ;
 temp . y = cy + r * sin ( a1 / 180 * 3.1415926535897932 ) ;
 if ( temp . x != current . x || temp . y != current . y || ! ( cur != NULL && cur -> first != NULL && ( cur -> first != cur -> last || cur -> first -> next == NULL ) ) ) {
 pt = chunkalloc ( sizeof ( SplinePoint ) ) ;
 Transform ( & pt -> me , & temp , transform ) ;
 pt -> noprevcp = true ;
 pt -> nonextcp = true ;
 if ( cur != NULL && cur -> first != NULL && ( cur -> first != cur -> last || cur -> first -> next == NULL ) ) {
 CheckMake ( cur -> last , pt ) ;
 SplineMake3 ( cur -> last , pt ) ;
 cur -> last = pt ;
 }
 else {
 SplinePointList * spl = chunkalloc ( sizeof ( SplinePointList ) ) ;
 spl -> first = spl -> last = pt ;
 if ( cur != NULL ) cur -> next = spl ;
 else head = spl ;
 cur = spl ;
 }
 }
 circlearcsto ( a1 , a2 , cx , cy , r , cur , transform , tok == pt_arcn ) ;
 current . x = cx + r * cos ( a2 / 180 * 3.1415926535897932 ) ;
 current . y = cy + r * sin ( a2 / 180 * 3.1415926535897932 ) ;
 }
 else sp = 0 ;
 break ;
 case pt_arct : case pt_arcto : if ( sp >= 5 ) {
 real x1 , y1 , x2 , y2 , r ;
 real xt1 , xt2 , yt1 , yt2 ;
 x1 = stack [ sp - 5 ] . u . val ;
 y1 = stack [ sp - 4 ] . u . val ;
 x2 = stack [ sp - 3 ] . u . val ;
 y2 = stack [ sp - 2 ] . u . val ;
 r = stack [ sp - 1 ] . u . val ;
 sp -= 5 ;
 xt1 = xt2 = x1 ;
 yt1 = yt2 = y1 ;
 if ( cur == NULL || cur -> first == NULL || ( cur -> first == cur -> last && cur -> first -> next != NULL ) ) ;
 else if ( current . x == x1 && current . y == y1 ) ;
 else if ( ( x1 == x2 && y1 == y2 ) || ( current . x - x1 ) * ( y2 - y1 ) == ( x2 - x1 ) * ( current . y - y1 ) ) {
 current . x = x1 ;
 current . y = y1 ;
 pt = chunkalloc ( sizeof ( SplinePoint ) ) ;
 Transform ( & pt -> me , & current , transform ) ;
 pt -> noprevcp = true ;
 pt -> nonextcp = true ;
 CheckMake ( cur -> last , pt ) ;
 SplineMake3 ( cur -> last , pt ) ;
 cur -> last = pt ;
 }
 else {
 real l1 = sqrt ( ( current . x - x1 ) * ( current . x - x1 ) + ( current . y - y1 ) * ( current . y - y1 ) ) ;
 real l2 = sqrt ( ( x2 - x1 ) * ( x2 - x1 ) + ( y2 - y1 ) * ( y2 - y1 ) ) ;
 real dx = ( ( current . x - x1 ) / l1 + ( x2 - x1 ) / l2 ) ;
 real dy = ( ( current . y - y1 ) / l1 + ( y2 - y1 ) / l2 ) ;
 real l3 = sqrt ( dx * dx + dy * dy ) ;
 real cx , cy , t , tmid ;
 real a1 , amid , a2 ;
 int clockwise = true ;
 dx /= l3 ;
 dy /= l3 ;
 a1 = atan2 ( current . y - y1 , current . x - x1 ) ;
 a2 = atan2 ( y2 - y1 , x2 - x1 ) ;
 amid = atan2 ( dy , dx ) - a1 ;
 tmid = r / sin ( amid ) ;
 t = r / tan ( amid ) ;
 if ( t < 0 ) {
 clockwise = false ;
 t = - t ;
 tmid = - tmid ;
 }
 cx = x1 + tmid * dx ;
 cy = y1 + tmid * dy ;
 xt1 = x1 + t * ( current . x - x1 ) / l1 ;
 yt1 = y1 + t * ( current . y - y1 ) / l1 ;
 xt2 = x1 + t * ( x2 - x1 ) / l2 ;
 yt2 = y1 + t * ( y2 - y1 ) / l2 ;
 if ( xt1 != current . x || yt1 != current . y ) {
 DBasePoint temp ;
 temp . x = xt1 ;
 temp . y = yt1 ;
 pt = chunkalloc ( sizeof ( SplinePoint ) ) ;
 Transform ( & pt -> me , & temp , transform ) ;
 pt -> noprevcp = true ;
 pt -> nonextcp = true ;
 CheckMake ( cur -> last , pt ) ;
 SplineMake3 ( cur -> last , pt ) ;
 cur -> last = pt ;
 }
 a1 = 3 * 3.1415926535897932 / 2 + a1 ;
 a2 = 3.1415926535897932 / 2 + a2 ;
 if ( ! clockwise ) {
 a1 += 3.1415926535897932 ;
 a2 += 3.1415926535897932 ;
 }
 circlearcsto ( a1 * 180 / 3.1415926535897932 , a2 * 180 / 3.1415926535897932 , cx , cy , r , cur , transform , clockwise ) ;
 }
 if ( tok == pt_arcto ) {
 stack [ sp ] . type = stack [ sp + 1 ] . type = stack [ sp + 2 ] . type = stack [ sp + 3 ] . type = ps_num ;
 stack [ sp ++ ] . u . val = xt1 ;
 stack [ sp ++ ] . u . val = yt1 ;
 stack [ sp ++ ] . u . val = xt2 ;
 stack [ sp ++ ] . u . val = yt2 ;
 }
 current . x = xt2 ;
 current . y = yt2 ;
 }
 break ;
 case pt_closepath : if ( cur != NULL && cur -> first != NULL && cur -> first != cur -> last ) {
 if ( RealNear ( cur -> first -> me . x , cur -> last -> me . x ) && RealNear ( cur -> first -> me . y , cur -> last -> me . y ) ) {
 SplinePoint * oldlast = cur -> last ;
 cur -> first -> prevcp = oldlast -> prevcp ;
 cur -> first -> prevcp . x += ( cur -> first -> me . x - oldlast -> me . x ) ;
 cur -> first -> prevcp . y += ( cur -> first -> me . y - oldlast -> me . y ) ;
 cur -> first -> noprevcp = oldlast -> noprevcp ;
 oldlast -> prev -> from -> next = NULL ;
 cur -> last = oldlast -> prev -> from ;
 SplineFree ( oldlast -> prev ) ;
 SplinePointFree ( oldlast ) ;
 }
 CheckMake ( cur -> last , cur -> first ) ;
 SplineMake3 ( cur -> last , cur -> first ) ;
 cur -> last = cur -> first ;
 }
 break ;
 case pt_setlinecap : if ( sp >= 1 ) linecap = stack [ -- sp ] . u . val ;
 break ;
 case pt_setlinejoin : if ( sp >= 1 ) linejoin = stack [ -- sp ] . u . val ;
 break ;
 case pt_setlinewidth : if ( sp >= 1 ) linewidth = stack [ -- sp ] . u . val ;
 break ;
 case pt_setdash : if ( sp >= 2 && stack [ sp - 1 ] . type == ps_num && stack [ sp - 2 ] . type == ps_array ) {
 sp -= 2 ;
 dash_offset = stack [ sp + 1 ] . u . val ;
 for ( i = 0 ;
 i < DASH_MAX && i < stack [ sp ] . u . dict . cnt ;
 ++ i ) dashes [ i ] = stack [ sp ] . u . dict . entries [ i ] . u . val ;
 dictfree ( & stack [ sp ] . u . dict ) ;
 }
 break ;
 case pt_currentlinecap : case pt_currentlinejoin : if ( sp < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 stack [ sp ] . type = ps_num ;
 stack [ sp ++ ] . u . val = tok == pt_currentlinecap ? linecap : linejoin ;
 }
 break ;
 case pt_currentlinewidth : if ( sp < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 stack [ sp ] . type = ps_num ;
 stack [ sp ++ ] . u . val = linewidth ;
 }
 break ;
 case pt_currentdash : if ( sp + 1 < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 struct pskeydict dict ;
 for ( i = 0 ;
 i < DASH_MAX && dashes [ i ] != 0 ;
 ++ i ) ;
 dict . cnt = dict . max = i ;
 dict . entries = calloc ( i , sizeof ( struct pskeyval ) ) ;
 dict . is_executable = false ;
 for ( j = 0 ;
 j < i ;
 ++ j ) {
 dict . entries [ j ] . type = ps_num ;
 dict . entries [ j ] . u . val = dashes [ j ] ;
 }
 stack [ sp ] . type = ps_array ;
 stack [ sp ++ ] . u . dict = dict ;
 stack [ sp ] . type = ps_num ;
 stack [ sp ++ ] . u . val = dash_offset ;
 }
 break ;
 case pt_currentgray : if ( sp < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 stack [ sp ] . type = ps_num ;
 stack [ sp ++ ] . u . val = ( 3 * ( ( fore >> 16 ) & 0xff ) + 6 * ( ( fore >> 8 ) & 0xff ) + ( fore & 0xff ) ) / 2550. ;
 }
 break ;
 case pt_setgray : if ( sp >= 1 ) {
 fore = stack [ -- sp ] . u . val * 255 ;
 fore *= 0x010101 ;
 }
 break ;
 case pt_setrgbcolor : if ( sp >= 3 ) {
 fore = ( ( ( int ) ( stack [ sp - 3 ] . u . val * 255 ) ) << 16 ) + ( ( ( int ) ( stack [ sp - 2 ] . u . val * 255 ) ) << 8 ) + ( int ) ( stack [ sp - 1 ] . u . val * 255 ) ;
 sp -= 3 ;
 }
 break ;
 case pt_currenthsbcolor : case pt_currentrgbcolor : if ( sp + 2 < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 stack [ sp ] . type = stack [ sp + 1 ] . type = stack [ sp + 2 ] . type = ps_num ;
 if ( tok == pt_currentrgbcolor ) {
 stack [ sp ++ ] . u . val = ( ( fore >> 16 ) & 0xff ) / 255. ;
 stack [ sp ++ ] . u . val = ( ( fore >> 8 ) & 0xff ) / 255. ;
 stack [ sp ++ ] . u . val = ( fore & 0xff ) / 255. ;
 }
 else {
 int r = fore >> 16 , g = ( fore >> 8 ) & 0xff , bl = fore & 0xff ;
 int mx , mn ;
 real h , s , b ;
 mx = mn = r ;
 if ( mx > g ) mn = g ;
 else mx = g ;
 if ( mx < bl ) mx = bl ;
 if ( mn > bl ) mn = bl ;
 b = mx / 255. ;
 s = h = 0 ;
 if ( mx > 0 ) s = ( ( real ) ( mx - mn ) ) / mx ;
 if ( s != 0 ) {
 real rdiff = ( ( real ) ( mx - r ) ) / ( mx - mn ) ;
 real gdiff = ( ( real ) ( mx - g ) ) / ( mx - mn ) ;
 real bdiff = ( ( real ) ( mx - bl ) ) / ( mx - mn ) ;
 if ( rdiff == 0 ) h = bdiff - gdiff ;
 else if ( gdiff == 0 ) h = 2 + rdiff - bdiff ;
 else h = 4 + gdiff - rdiff ;
 h /= 6 ;
 if ( h < 0 ) h += 1 ;
 }
 stack [ sp ++ ] . u . val = h ;
 stack [ sp ++ ] . u . val = s ;
 stack [ sp ++ ] . u . val = b ;
 }
 }
 break ;
 case pt_sethsbcolor : if ( sp >= 3 ) {
 real h = stack [ sp - 3 ] . u . val , s = stack [ sp - 2 ] . u . val , b = stack [ sp - 1 ] . u . val ;
 int r , g , bl ;
 if ( s == 0 ) fore = ( ( int ) ( b * 255 ) ) * 0x010101 ;
 else {
 real sextant = ( h - floor ( h ) ) * 6 ;
 real mod = sextant - floor ( sextant ) ;
 real p = b * ( 1 - s ) , q = b * ( 1 - s * mod ) , t = b * ( 1 - s * ( 1 - mod ) ) ;
 switch ( ( int ) sextant ) {
 case 0 : r = b * 255. ;
 g = t * 255. ;
 bl = p * 255. ;
 break ;
 case 1 : r = q * 255. ;
 g = b * 255. ;
 bl = p * 255. ;
 break ;
 case 2 : r = p * 255. ;
 g = b * 255. ;
 bl = t * 255. ;
 break ;
 case 3 : r = p * 255. ;
 g = q * 255. ;
 bl = b * 255. ;
 break ;
 case 4 : r = t * 255. ;
 g = p * 255. ;
 bl = b * 255. ;
 break ;
 case 5 : r = b * 255. ;
 g = p * 255. ;
 bl = q * 255. ;
 break ;
 default : break ;
 }
 fore = COLOR_CREATE ( r , g , bl ) ;
 }
 sp -= 3 ;
 }
 break ;
 case pt_currentcmykcolor : if ( sp + 3 < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 real c , m , y , k ;
 stack [ sp ] . type = stack [ sp + 1 ] . type = stack [ sp + 2 ] . type = stack [ sp + 3 ] . type = ps_num ;
 y = 1. - ( fore & 0xff ) / 255. ;
 m = 1. - ( ( fore >> 8 ) & 0xff ) / 255. ;
 c = 1. - ( ( fore >> 16 ) & 0xff ) / 255. ;
 k = y ;
 if ( k > m ) k = m ;
 if ( k > c ) k = c ;
 if ( k != 1 ) {
 y = ( y - k ) / ( 1 - k ) ;
 m = ( m - k ) / ( 1 - k ) ;
 c = ( c - k ) / ( 1 - k ) ;
 }
 else y = m = c = 0 ;
 stack [ sp ++ ] . u . val = c ;
 stack [ sp ++ ] . u . val = m ;
 stack [ sp ++ ] . u . val = y ;
 stack [ sp ++ ] . u . val = k ;
 }
 break ;
 case pt_setcmykcolor : if ( sp >= 4 ) {
 real c = stack [ sp - 4 ] . u . val , m = stack [ sp - 3 ] . u . val , y = stack [ sp - 2 ] . u . val , k = stack [ sp - 1 ] . u . val ;
 sp -= 4 ;
 if ( k == 1 ) fore = 0x000000 ;
 else {
 if ( ( y = ( 1 - k ) * y + k ) < 0 ) y = 0 ;
 else if ( y > 1 ) y = 1 ;
 if ( ( m = ( 1 - k ) * m + k ) < 0 ) m = 0 ;
 else if ( m > 1 ) m = 1 ;
 if ( ( c = ( 1 - k ) * c + k ) < 0 ) c = 0 ;
 else if ( c > 1 ) c = 1 ;
 fore = ( ( int ) ( ( 1 - c ) * 255. ) << 16 ) | ( ( int ) ( ( 1 - m ) * 255. ) << 8 ) | ( ( int ) ( ( 1 - y ) * 255. ) ) ;
 }
 }
 break ;
 case pt_currentpoint : if ( sp + 1 < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 stack [ sp ] . type = ps_num ;
 stack [ sp ++ ] . u . val = current . x ;
 stack [ sp ] . type = ps_num ;
 stack [ sp ++ ] . u . val = current . y ;
 }
 break ;
 case pt_fill : case pt_stroke : if ( head == NULL && ec -> splines != NULL ) {
 ent = ec -> splines ;
 if ( tok == pt_stroke ) {
 ent -> u . splines . cap = linecap ;
 ent -> u . splines . join = linejoin ;
 ent -> u . splines . stroke_width = linewidth ;
 memcpy ( ent -> u . splines . transform , transform , sizeof ( transform ) ) ;
 }
 }
 else {
 ent = EntityCreate ( head , linecap , linejoin , linewidth , transform , clippath ) ;
 ent -> next = ec -> splines ;
 ec -> splines = ent ;
 }
 if ( tok == pt_fill ) ent -> u . splines . fill . col = fore ;
 else ent -> u . splines . stroke . col = fore ;
 head = NULL ;
 cur = NULL ;
 break ;
 case pt_clip : SplinePointListsFree ( clippath ) ;
 clippath = SplinePointListCopy ( head ) ;
 if ( clippath != NULL && clippath -> first != clippath -> last ) {
 SplineMake3 ( clippath -> last , clippath -> first ) ;
 clippath -> last = clippath -> first ;
 }
 break ;
 case pt_imagemask : i = PSAddImagemask ( ec , stack , sp , transform , fore ) ;
 while ( sp > i ) {
 -- sp ;
 if ( stack [ sp ] . type == ps_string || stack [ sp ] . type == ps_instr || stack [ sp ] . type == ps_lit ) free ( stack [ sp ] . u . str ) ;
 else if ( stack [ sp ] . type == ps_array || stack [ sp ] . type == ps_dict ) dictfree ( & stack [ sp ] . u . dict ) ;
 }
 break ;
 case pt_save : case pt_currentmatrix : if ( sp < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 stack [ sp ] . type = ps_num ;
 stack [ sp ++ ] . u . val = 0 ;
 }
 ;
 case pt_gsave : if ( gsp < 30 ) {
 memcpy ( gsaves [ gsp ] . transform , transform , sizeof ( transform ) ) ;
 gsaves [ gsp ] . current = current ;
 gsaves [ gsp ] . linewidth = linewidth ;
 gsaves [ gsp ] . linecap = linecap ;
 gsaves [ gsp ] . linejoin = linejoin ;
 gsaves [ gsp ] . fore = fore ;
 gsaves [ gsp ] . clippath = SplinePointListCopy ( clippath ) ;
 ++ gsp ;
 }
 break ;
 case pt_restore : case pt_setmatrix : if ( sp >= 1 ) -- sp ;
 ;
 case pt_grestore : if ( gsp > 0 ) {
 -- gsp ;
 memcpy ( transform , gsaves [ gsp ] . transform , sizeof ( transform ) ) ;
 current = gsaves [ gsp ] . current ;
 linewidth = gsaves [ gsp ] . linewidth ;
 linecap = gsaves [ gsp ] . linecap ;
 linejoin = gsaves [ gsp ] . linejoin ;
 fore = gsaves [ gsp ] . fore ;
 SplinePointListsFree ( clippath ) ;
 clippath = gsaves [ gsp ] . clippath ;
 }
 break ;
 case pt_null : if ( sp < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 stack [ sp ] . u . val = 0 ;
 stack [ sp ++ ] . type = ps_num ;
 }
 break ;
 case pt_currentoverprint : if ( sp < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 stack [ sp ] . u . val = 0 ;
 stack [ sp ++ ] . type = ps_bool ;
 }
 break ;
 case pt_setoverprint : if ( sp >= 1 ) -- sp ;
 break ;
 case pt_currentflat : if ( sp < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 stack [ sp ] . u . val = 1.0 ;
 stack [ sp ++ ] . type = ps_num ;
 }
 break ;
 case pt_setflat : if ( sp >= 1 ) -- sp ;
 break ;
 case pt_currentmiterlimit : if ( sp < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 stack [ sp ] . u . val = 10.0 ;
 stack [ sp ++ ] . type = ps_num ;
 }
 break ;
 case pt_setmiterlimit : if ( sp >= 1 ) -- sp ;
 break ;
 case pt_currentpacking : if ( sp < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 stack [ sp ] . u . val = 0 ;
 stack [ sp ++ ] . type = ps_bool ;
 }
 break ;
 case pt_setpacking : if ( sp >= 1 ) -- sp ;
 break ;
 case pt_currentstrokeadjust : if ( sp < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 stack [ sp ] . u . val = 0 ;
 stack [ sp ++ ] . type = ps_bool ;
 }
 break ;
 case pt_setstrokeadjust : if ( sp >= 1 ) -- sp ;
 break ;
 case pt_currentsmoothness : if ( sp < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 stack [ sp ] . u . val = 1.0 ;
 stack [ sp ++ ] . type = ps_num ;
 }
 break ;
 case pt_setsmoothness : if ( sp >= 1 ) -- sp ;
 break ;
 case pt_currentobjectformat : if ( sp < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 stack [ sp ] . u . val = 0.0 ;
 stack [ sp ++ ] . type = ps_num ;
 }
 break ;
 case pt_setobjectformat : if ( sp >= 1 ) -- sp ;
 break ;
 case pt_currentglobal : case pt_currentshared : if ( sp < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 stack [ sp ] . u . val = 0 ;
 stack [ sp ++ ] . type = ps_bool ;
 }
 break ;
 case pt_setglobal : if ( sp >= 1 ) -- sp ;
 break ;
 case pt_openarray : case pt_mark : if ( sp < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 stack [ sp ++ ] . type = ps_mark ;
 }
 break ;
 case pt_counttomark : for ( i = 0 ;
 ( unsigned ) i < sp ;
 ++ i ) if ( stack [ sp - 1 - i ] . type == ps_mark ) break ;
 if ( ( unsigned ) i == sp ) LogError ( _ ( "No mark in counttomark\n" ) ) ;
 else if ( sp < sizeof ( stack ) / sizeof ( stack [ 0 ] ) ) {
 stack [ sp ] . type = ps_num ;
 stack [ sp ++ ] . u . val = i ;
 }
 break ;
 case pt_cleartomark : for ( i = 0 ;
 ( unsigned ) i < sp ;
 ++ i ) if ( stack [ sp - 1 - i ] . type == ps_mark ) break ;
 if ( ( unsigned ) i == sp ) LogError ( _ ( "No mark in cleartomark\n" ) ) ;
 else {
 while ( sp >= i ) {
 -- sp ;
 if ( stack [ sp ] . type == ps_string || stack [ sp ] . type == ps_instr || stack [ sp ] . type == ps_lit ) free ( stack [ sp ] . u . str ) ;
 else if ( stack [ sp ] . type == ps_array || stack [ sp ] . type == ps_dict ) dictfree ( & stack [ sp ] . u . dict ) ;
 }
 }
 break ;
 case pt_closearray : for ( i = 0 ;
 ( unsigned ) i < sp ;
 ++ i ) if ( stack [ sp - 1 - i ] . type == ps_mark ) break ;
 if ( ( unsigned ) i == sp ) LogError ( _ ( "No mark in ] (close array)\n" ) ) ;
 else {
 struct pskeydict dict ;
 dict . cnt = dict . max = i ;
 dict . entries = calloc ( i , sizeof ( struct pskeyval ) ) ;
 dict . is_executable = false ;
 for ( j = 0 ;
 j < i ;
 ++ j ) {
 dict . entries [ j ] . type = stack [ sp - i + j ] . type ;
 dict . entries [ j ] . u = stack [ sp - i + j ] . u ;
 }
 collectgarbage ( & tofrees , & dict ) ;
 sp = sp - i ;
 stack [ sp - 1 ] . type = ps_array ;
 stack [ sp - 1 ] . u . dict = dict ;
 }
 break ;
 case pt_array : if ( sp >= 1 && stack [ sp - 1 ] . type == ps_num ) {
 struct pskeydict dict ;
 dict . cnt = dict . max = stack [ sp - 1 ] . u . val ;
 dict . entries = calloc ( dict . cnt , sizeof ( struct pskeyval ) ) ;
 dict . is_executable = false ;
 stack [ sp - 1 ] . type = ps_array ;
 stack [ sp - 1 ] . u . dict = dict ;
 }
 break ;
 case pt_aload : sp = aload ( sp , stack , sizeof ( stack ) / sizeof ( stack [ 0 ] ) , & tofrees ) ;
 break ;
 case pt_astore : if ( sp >= 1 && stack [ sp - 1 ] . type == ps_array ) {
 struct pskeydict dict ;
 -- sp ;
 dict = stack [ sp ] . u . dict ;
 if ( sp >= dict . cnt ) {
 for ( i = dict . cnt - 1 ;
 i >= 0 ;
 -- i ) {
 -- sp ;
 dict . entries [ i ] . type = stack [ sp ] . type ;
 dict . entries [ i ] . u = stack [ sp ] . u ;
 }
 }
 stack [ sp ] . type = ps_array ;
 stack [ sp ] . u . dict = dict ;
 ++ sp ;
 }
 break ;
 case pt_output : case pt_outputd : case pt_print : if ( sp >= 1 ) {
 -- sp ;
 switch ( stack [ sp ] . type ) {
 case ps_num : printf ( "%g" , ( double ) stack [ sp ] . u . val ) ;
 break ;
 case ps_bool : printf ( "%s" , stack [ sp ] . u . tf ? "true" : "false" ) ;
 break ;
 case ps_string : case ps_instr : case ps_lit : if ( tok == pt_outputd ) printf ( stack [ sp ] . type == ps_lit ? "/" : stack [ sp ] . type == ps_string ? "(" : "{
" ) ;
 printf ( "%s" , stack [ sp ] . u . str ) ;
 if ( tok == pt_outputd ) printf ( stack [ sp ] . type == ps_lit ? "" : stack [ sp ] . type == ps_string ? ")" : "}
" ) ;
 free ( stack [ sp ] . u . str ) ;
 break ;
 case ps_void : printf ( "-- void --" ) ;
 break ;
 case ps_array : if ( tok == pt_outputd ) {
 printarray ( & stack [ sp ] . u . dict ) ;
 dictfree ( & stack [ sp ] . u . dict ) ;
 break ;
 }
 dictfree ( & stack [ sp ] . u . dict ) ;
 default : printf ( "-- nostringval --" ) ;
 break ;
 }
 if ( tok == pt_output || tok == pt_outputd ) printf ( "\n" ) ;
 }
 else LogError ( _ ( "Nothing on stack to print\n" ) ) ;
 break ;
 case pt_cvi : case pt_cvr : if ( sp >= 1 && stack [ sp - 1 ] . type == ps_string ) {
 double val = strtod ( stack [ sp - 1 ] . u . str , NULL ) ;
 free ( stack [ sp - 1 ] . u . str ) ;
 stack [ sp - 1 ] . u . val = val ;
 stack [ sp - 1 ] . type = ps_num ;
 }
 break ;
 case pt_cvlit : if ( sp >= 1 ) {
 if ( stack [ sp - 1 ] . type == ps_array ) stack [ sp - 1 ] . u . dict . is_executable = false ;
 }
 case pt_cvn : if ( sp >= 1 ) {
 if ( stack [ sp - 1 ] . type == ps_string ) stack [ sp - 1 ] . type = ps_lit ;
 }
 case pt_cvx : if ( sp >= 1 ) {
 if ( stack [ sp - 1 ] . type == ps_array ) stack [ sp - 1 ] . u . dict . is_executable = true ;
 }
 break ;
 case pt_cvrs : if ( sp >= 3 && stack [ sp - 1 ] . type == ps_string && stack [ sp - 2 ] . type == ps_num && stack [ sp - 3 ] . type == ps_num ) {
 if ( stack [ sp - 2 ] . u . val == 8 ) sprintf ( stack [ sp - 1 ] . u . str , "%o" , ( int ) stack [ sp - 3 ] . u . val ) ;
 else if ( stack [ sp - 2 ] . u . val == 16 ) sprintf ( stack [ sp - 1 ] . u . str , "%X" , ( int ) stack [ sp - 3 ] . u . val ) ;
 else sprintf ( stack [ sp - 1 ] . u . str , "%g" , ( double ) stack [ sp - 3 ] . u . val ) ;
 stack [ sp - 3 ] = stack [ sp - 1 ] ;
 sp -= 2 ;
 }
 break ;
 case pt_cvs : if ( sp >= 2 && stack [ sp - 1 ] . type == ps_string ) {
 switch ( stack [ sp ] . type ) {
 case ps_num : sprintf ( stack [ sp - 1 ] . u . str , "%g" , ( double ) stack [ sp - 2 ] . u . val ) ;
 break ;
 case ps_bool : sprintf ( stack [ sp - 1 ] . u . str , "%s" , stack [ sp - 2 ] . u . tf ? "true" : "false" ) ;
 break ;
 case ps_string : case ps_instr : case ps_lit : sprintf ( stack [ sp - 1 ] . u . str , "%s" , stack [ sp - 2 ] . u . str ) ;
 free ( stack [ sp ] . u . str ) ;
 break ;
 case ps_void : printf ( "-- void --" ) ;
 break ;
 case ps_array : dictfree ( & stack [ sp ] . u . dict ) ;
 default : sprintf ( stack [ sp - 1 ] . u . str , "-- nostringval --" ) ;
 break ;
 }
 stack [ sp - 2 ] = stack [ sp - 1 ] ;
 -- sp ;
 }
 break ;
 case pt_stringop : if ( sp >= 1 && stack [ sp - 1 ] . type == ps_num ) {
 stack [ sp - 1 ] . type = ps_string ;
 stack [ sp - 1 ] . u . str = calloc ( stack [ sp - 1 ] . u . val + 1 , 1 ) ;
 }
 break ;
 case pt_unknown : if ( ! warned ) {
 LogError ( _ ( "Warning: Unable to parse token %s, some features may be lost\n" ) , tokbuf ) ;
 warned = true ;
 }
 break ;
 default : break ;
 }
 }
 }
 done : if ( rs != NULL ) {
 int i , cnt , j ;
 for ( i = sp - 1 ;
 i >= 0 ;
 -- i ) if ( stack [ i ] . type != ps_num ) break ;
 cnt = sp - 1 - i ;
 if ( cnt > rs -> max ) cnt = rs -> max ;
 rs -> cnt = cnt ;
 for ( j = i + 1 ;
 ( unsigned ) j < sp ;
 ++ j ) rs -> stack [ j - i - 1 ] = stack [ j ] . u . val ;
 }
 freestuff ( stack , sp , & dict , & gb , & tofrees ) ;
 if ( head != NULL ) {
 ent = EntityCreate ( head , linecap , linejoin , linewidth , transform , clippath ) ;
 ent -> next = ec -> splines ;
 ec -> splines = ent ;
 }
 while ( gsp > 0 ) {
 -- gsp ;
 SplinePointListsFree ( gsaves [ gsp ] . clippath ) ;
 }
 SplinePointListsFree ( clippath ) ;
 ECCategorizePoints ( ec ) ;
 if ( ec -> width == UNDEFINED_WIDTH ) ec -> width = wrapper -> advance_width ;
 switch_to_old_locale ( & tmplocale , & oldlocale ) ;
 free ( tokbuf ) ;
 }