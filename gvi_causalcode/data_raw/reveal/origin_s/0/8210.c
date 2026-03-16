static void copy_bits ( PutBitContext * pb , const uint8_t * data , int size , GetBitContext * gb , int nbits ) {
 int rmn_bytes , rmn_bits ;
 rmn_bits = rmn_bytes = get_bits_left ( gb ) ;
 if ( rmn_bits < nbits ) return ;
 if ( nbits > pb -> size_in_bits - put_bits_count ( pb ) ) return ;
 rmn_bits &= 7 ;
 rmn_bytes >>= 3 ;
 if ( ( rmn_bits = FFMIN ( rmn_bits , nbits ) ) > 0 ) put_bits ( pb , rmn_bits , get_bits ( gb , rmn_bits ) ) ;
 avpriv_copy_bits ( pb , data + size - rmn_bytes , FFMIN ( nbits - rmn_bits , rmn_bytes << 3 ) ) ;
 }