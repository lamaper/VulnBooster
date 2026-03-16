static void encode_mv_component ( vp9_writer * w , int comp , const nmv_component * mvcomp , int usehp ) {
 int offset ;
 const int sign = comp < 0 ;
 const int mag = sign ? - comp : comp ;
 const int mv_class = vp9_get_mv_class ( mag - 1 , & offset ) ;
 const int d = offset >> 3 ;
 const int fr = ( offset >> 1 ) & 3 ;
 const int hp = offset & 1 ;
 assert ( comp != 0 ) ;
 vp9_write ( w , sign , mvcomp -> sign ) ;
 vp9_write_token ( w , vp9_mv_class_tree , mvcomp -> classes , & mv_class_encodings [ mv_class ] ) ;
 if ( mv_class == MV_CLASS_0 ) {
 vp9_write_token ( w , vp9_mv_class0_tree , mvcomp -> class0 , & mv_class0_encodings [ d ] ) ;
 }
 else {
 int i ;
 const int n = mv_class + CLASS0_BITS - 1 ;
 for ( i = 0 ;
 i < n ;
 ++ i ) vp9_write ( w , ( d >> i ) & 1 , mvcomp -> bits [ i ] ) ;
 }
 vp9_write_token ( w , vp9_mv_fp_tree , mv_class == MV_CLASS_0 ? mvcomp -> class0_fp [ d ] : mvcomp -> fp , & mv_fp_encodings [ fr ] ) ;
 if ( usehp ) vp9_write ( w , hp , mv_class == MV_CLASS_0 ? mvcomp -> class0_hp : mvcomp -> hp ) ;
 }