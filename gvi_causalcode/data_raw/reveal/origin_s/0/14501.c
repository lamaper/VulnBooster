static void lexstart ( struct vars * v ) {
 prefixes ( v ) ;
 NOERR ( ) ;
 if ( v -> cflags & REG_QUOTE ) {
 assert ( ! ( v -> cflags & ( REG_ADVANCED | REG_EXPANDED | REG_NEWLINE ) ) ) ;
 INTOCON ( L_Q ) ;
 }
 else if ( v -> cflags & REG_EXTENDED ) {
 assert ( ! ( v -> cflags & REG_QUOTE ) ) ;
 INTOCON ( L_ERE ) ;
 }
 else {
 assert ( ! ( v -> cflags & ( REG_QUOTE | REG_ADVF ) ) ) ;
 INTOCON ( L_BRE ) ;
 }
 v -> nexttype = EMPTY ;
 next ( v ) ;
 }