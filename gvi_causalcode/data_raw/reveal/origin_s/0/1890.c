static void dumpnames ( struct alltabs * at , SplineFont * sf , enum fontformat format ) {
 int i , j ;
 struct ttflangname dummy , * cur , * useng = NULL ;
 struct macname * mn ;
 struct other_names * on , * onn ;
 NamTab nt ;
 struct otfname * otfn ;
 struct otffeatname * fn ;
 memset ( & nt , 0 , sizeof ( nt ) ) ;
 nt . encoding_name = at -> map -> enc ;
 nt . format = format ;
 nt . applemode = at -> applemode ;
 nt . strings = tmpfile ( ) ;
 if ( ( format >= ff_ttf && format <= ff_otfdfont ) && ( at -> gi . flags & ttf_flag_symbol ) ) nt . format = ff_ttfsym ;
 memset ( & dummy , 0 , sizeof ( dummy ) ) ;
 for ( cur = sf -> names ;
 cur != NULL ;
 cur = cur -> next ) {
 if ( cur -> lang == 0x409 ) {
 dummy = * cur ;
 useng = cur ;
 break ;
 }
 }
 DefaultTTFEnglishNames ( & dummy , sf ) ;
 for ( i = 0 ;
 i < ttf_namemax ;
 ++ i ) if ( dummy . names [ i ] != NULL ) AddEncodedName ( & nt , dummy . names [ i ] , 0x409 , i ) ;
 for ( cur = sf -> names ;
 cur != NULL ;
 cur = cur -> next ) {
 if ( cur -> lang != 0x409 ) for ( i = 0 ;
 i < ttf_namemax ;
 ++ i ) if ( cur -> names [ i ] != NULL ) AddEncodedName ( & nt , cur -> names [ i ] , cur -> lang , i ) ;
 }
 if ( at -> feat_name != NULL ) {
 for ( i = 0 ;
 at -> feat_name [ i ] . strid != 0 ;
 ++ i ) {
 for ( mn = at -> feat_name [ i ] . mn ;
 mn != NULL ;
 mn = mn -> next ) AddMacName ( & nt , mn , at -> feat_name [ i ] . strid ) ;
 }
 }
 for ( on = at -> other_names ;
 on != NULL ;
 on = onn ) {
 for ( mn = on -> mn ;
 mn != NULL ;
 mn = mn -> next ) AddMacName ( & nt , mn , on -> strid ) ;
 onn = on -> next ;
 chunkfree ( on , sizeof ( * on ) ) ;
 }
 if ( at -> fontstyle_name_strid != 0 && sf -> fontstyle_name != NULL ) {
 for ( otfn = sf -> fontstyle_name ;
 otfn != NULL ;
 otfn = otfn -> next ) AddEncodedName ( & nt , otfn -> name , otfn -> lang , at -> fontstyle_name_strid ) ;
 }
 for ( fn = sf -> feat_names ;
 fn != NULL ;
 fn = fn -> next ) {
 for ( otfn = fn -> names ;
 otfn != NULL ;
 otfn = otfn -> next ) AddEncodedName ( & nt , otfn -> name , otfn -> lang , fn -> nid ) ;
 }
 qsort ( nt . entries , nt . cur , sizeof ( NameEntry ) , compare_entry ) ;
 at -> name = tmpfile ( ) ;
 putshort ( at -> name , 0 ) ;
 putshort ( at -> name , nt . cur ) ;
 putshort ( at -> name , ( 3 + nt . cur * 6 ) * sizeof ( int16 ) ) ;
 for ( i = 0 ;
 i < nt . cur ;
 ++ i ) {
 putshort ( at -> name , nt . entries [ i ] . platform ) ;
 putshort ( at -> name , nt . entries [ i ] . specific ) ;
 putshort ( at -> name , nt . entries [ i ] . lang ) ;
 putshort ( at -> name , nt . entries [ i ] . strid ) ;
 putshort ( at -> name , nt . entries [ i ] . len ) ;
 putshort ( at -> name , nt . entries [ i ] . offset ) ;
 }
 if ( ! ttfcopyfile ( at -> name , nt . strings , ( 3 + nt . cur * 6 ) * sizeof ( int16 ) , "name-data" ) ) at -> error = true ;
 at -> namelen = ftell ( at -> name ) ;
 if ( ( at -> namelen & 3 ) != 0 ) for ( j = 4 - ( at -> namelen & 3 ) ;
 j > 0 ;
 -- j ) putc ( '\0' , at -> name ) ;
 for ( i = 0 ;
 i < ttf_namemax ;
 ++ i ) if ( useng == NULL || dummy . names [ i ] != useng -> names [ i ] ) free ( dummy . names [ i ] ) ;
 free ( nt . entries ) ;
 free ( at -> feat_name ) ;
 }