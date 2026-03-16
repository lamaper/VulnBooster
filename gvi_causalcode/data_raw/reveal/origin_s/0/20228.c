static void write_variables ( struct recvbuf * rbufp , int restrict_mask ) {
 const struct ctl_var * v ;
 int ext_var ;
 char * valuep ;
 long val ;
 size_t octets ;
 char * vareqv ;
 const char * t ;
 char * tt ;
 val = 0 ;
 if ( res_associd != 0 ) {
 ctl_error ( CERR_PERMISSION ) ;
 return ;
 }
 rpkt . status = htons ( ctlsysstatus ( ) ) ;
 while ( ( v = ctl_getitem ( sys_var , & valuep ) ) != 0 ) {
 ext_var = 0 ;
 if ( v -> flags & EOV ) {
 if ( ( v = ctl_getitem ( ext_sys_var , & valuep ) ) != 0 ) {
 if ( v -> flags & EOV ) {
 ctl_error ( CERR_UNKNOWNVAR ) ;
 return ;
 }
 ext_var = 1 ;
 }
 else {
 break ;
 }
 }
 if ( ! ( v -> flags & CAN_WRITE ) ) {
 ctl_error ( CERR_PERMISSION ) ;
 return ;
 }
 if ( ! ext_var && ( * valuep == '\0' || ! atoint ( valuep , & val ) ) ) {
 ctl_error ( CERR_BADFMT ) ;
 return ;
 }
 if ( ! ext_var && ( val & ~ LEAP_NOTINSYNC ) != 0 ) {
 ctl_error ( CERR_BADVALUE ) ;
 return ;
 }
 if ( ext_var ) {
 octets = strlen ( v -> text ) + strlen ( valuep ) + 2 ;
 vareqv = emalloc ( octets ) ;
 tt = vareqv ;
 t = v -> text ;
 while ( * t && * t != '=' ) * tt ++ = * t ++ ;
 * tt ++ = '=' ;
 memcpy ( tt , valuep , 1 + strlen ( valuep ) ) ;
 set_sys_var ( vareqv , 1 + strlen ( vareqv ) , v -> flags ) ;
 free ( vareqv ) ;
 }
 else {
 ctl_error ( CERR_UNSPEC ) ;
 return ;
 }
 }
 ctl_flushpkt ( 0 ) ;
 }