static FT_Error cid_read_subrs ( CID_Face face ) {
 CID_FaceInfo cid = & face -> cid ;
 FT_Memory memory = face -> root . memory ;
 FT_Stream stream = face -> cid_stream ;
 FT_Error error ;
 FT_Int n ;
 CID_Subrs subr ;
 FT_UInt max_offsets = 0 ;
 FT_ULong * offsets = 0 ;
 PSAux_Service psaux = ( PSAux_Service ) face -> psaux ;
 if ( FT_NEW_ARRAY ( face -> subrs , cid -> num_dicts ) ) goto Exit ;
 subr = face -> subrs ;
 for ( n = 0 ;
 n < cid -> num_dicts ;
 n ++ , subr ++ ) {
 CID_FaceDict dict = cid -> font_dicts + n ;
 FT_Int lenIV = dict -> private_dict . lenIV ;
 FT_UInt count , num_subrs = dict -> num_subrs ;
 FT_ULong data_len ;
 FT_Byte * p ;
 if ( num_subrs == FT_UINT_MAX ) {
 error = FT_THROW ( Syntax_Error ) ;
 goto Fail ;
 }
 if ( num_subrs + 1 > max_offsets ) {
 FT_UInt new_max = FT_PAD_CEIL ( num_subrs + 1 , 4 ) ;
 if ( new_max <= max_offsets ) {
 error = FT_THROW ( Syntax_Error ) ;
 goto Fail ;
 }
 if ( FT_RENEW_ARRAY ( offsets , max_offsets , new_max ) ) goto Fail ;
 max_offsets = new_max ;
 }
 if ( FT_STREAM_SEEK ( cid -> data_offset + dict -> subrmap_offset ) || FT_FRAME_ENTER ( ( num_subrs + 1 ) * dict -> sd_bytes ) ) goto Fail ;
 p = ( FT_Byte * ) stream -> cursor ;
 for ( count = 0 ;
 count <= num_subrs ;
 count ++ ) offsets [ count ] = cid_get_offset ( & p , ( FT_Byte ) dict -> sd_bytes ) ;
 FT_FRAME_EXIT ( ) ;
 for ( count = 1 ;
 count <= num_subrs ;
 count ++ ) if ( offsets [ count - 1 ] > offsets [ count ] ) goto Fail ;
 data_len = offsets [ num_subrs ] - offsets [ 0 ] ;
 if ( FT_NEW_ARRAY ( subr -> code , num_subrs + 1 ) || FT_ALLOC ( subr -> code [ 0 ] , data_len ) ) goto Fail ;
 if ( FT_STREAM_SEEK ( cid -> data_offset + offsets [ 0 ] ) || FT_STREAM_READ ( subr -> code [ 0 ] , data_len ) ) goto Fail ;
 for ( count = 1 ;
 count <= num_subrs ;
 count ++ ) {
 FT_ULong len ;
 len = offsets [ count ] - offsets [ count - 1 ] ;
 subr -> code [ count ] = subr -> code [ count - 1 ] + len ;
 }
 if ( lenIV >= 0 ) {
 for ( count = 0 ;
 count < num_subrs ;
 count ++ ) {
 FT_ULong len ;
 len = offsets [ count + 1 ] - offsets [ count ] ;
 psaux -> t1_decrypt ( subr -> code [ count ] , len , 4330 ) ;
 }
 }
 subr -> num_subrs = num_subrs ;
 }
 Exit : FT_FREE ( offsets ) ;
 return error ;
 Fail : if ( face -> subrs ) {
 for ( n = 0 ;
 n < cid -> num_dicts ;
 n ++ ) {
 if ( face -> subrs [ n ] . code ) FT_FREE ( face -> subrs [ n ] . code [ 0 ] ) ;
 FT_FREE ( face -> subrs [ n ] . code ) ;
 }
 FT_FREE ( face -> subrs ) ;
 }
 goto Exit ;
 }