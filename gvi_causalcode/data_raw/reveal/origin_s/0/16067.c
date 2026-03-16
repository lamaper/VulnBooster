static char * _catkey ( char * buffer , int32_t set_num , int32_t msg_num ) {
 int32_t i = 0 ;
 i = T_CString_integerToString ( buffer , set_num , 10 ) ;
 buffer [ i ++ ] = SEPARATOR ;
 T_CString_integerToString ( buffer + i , msg_num , 10 ) ;
 return buffer ;
 }