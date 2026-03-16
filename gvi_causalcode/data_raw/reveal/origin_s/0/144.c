static MacroBlock decode_macroblock ( Escape124Context * s , GetBitContext * gb , int * codebook_index , int superblock_index ) {
 unsigned block_index , depth ;
 if ( get_bits1 ( gb ) ) {
 static const char transitions [ 3 ] [ 2 ] = {
 {
 2 , 1 }
 , {
 0 , 2 }
 , {
 1 , 0 }
 }
 ;
 * codebook_index = transitions [ * codebook_index ] [ get_bits1 ( gb ) ] ;
 }
 depth = s -> codebooks [ * codebook_index ] . depth ;
 block_index = depth ? get_bits ( gb , depth ) : 0 ;
 if ( * codebook_index == 1 ) {
 block_index += superblock_index << s -> codebooks [ 1 ] . depth ;
 }
 if ( block_index >= s -> codebooks [ * codebook_index ] . size ) return ( MacroBlock ) {
 {
 0 }
 }
 ;
 return s -> codebooks [ * codebook_index ] . blocks [ block_index ] ;
 }