void SFSplinesFromLayers ( SplineFont * sf , int tostroke ) {
 int i , layer ;
 int flags = - 1 ;
 Layer * new ;
 CharViewBase * cv ;
 for ( i = 0 ;
 i < sf -> glyphcnt ;
 ++ i ) if ( sf -> glyphs [ i ] != NULL ) {
 SplineChar * sc = sf -> glyphs [ i ] ;
 SplineSet * splines = SplinesFromLayers ( sc , & flags , tostroke ) ;
 RefChar * head = NULL , * last = NULL ;
 for ( layer = ly_fore ;
 layer < sc -> layer_cnt ;
 ++ layer ) {
 if ( head == NULL ) head = last = sc -> layers [ layer ] . refs ;
 else last -> next = sc -> layers [ layer ] . refs ;
 if ( last != NULL ) while ( last -> next != NULL ) last = last -> next ;
 sc -> layers [ layer ] . refs = NULL ;
 }
 new = calloc ( 2 , sizeof ( Layer ) ) ;
 new [ ly_back ] = sc -> layers [ ly_back ] ;
 memset ( & sc -> layers [ ly_back ] , 0 , sizeof ( Layer ) ) ;
 LayerDefault ( & new [ ly_fore ] ) ;
 new [ ly_fore ] . splines = splines ;
 new [ ly_fore ] . refs = head ;
 for ( layer = ly_fore ;
 layer < sc -> layer_cnt ;
 ++ layer ) {
 SplinePointListsMDFree ( sc , sc -> layers [ layer ] . splines ) ;
 RefCharsFree ( sc -> layers [ layer ] . refs ) ;
 ImageListsFree ( sc -> layers [ layer ] . images ) ;
 }
 free ( sc -> layers ) ;
 sc -> layers = new ;
 sc -> layer_cnt = 2 ;
 for ( cv = sc -> views ;
 cv != NULL ;
 cv = cv -> next ) {
 cv -> layerheads [ dm_back ] = & sc -> layers [ ly_back ] ;
 cv -> layerheads [ dm_fore ] = & sc -> layers [ ly_fore ] ;
 }
 }
 SFReinstanciateRefs ( sf ) ;
 }