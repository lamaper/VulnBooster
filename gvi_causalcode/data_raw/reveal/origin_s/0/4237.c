static inline void loco_update_rice_param ( RICEContext * r , int val ) {
 r -> sum += val ;
 r -> count ++ ;
 if ( r -> count == 16 ) {
 r -> sum >>= 1 ;
 r -> count >>= 1 ;
 }
 }