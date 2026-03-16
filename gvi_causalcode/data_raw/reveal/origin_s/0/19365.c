static const char * parseState ( const char * s , int32_t state [ 256 ] , uint32_t * pFlags ) {
 const char * t ;
 uint32_t start , end , i ;
 int32_t entry ;
 for ( i = 0 ;
 i < 256 ;
 ++ i ) {
 state [ i ] = MBCS_ENTRY_FINAL ( 0 , MBCS_STATE_ILLEGAL , 0xffff ) ;
 }
 s = u_skipWhitespace ( s ) ;
 if ( uprv_strncmp ( "initial" , s , 7 ) == 0 ) {
 * pFlags = MBCS_STATE_FLAG_DIRECT ;
 s = u_skipWhitespace ( s + 7 ) ;
 if ( * s ++ != ',' ) {
 return s - 1 ;
 }
 }
 else if ( * pFlags == 0 && uprv_strncmp ( "surrogates" , s , 10 ) == 0 ) {
 * pFlags = MBCS_STATE_FLAG_SURROGATES ;
 s = u_skipWhitespace ( s + 10 ) ;
 if ( * s ++ != ',' ) {
 return s - 1 ;
 }
 }
 else if ( * s == 0 ) {
 return NULL ;
 }
 for ( ;
 ;
 ) {
 s = u_skipWhitespace ( s ) ;
 start = uprv_strtoul ( s , ( char * * ) & t , 16 ) ;
 if ( s == t || 0xff < start ) {
 return s ;
 }
 s = u_skipWhitespace ( t ) ;
 if ( * s == '-' ) {
 s = u_skipWhitespace ( s + 1 ) ;
 end = uprv_strtoul ( s , ( char * * ) & t , 16 ) ;
 if ( s == t || end < start || 0xff < end ) {
 return s ;
 }
 s = u_skipWhitespace ( t ) ;
 }
 else {
 end = start ;
 }
 if ( * s != ':' && * s != '.' ) {
 entry = MBCS_ENTRY_FINAL ( 0 , MBCS_STATE_VALID_16 , 0 ) ;
 }
 else {
 entry = MBCS_ENTRY_TRANSITION ( 0 , 0 ) ;
 if ( * s == ':' ) {
 s = u_skipWhitespace ( s + 1 ) ;
 i = uprv_strtoul ( s , ( char * * ) & t , 16 ) ;
 if ( s != t ) {
 if ( 0x7f < i ) {
 return s ;
 }
 s = u_skipWhitespace ( t ) ;
 entry = MBCS_ENTRY_SET_STATE ( entry , i ) ;
 }
 }
 if ( * s == '.' ) {
 entry = MBCS_ENTRY_SET_FINAL ( entry ) ;
 s = u_skipWhitespace ( s + 1 ) ;
 if ( * s == 'u' ) {
 entry = MBCS_ENTRY_FINAL_SET_ACTION_VALUE ( entry , MBCS_STATE_UNASSIGNED , 0xfffe ) ;
 s = u_skipWhitespace ( s + 1 ) ;
 }
 else if ( * s == 'p' ) {
 if ( * pFlags != MBCS_STATE_FLAG_DIRECT ) {
 entry = MBCS_ENTRY_FINAL_SET_ACTION ( entry , MBCS_STATE_VALID_16_PAIR ) ;
 }
 else {
 entry = MBCS_ENTRY_FINAL_SET_ACTION ( entry , MBCS_STATE_VALID_16 ) ;
 }
 s = u_skipWhitespace ( s + 1 ) ;
 }
 else if ( * s == 's' ) {
 entry = MBCS_ENTRY_FINAL_SET_ACTION ( entry , MBCS_STATE_CHANGE_ONLY ) ;
 s = u_skipWhitespace ( s + 1 ) ;
 }
 else if ( * s == 'i' ) {
 entry = MBCS_ENTRY_FINAL_SET_ACTION_VALUE ( entry , MBCS_STATE_ILLEGAL , 0xffff ) ;
 s = u_skipWhitespace ( s + 1 ) ;
 }
 else {
 entry = MBCS_ENTRY_FINAL_SET_ACTION ( entry , MBCS_STATE_VALID_16 ) ;
 }
 }
 else {
 }
 }
 if ( MBCS_ENTRY_FINAL_ACTION ( entry ) == MBCS_STATE_VALID_16 ) {
 switch ( * pFlags ) {
 case 0 : break ;
 case MBCS_STATE_FLAG_DIRECT : entry = MBCS_ENTRY_FINAL_SET_ACTION_VALUE ( entry , MBCS_STATE_VALID_DIRECT_16 , 0xfffe ) ;
 break ;
 case MBCS_STATE_FLAG_SURROGATES : entry = MBCS_ENTRY_FINAL_SET_ACTION_VALUE ( entry , MBCS_STATE_VALID_16_PAIR , 0 ) ;
 break ;
 default : break ;
 }
 }
 for ( i = start ;
 i <= end ;
 ++ i ) {
 state [ i ] = entry ;
 }
 if ( * s == ',' ) {
 ++ s ;
 }
 else {
 return * s == 0 ? NULL : s ;
 }
 }
 }