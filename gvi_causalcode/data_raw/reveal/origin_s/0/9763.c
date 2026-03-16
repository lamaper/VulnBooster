static Entity * EntityCreate ( SplinePointList * head , int linecap , int linejoin , real linewidth , real * transform , SplineSet * clippath ) {
 Entity * ent = calloc ( 1 , sizeof ( Entity ) ) ;
 ent -> type = et_splines ;
 ent -> u . splines . splines = head ;
 ent -> u . splines . cap = linecap ;
 ent -> u . splines . join = linejoin ;
 ent -> u . splines . stroke_width = linewidth ;
 ent -> u . splines . fill . col = 0xffffffff ;
 ent -> u . splines . stroke . col = 0xffffffff ;
 ent -> u . splines . fill . opacity = 1.0 ;
 ent -> u . splines . stroke . opacity = 1.0 ;
 ent -> clippath = SplinePointListCopy ( clippath ) ;
 memcpy ( ent -> u . splines . transform , transform , 6 * sizeof ( real ) ) ;
 return ( ent ) ;
 }