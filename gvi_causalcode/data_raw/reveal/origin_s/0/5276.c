static int get_para_features ( KVMState * s ) {
 int i , features = 0 ;
 for ( i = 0 ;
 i < ARRAY_SIZE ( para_features ) ;
 i ++ ) {
 if ( kvm_check_extension ( s , para_features [ i ] . cap ) ) {
 features |= ( 1 << para_features [ i ] . feature ) ;
 }
 }
 return features ;
 }