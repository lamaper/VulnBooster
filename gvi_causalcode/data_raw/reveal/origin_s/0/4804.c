static SplinePointList * SplinesFromLayers ( SplineChar * sc , int * flags , int tostroke ) {
 int layer ;
 SplinePointList * head = NULL , * last , * new , * nlast , * temp , * each , * transed ;
 StrokeInfo si ;
 int handle_eraser ;
 real inversetrans [ 6 ] , transform [ 6 ] ;
 int changed ;
 if ( tostroke ) {
 for ( layer = ly_fore ;
 layer < sc -> layer_cnt ;
 ++ layer ) {
 if ( sc -> layers [ layer ] . splines == NULL ) continue ;
 else if ( head == NULL ) head = sc -> layers [ layer ] . splines ;
 else last -> next = sc -> layers [ layer ] . splines ;
 for ( last = sc -> layers [ layer ] . splines ;
 last -> next != NULL ;
 last = last -> next ) ;
 sc -> layers [ layer ] . splines = NULL ;
 }
 return ( head ) ;
 }
 if ( * flags == - 1 ) * flags = PsStrokeFlagsDlg ( ) ;
 if ( * flags & sf_correctdir ) {
 for ( layer = ly_fore ;
 layer < sc -> layer_cnt ;
 ++ layer ) if ( sc -> layers [ layer ] . dofill ) SplineSetsCorrect ( sc -> layers [ layer ] . splines , & changed ) ;
 }
 handle_eraser = * flags & sf_handle_eraser ;
 for ( layer = ly_fore ;
 layer < sc -> layer_cnt ;
 ++ layer ) {
 if ( sc -> layers [ layer ] . dostroke ) {
 memset ( & si , '\0' , sizeof ( si ) ) ;
 si . join = sc -> layers [ layer ] . stroke_pen . linejoin ;
 si . cap = sc -> layers [ layer ] . stroke_pen . linecap ;
 si . radius = sc -> layers [ layer ] . stroke_pen . width / 2.0f ;
 if ( sc -> layers [ layer ] . stroke_pen . width == WIDTH_INHERITED ) si . radius = .5 ;
 if ( si . cap == lc_inherited ) si . cap = lc_butt ;
 if ( si . join == lj_inherited ) si . join = lj_miter ;
 new = NULL ;
 memcpy ( transform , sc -> layers [ layer ] . stroke_pen . trans , 4 * sizeof ( real ) ) ;
 transform [ 4 ] = transform [ 5 ] = 0 ;
 MatInverse ( inversetrans , transform ) ;
 transed = SplinePointListTransform ( SplinePointListCopy ( sc -> layers [ layer ] . splines ) , inversetrans , tpt_AllPoints ) ;
 for ( each = transed ;
 each != NULL ;
 each = each -> next ) {
 temp = SplineSetStroke ( each , & si , sc -> layers [ layer ] . order2 ) ;
 if ( new == NULL ) new = temp ;
 else nlast -> next = temp ;
 if ( temp != NULL ) for ( nlast = temp ;
 nlast -> next != NULL ;
 nlast = nlast -> next ) ;
 }
 new = SplinePointListTransform ( new , transform , tpt_AllPoints ) ;
 SplinePointListsFree ( transed ) ;
 if ( handle_eraser && sc -> layers [ layer ] . stroke_pen . brush . col == 0xffffff ) {
 head = EraseStroke ( sc , head , new ) ;
 last = head ;
 if ( last != NULL ) for ( ;
 last -> next != NULL ;
 last = last -> next ) ;
 }
 else {
 if ( head == NULL ) head = new ;
 else last -> next = new ;
 if ( new != NULL ) for ( last = new ;
 last -> next != NULL ;
 last = last -> next ) ;
 }
 }
 if ( sc -> layers [ layer ] . dofill ) {
 if ( handle_eraser && sc -> layers [ layer ] . fill_brush . col == 0xffffff ) {
 head = EraseStroke ( sc , head , sc -> layers [ layer ] . splines ) ;
 last = head ;
 if ( last != NULL ) for ( ;
 last -> next != NULL ;
 last = last -> next ) ;
 }
 else {
 new = SplinePointListCopy ( sc -> layers [ layer ] . splines ) ;
 if ( head == NULL ) head = new ;
 else last -> next = new ;
 if ( new != NULL ) for ( last = new ;
 last -> next != NULL ;
 last = last -> next ) ;
 }
 }
 }
 return ( head ) ;
 }