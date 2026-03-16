static void insert_mb_into_sb ( SuperBlock * sb , MacroBlock mb , unsigned index ) {
 uint32_t * dst = sb -> pixels32 + index + ( index & - 4 ) ;
 dst [ 0 ] = mb . pixels32 [ 0 ] ;
 dst [ 4 ] = mb . pixels32 [ 1 ] ;
 }