DSA * DSAparams_dup ( DSA * dsa ) {
 return ASN1_item_dup ( ASN1_ITEM_rptr ( DSAparams ) , dsa ) ;
 }