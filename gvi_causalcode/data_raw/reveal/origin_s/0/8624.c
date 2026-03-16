static void ttc_perfonttables ( struct alltabs * all , int me , int mainpos , enum fontformat format ) {
 struct alltabs * at = & all [ me ] ;
 struct alltabs * main = & all [ mainpos ] ;
 SplineFont * sf = at -> sf ;
 struct ttf_table * tab ;
 at -> gi . xmin = main -> gi . xmin ;
 at -> gi . xmax = main -> gi . xmax ;
 at -> gi . ymin = main -> gi . ymin ;
 at -> gi . ymax = main -> gi . ymax ;
 at -> gi . glyph_len = main -> gi . glyph_len ;
 at -> gi . gcnt = main -> maxp . numGlyphs ;
 sethead ( & at -> head , sf , at , format , NULL ) ;
 memcpy ( at -> head . modtime , main -> head . modtime , sizeof ( at -> head . modtime ) ) ;
 memcpy ( at -> head . createtime , at -> head . modtime , sizeof ( at -> head . modtime ) ) ;
 initATTables ( at , sf , format ) ;
 if ( format == ff_ttf ) {
 if ( sf -> gasp_cnt != 0 || ! SFHasInstructions ( sf ) ) dumpgasp ( at , sf ) ;
 at -> fpgmf = checkdupstoredtable ( sf , CHR ( 'f' , 'p' , 'g' , 'm' ) , & at -> fpgmlen , all , me ) ;
 at -> prepf = checkdupstoredtable ( sf , CHR ( 'p' , 'r' , 'e' , 'p' ) , & at -> preplen , all , me ) ;
 at -> cvtf = checkdupstoredtable ( sf , CHR ( 'c' , 'v' , 't' , ' ' ) , & at -> cvtlen , all , me ) ;
 }
 for ( tab = sf -> ttf_tab_saved ;
 tab != NULL ;
 tab = tab -> next ) tab -> temp = dumpsavedtable ( tab ) ;
 {
 int cnt = sf -> glyphcnt ;
 SplineChar * * g = sf -> glyphs ;
 int * bygid = at -> gi . bygid ;
 sf -> glyphcnt = main -> sf -> glyphcnt ;
 sf -> glyphs = main -> sf -> glyphs ;
 at -> gi . bygid = main -> gi . bygid ;
 dumppost ( at , sf , format ) ;
 sf -> glyphcnt = cnt ;
 sf -> glyphs = g ;
 at -> gi . bygid = bygid ;
 }
 dumpcmap ( at , sf , format ) ;
 redohead ( at ) ;
 pfed_dump ( at , sf ) ;
 tex_dump ( at , sf ) ;
 if ( format == ff_ttf ) {
 at -> loca = ( void * ) ( intpt ) - 1 ;
 at -> localen = mainpos ;
 at -> gi . glyphs = ( void * ) ( intpt ) - 1 ;
 at -> gi . glyph_len = mainpos ;
 }
 else {
 at -> cfff = ( void * ) ( intpt ) - 1 ;
 at -> cfflen = mainpos ;
 }
 at -> fftmf = ( void * ) ( intpt ) - 1 ;
 at -> fftmlen = mainpos ;
 at -> hheadf = ( void * ) ( intpt ) - 1 ;
 at -> hheadlen = mainpos ;
 at -> gi . hmtx = ( void * ) ( intpt ) - 1 ;
 at -> gi . hmtxlen = mainpos ;
 at -> maxpf = ( void * ) ( intpt ) - 1 ;
 at -> maxplen = mainpos ;
 if ( all [ mainpos ] . vheadf != NULL ) {
 at -> vheadf = ( void * ) ( intpt ) - 1 ;
 at -> vheadlen = mainpos ;
 at -> gi . vmtx = ( void * ) ( intpt ) - 1 ;
 at -> gi . vmtxlen = mainpos ;
 }
 free ( at -> gi . bygid ) ;
 }