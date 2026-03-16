VIR_ONCE_GLOBAL_INIT ( qemuAgent ) # if DEBUG_RAW_IO # include < c - ctype . h > static char * qemuAgentEscapeNonPrintable ( const char * text ) {
 size_t i ;
 virBuffer buf = VIR_BUFFER_INITIALIZER ;
 for ( i = 0 ;
 text [ i ] != '\0' ;
 i ++ ) {
 if ( text [ i ] == '\\' ) virBufferAddLit ( & buf , "\\\\" ) ;
 else if ( c_isprint ( text [ i ] ) || text [ i ] == '\n' || ( text [ i ] == '\r' && text [ i + 1 ] == '\n' ) ) virBufferAddChar ( & buf , text [ i ] ) ;
 else virBufferAsprintf ( & buf , "\\x%02x" , text [ i ] ) ;
 }
 return virBufferContentAndReset ( & buf ) ;
 }

 qemuAgentPtr mon = obj ;
 VIR_DEBUG ( "mon=%p" , mon ) ;
 if ( mon -> cb && mon -> cb -> destroy ) ( mon -> cb -> destroy ) ( mon , mon -> vm ) ;
 virCondDestroy ( & mon -> notify ) ;
 VIR_FREE ( mon -> buffer ) ;
 virResetError ( & mon -> lastError ) ;
 }