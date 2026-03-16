static int dumpcff ( struct alltabs * at , SplineFont * sf , enum fontformat format , FILE * cff ) {
 int ret ;
 if ( format == ff_cff ) {
 AssignTTFGlyph ( & at -> gi , sf , at -> map , true ) ;
 ret = dumptype2glyphs ( sf , at ) ;
 }
 else {
 SFDummyUpCIDs ( & at -> gi , sf ) ;
 ret = dumpcidglyphs ( sf , at ) ;
 free ( sf -> glyphs ) ;
 sf -> glyphs = NULL ;
 sf -> glyphcnt = sf -> glyphmax = 0 ;
 }
 free ( at -> gi . bygid ) ;
 if ( ! ret ) at -> error = true ;
 else if ( at -> gi . flags & ps_flag_nocffsugar ) {
 if ( ! ttfcopyfile ( cff , at -> cfff , 0 , "CFF" ) ) at -> error = true ;
 }
 else {
 long len ;
 char buffer [ 80 ] ;
 fprintf ( cff , "%%!PS-Adobe-3.0 Resource-FontSet\n" ) ;
 fprintf ( cff , "%%%%DocumentNeedResources:ProcSet (FontSetInit)\n" ) ;
 fprintf ( cff , "%%%%Title: (FontSet/%s)\n" , sf -> fontname ) ;
 fprintf ( cff , "%%%%EndComments\n" ) ;
 fprintf ( cff , "%%%%IncludeResource: ProcSet(FontSetInit)\n" ) ;
 fprintf ( cff , "%%%%BeginResource: FontSet(%s)\n" , sf -> fontname ) ;
 fprintf ( cff , "/FontSetInit /ProcSet findresource begin\n" ) ;
 fseek ( at -> cfff , 0 , SEEK_END ) ;
 len = ftell ( at -> cfff ) ;
 rewind ( at -> cfff ) ;
 sprintf ( buffer , "/%s %ld StartData\n" , sf -> fontname , len ) ;
 fprintf ( cff , "%%%%BeginData: %ld Binary Bytes\n" , ( long ) ( len + strlen ( buffer ) ) ) ;
 fputs ( buffer , cff ) ;
 if ( ! ttfcopyfile ( cff , at -> cfff , ftell ( cff ) , "CFF" ) ) at -> error = true ;
 fprintf ( cff , "\n%%%%EndData\n" ) ;
 fprintf ( cff , "%%%%EndResource\n" ) ;
 fprintf ( cff , "%%%%EOF\n" ) ;
 }
 return ( ! at -> error ) ;
 }