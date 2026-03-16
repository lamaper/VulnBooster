int WriteTTC ( const char * filename , struct sflist * sfs , enum fontformat format , enum bitmapformat bf , int flags , int layer , enum ttc_flags ttcflags ) {
 struct sflist * sfitem , * sfi2 ;
 int ok = 1 ;
 FILE * ttc ;
 int cnt , offset ;
 int dobruteforce ;
 struct alltabs * ret ;
 SplineFont dummysf ;
 if ( strstr ( filename , "://" ) != NULL ) {
 if ( ( ttc = tmpfile ( ) ) == NULL ) return ( 0 ) ;
 }
 else {
 if ( ( ttc = fopen ( filename , "wb+" ) ) == NULL ) return ( 0 ) ;
 }
 format = ( ttcflags & ttc_flag_cff ) ? ff_otf : ff_ttf ;
 dobruteforce = true ;
 if ( ( ttcflags & ttc_flag_trymerge ) && bf == bf_none ) {
 dobruteforce = false ;
 ret = ttc_prep ( sfs , format , bf , flags , layer , & dummysf ) ;
 if ( ret == NULL ) dobruteforce = true ;
 else ttc_dump ( ttc , ret , format , flags , ttcflags ) ;
 free ( ret ) ;
 }
 if ( dobruteforce ) {
 for ( sfitem = sfs , cnt = 0 ;
 sfitem != NULL ;
 sfitem = sfitem -> next , ++ cnt ) {
 sfitem -> tempttf = tmpfile ( ) ;
 if ( sfitem -> tempttf == NULL ) ok = 0 ;
 else ok = _WriteTTFFont ( sfitem -> tempttf , sfitem -> sf , format , sfitem -> sizes , bf , flags & ~ ttf_flag_dummyDSIG , sfitem -> map , layer ) ;
 if ( ! ok ) {
 for ( sfi2 = sfs ;
 sfi2 != NULL ;
 sfi2 = sfi2 -> next ) if ( sfi2 -> tempttf != NULL ) fclose ( sfi2 -> tempttf ) ;
 fclose ( ttc ) ;
 return ( true ) ;
 }
 fseek ( sfitem -> tempttf , 0 , SEEK_END ) ;
 sfitem -> len = ftell ( sfitem -> tempttf ) ;
 }
 putlong ( ttc , CHR ( 't' , 't' , 'c' , 'f' ) ) ;
 if ( flags & ttf_flag_dummyDSIG ) {
 putlong ( ttc , 0x00020000 ) ;
 offset = 4 * ( 3 + cnt + 4 ) ;
 }
 else {
 putlong ( ttc , 0x00010000 ) ;
 offset = 4 * ( 3 + cnt ) ;
 }
 putlong ( ttc , cnt ) ;
 for ( sfitem = sfs ;
 sfitem != NULL ;
 sfitem = sfitem -> next ) {
 putlong ( ttc , offset ) ;
 offset += ( ( sfitem -> len + 3 ) >> 2 ) << 2 ;
 }
 if ( flags & ttf_flag_dummyDSIG ) {
 putlong ( ttc , CHR ( 'D' , 'S' , 'I' , 'G' ) ) ;
 putlong ( ttc , 8 ) ;
 putlong ( ttc , 0x00000001 ) ;
 putlong ( ttc , 0 ) ;
 }
 for ( sfitem = sfs ;
 sfitem != NULL ;
 sfitem = sfitem -> next ) CopySFNTAndFixup ( ttc , sfitem -> tempttf ) ;
 if ( ftell ( ttc ) != offset ) IError ( "Miscalculated offsets in ttc" ) ;
 }
 else if ( strstr ( filename , "://" ) != NULL && ok ) ok = URLFromFile ( filename , ttc ) ;
 if ( ferror ( ttc ) ) ok = false ;
 if ( fclose ( ttc ) == - 1 ) ok = false ;
 if ( ! ok ) LogError ( _ ( "Something went wrong" ) ) ;
 return ( ok ) ;
 }