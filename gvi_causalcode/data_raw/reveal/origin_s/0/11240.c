void EntityDefaultStrokeFill ( Entity * ent ) {
 while ( ent != NULL ) {
 if ( ent -> type == et_splines && ent -> u . splines . stroke . col == 0xffffffff && ent -> u . splines . fill . col == 0xffffffff ) {
 SplineSet * spl ;
 int all = 1 ;
 for ( spl = ent -> u . splines . splines ;
 spl != NULL ;
 spl = spl -> next ) if ( spl -> first -> prev != NULL ) {
 all = false ;
 break ;
 }
 if ( all && ent -> u . splines . splines != NULL && ( ent -> u . splines . stroke_width == 0 || ent -> u . splines . stroke_width == WIDTH_INHERITED ) ) ent -> u . splines . stroke_width = 40 ;
 if ( ent -> u . splines . stroke_width == 0 || ent -> u . splines . stroke_width == WIDTH_INHERITED ) ent -> u . splines . fill . col = COLOR_INHERITED ;
 else ent -> u . splines . stroke . col = COLOR_INHERITED ;
 }
 ent = ent -> next ;
 }
 }