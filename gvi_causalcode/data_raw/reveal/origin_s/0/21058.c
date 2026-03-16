int ReadOffset ( ArchiveHandle * AH , pgoff_t * o ) {
 int i ;
 int off ;
 int offsetFlg ;
 * o = 0 ;
 if ( AH -> version < K_VERS_1_7 ) {
 i = ReadInt ( AH ) ;
 if ( i < 0 ) return K_OFFSET_POS_NOT_SET ;
 else if ( i == 0 ) return K_OFFSET_NO_DATA ;
 * o = ( pgoff_t ) i ;
 return K_OFFSET_POS_SET ;
 }
 offsetFlg = ( * AH -> ReadBytePtr ) ( AH ) & 0xFF ;
 switch ( offsetFlg ) {
 case K_OFFSET_POS_NOT_SET : case K_OFFSET_NO_DATA : case K_OFFSET_POS_SET : break ;
 default : exit_horribly ( modulename , "unexpected data offset flag %d\n" , offsetFlg ) ;
 }
 for ( off = 0 ;
 off < AH -> offSize ;
 off ++ ) {
 if ( off < sizeof ( pgoff_t ) ) * o |= ( ( pgoff_t ) ( ( * AH -> ReadBytePtr ) ( AH ) ) ) << ( off * 8 ) ;
 else {
 if ( ( * AH -> ReadBytePtr ) ( AH ) != 0 ) exit_horribly ( modulename , "file offset in dump file is too large\n" ) ;
 }
 }
 return offsetFlg ;
 }