static int dsa_cb ( int operation , ASN1_VALUE * * pval , const ASN1_ITEM * it , void * exarg ) {
 if ( operation == ASN1_OP_NEW_PRE ) {
 * pval = ( ASN1_VALUE * ) DSA_new ( ) ;
 if ( * pval ) return 2 ;
 return 0 ;
 }
 else if ( operation == ASN1_OP_FREE_PRE ) {
 DSA_free ( ( DSA * ) * pval ) ;
 * pval = NULL ;
 return 2 ;
 }
 return 1 ;
 }