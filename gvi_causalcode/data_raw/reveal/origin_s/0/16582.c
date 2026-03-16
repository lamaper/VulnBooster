SplinePointList * SplinesFromEntityChar ( EntityChar * ec , int * flags , int is_stroked ) {
 Entity * ent , * next ;
 SplinePointList * head = NULL , * last , * new , * nlast , * temp , * each , * transed ;
 StrokeInfo si ;
 real inversetrans [ 6 ] ;
 int handle_eraser = false ;
 int ask = false ;
 EntityDefaultStrokeFill ( ec -> splines ) ;
 if ( ! is_stroked ) {
 if ( * flags == - 1 ) {
 for ( ent = ec -> splines ;
 ent != NULL ;
 ent = ent -> next ) {
 if ( ent -> type == et_splines && ( ent -> u . splines . fill . col == 0xffffff || ( ent -> u . splines . stroke_width != 0 && ent -> u . splines . stroke . col != 0xffffffff ) ) ) {
 ask = true ;
 break ;
 }
 }
 if ( ask ) * flags = PsStrokeFlagsDlg ( ) ;
 }
 if ( * flags & sf_correctdir ) EntityCharCorrectDir ( ec ) ;
 handle_eraser = * flags != - 1 && ( * flags & sf_handle_eraser ) ;
 if ( handle_eraser ) ec -> splines = EntityReverse ( ec -> splines ) ;
 }
 for ( ent = ec -> splines ;
 ent != NULL ;
 ent = next ) {
 next = ent -> next ;
 if ( ent -> type == et_splines && is_stroked ) {
 if ( head == NULL ) head = ent -> u . splines . splines ;
 else last -> next = ent -> u . splines . splines ;
 if ( ent -> u . splines . splines != NULL ) for ( last = ent -> u . splines . splines ;
 last -> next != NULL ;
 last = last -> next ) ;
 ent -> u . splines . splines = NULL ;
 }
 else if ( ent -> type == et_splines ) {
 if ( ent -> u . splines . stroke . col != 0xffffffff && ( ent -> u . splines . fill . col == 0xffffffff || ent -> u . splines . stroke_width != 0 ) ) {
 memset ( & si , '\0' , sizeof ( si ) ) ;
 si . join = ent -> u . splines . join ;
 si . cap = ent -> u . splines . cap ;
 si . radius = ent -> u . splines . stroke_width / 2 ;
 if ( ent -> u . splines . stroke_width == WIDTH_INHERITED ) si . radius = .5 ;
 if ( si . cap == lc_inherited ) si . cap = lc_butt ;
 if ( si . join == lj_inherited ) si . join = lj_miter ;
 new = NULL ;
 MatInverse ( inversetrans , ent -> u . splines . transform ) ;
 transed = SplinePointListTransform ( SplinePointListCopy ( ent -> u . splines . splines ) , inversetrans , tpt_AllPoints ) ;
 for ( each = transed ;
 each != NULL ;
 each = each -> next ) {
 temp = SplineSetStroke ( each , & si , false ) ;
 if ( new == NULL ) new = temp ;
 else nlast -> next = temp ;
 if ( temp != NULL ) for ( nlast = temp ;
 nlast -> next != NULL ;
 nlast = nlast -> next ) ;
 }
 new = SplinePointListTransform ( new , ent -> u . splines . transform , tpt_AllPoints ) ;
 SplinePointListsFree ( transed ) ;
 if ( handle_eraser && ent -> u . splines . stroke . col == 0xffffff ) {
 head = EraseStroke ( ec -> sc , head , new ) ;
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
 if ( ent -> u . splines . fill . col == 0xffffffff && ent -> u . splines . stroke . col != 0xffffffff ) SplinePointListsFree ( ent -> u . splines . splines ) ;
 else if ( handle_eraser && ent -> u . splines . fill . col == 0xffffff ) {
 head = EraseStroke ( ec -> sc , head , ent -> u . splines . splines ) ;
 last = head ;
 if ( last != NULL ) for ( ;
 last -> next != NULL ;
 last = last -> next ) ;
 }
 else {
 new = ent -> u . splines . splines ;
 if ( head == NULL ) head = new ;
 else last -> next = new ;
 if ( new != NULL ) for ( last = new ;
 last -> next != NULL ;
 last = last -> next ) ;
 }
 }
 SplinePointListsFree ( ent -> clippath ) ;
 free ( ent ) ;
 }
 return ( head ) ;
 }