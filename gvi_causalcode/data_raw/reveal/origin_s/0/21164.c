static int ivi_huff_desc_cmp ( const IVIHuffDesc * desc1 , const IVIHuffDesc * desc2 ) {
 return desc1 -> num_rows != desc2 -> num_rows || memcmp ( desc1 -> xbits , desc2 -> xbits , desc1 -> num_rows ) ;
 }