static int Asn1SequenceAppend ( Asn1Generic * seq , Asn1Generic * node ) {
 Asn1Generic * it , * new_container ;
 if ( seq -> data == NULL ) {
 seq -> data = node ;
 return 0 ;
 }
 new_container = Asn1GenericNew ( ) ;
 if ( new_container == NULL ) return - 1 ;
 new_container -> data = node ;
 for ( it = seq ;
 it -> next != NULL ;
 it = it -> next ) ;
 it -> next = new_container ;
 return 0 ;
 }