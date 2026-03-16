void vp9_pack_bitstream ( VP9_COMP * cpi , uint8_t * dest , size_t * size ) {
 uint8_t * data = dest ;
 size_t first_part_size , uncompressed_hdr_size ;
 struct vp9_write_bit_buffer wb = {
 data , 0 }
 ;
 struct vp9_write_bit_buffer saved_wb ;
 write_uncompressed_header ( cpi , & wb ) ;
 saved_wb = wb ;
 vp9_wb_write_literal ( & wb , 0 , 16 ) ;
 uncompressed_hdr_size = vp9_wb_bytes_written ( & wb ) ;
 data += uncompressed_hdr_size ;
 vp9_clear_system_state ( ) ;
 first_part_size = write_compressed_header ( cpi , data ) ;
 data += first_part_size ;
 vp9_wb_write_literal ( & saved_wb , ( int ) first_part_size , 16 ) ;
 data += encode_tiles ( cpi , data ) ;
 * size = data - dest ;
 }