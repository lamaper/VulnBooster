static void CopySFNTAndFixup ( FILE * ttc , FILE * ttf ) {
 int offset = ftell ( ttc ) ;
 int val , table_cnt , i ;
 fseek ( ttf , 0 , SEEK_SET ) ;
 val = getlong ( ttf ) ;
 putlong ( ttc , val ) ;
 table_cnt = getushort ( ttf ) ;
 putshort ( ttc , table_cnt ) ;
 val = getushort ( ttf ) ;
 putshort ( ttc , val ) ;
 val = getushort ( ttf ) ;
 putshort ( ttc , val ) ;
 val = getushort ( ttf ) ;
 putshort ( ttc , val ) ;
 for ( i = 0 ;
 i < table_cnt ;
 ++ i ) {
 val = getlong ( ttf ) ;
 putlong ( ttc , val ) ;
 val = getlong ( ttf ) ;
 putlong ( ttc , val ) ;
 val = getlong ( ttf ) ;
 putlong ( ttc , val + offset ) ;
 val = getlong ( ttf ) ;
 putlong ( ttc , val ) ;
 }
 while ( ( val = getc ( ttf ) ) != EOF ) putc ( val , ttc ) ;
 fclose ( ttf ) ;
 if ( ftell ( ttc ) & 1 ) putc ( '\0' , ttc ) ;
 if ( ftell ( ttc ) & 2 ) putshort ( ttc , 0 ) ;
 }