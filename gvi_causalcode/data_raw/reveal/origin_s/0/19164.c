static void dump_search_desc ( KEYDB_HANDLE hd , const char * text , KEYDB_SEARCH_DESC * desc , size_t ndesc ) {
 int n ;
 const char * s ;
 for ( n = 0 ;
 n < ndesc ;
 n ++ ) {
 switch ( desc [ n ] . mode ) {
 case KEYDB_SEARCH_MODE_NONE : s = "none" ;
 break ;
 case KEYDB_SEARCH_MODE_EXACT : s = "exact" ;
 break ;
 case KEYDB_SEARCH_MODE_SUBSTR : s = "substr" ;
 break ;
 case KEYDB_SEARCH_MODE_MAIL : s = "mail" ;
 break ;
 case KEYDB_SEARCH_MODE_MAILSUB : s = "mailsub" ;
 break ;
 case KEYDB_SEARCH_MODE_MAILEND : s = "mailend" ;
 break ;
 case KEYDB_SEARCH_MODE_WORDS : s = "words" ;
 break ;
 case KEYDB_SEARCH_MODE_SHORT_KID : s = "short_kid" ;
 break ;
 case KEYDB_SEARCH_MODE_LONG_KID : s = "long_kid" ;
 break ;
 case KEYDB_SEARCH_MODE_FPR16 : s = "fpr16" ;
 break ;
 case KEYDB_SEARCH_MODE_FPR20 : s = "fpr20" ;
 break ;
 case KEYDB_SEARCH_MODE_FPR : s = "fpr" ;
 break ;
 case KEYDB_SEARCH_MODE_ISSUER : s = "issuer" ;
 break ;
 case KEYDB_SEARCH_MODE_ISSUER_SN : s = "issuer_sn" ;
 break ;
 case KEYDB_SEARCH_MODE_SN : s = "sn" ;
 break ;
 case KEYDB_SEARCH_MODE_SUBJECT : s = "subject" ;
 break ;
 case KEYDB_SEARCH_MODE_KEYGRIP : s = "keygrip" ;
 break ;
 case KEYDB_SEARCH_MODE_FIRST : s = "first" ;
 break ;
 case KEYDB_SEARCH_MODE_NEXT : s = "next" ;
 break ;
 default : s = "?" ;
 break ;
 }
 if ( ! n ) log_debug ( "%s: mode=%s (hd=%p)" , text , s , hd ) ;
 else log_debug ( "%*s mode=%s" , ( int ) strlen ( text ) , "" , s ) ;
 if ( desc [ n ] . mode == KEYDB_SEARCH_MODE_LONG_KID ) log_printf ( " %08lX%08lX" , ( unsigned long ) desc [ n ] . u . kid [ 0 ] , ( unsigned long ) desc [ n ] . u . kid [ 1 ] ) ;
 else if ( desc [ n ] . mode == KEYDB_SEARCH_MODE_SHORT_KID ) log_printf ( " %08lX" , ( unsigned long ) desc [ n ] . u . kid [ 1 ] ) ;
 else if ( desc [ n ] . mode == KEYDB_SEARCH_MODE_SUBSTR ) log_printf ( " '%s'" , desc [ n ] . u . name ) ;
 }
 }