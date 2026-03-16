static fragment_head * force_reassemble_seq ( reassembly_table * table , packet_info * pinfo , guint32 id ) {
 fragment_head * fd_head ;
 fragment_item * fd_i ;
 fragment_item * last_fd ;
 guint32 dfpos , size , packet_lost , burst_lost , seq_num ;
 guint8 * data ;
 fd_head = fragment_get ( table , pinfo , id , NULL ) ;
 if ( pinfo -> fd -> flags . visited ) {
 if ( fd_head != NULL && fd_head -> flags & FD_DEFRAGMENTED ) {
 return fd_head ;
 }
 else {
 return NULL ;
 }
 }
 if ( fd_head == NULL ) {
 return NULL ;
 }
 packet_lost = 0 ;
 burst_lost = 0 ;
 seq_num = 0 ;
 for ( fd_i = fd_head -> next ;
 fd_i ;
 fd_i = fd_i -> next ) {
 if ( seq_num != fd_i -> offset ) {
 packet_lost += fd_i -> offset - seq_num ;
 if ( ( fd_i -> offset - seq_num ) > burst_lost ) {
 burst_lost = fd_i -> offset - seq_num ;
 }
 }
 seq_num = fd_i -> offset + 1 ;
 }
 size = 0 ;
 last_fd = NULL ;
 for ( fd_i = fd_head -> next ;
 fd_i ;
 fd_i = fd_i -> next ) {
 if ( ! last_fd || last_fd -> offset != fd_i -> offset ) {
 size += fd_i -> len ;
 }
 last_fd = fd_i ;
 }
 data = ( guint8 * ) g_malloc ( size ) ;
 fd_head -> tvb_data = tvb_new_real_data ( data , size , size ) ;
 fd_head -> len = size ;
 dfpos = 0 ;
 last_fd = NULL ;
 for ( fd_i = fd_head -> next ;
 fd_i && fd_i -> len + dfpos <= size ;
 fd_i = fd_i -> next ) {
 if ( fd_i -> len ) {
 if ( ! last_fd || last_fd -> offset != fd_i -> offset ) {
 tvb_memcpy ( fd_i -> tvb_data , data + dfpos , 0 , fd_i -> len ) ;
 dfpos += fd_i -> len ;
 }
 else {
 fd_i -> flags |= FD_OVERLAP ;
 fd_head -> flags |= FD_OVERLAP ;
 if ( ( last_fd -> len != fd_i -> len ) || tvb_memeql ( last_fd -> tvb_data , 0 , tvb_get_ptr ( fd_i -> tvb_data , 0 , last_fd -> len ) , last_fd -> len ) ) {
 fd_i -> flags |= FD_OVERLAPCONFLICT ;
 fd_head -> flags |= FD_OVERLAPCONFLICT ;
 }
 }
 }
 last_fd = fd_i ;
 }
 for ( fd_i = fd_head -> next ;
 fd_i ;
 fd_i = fd_i -> next ) {
 if ( fd_i -> tvb_data ) {
 tvb_free ( fd_i -> tvb_data ) ;
 fd_i -> tvb_data = NULL ;
 }
 }
 fd_head -> flags |= FD_DEFRAGMENTED ;
 fd_head -> reassembled_in = pinfo -> fd -> num ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " (t4-data Reassembled: %d pack lost, %d pack burst lost)" , packet_lost , burst_lost ) ;
 p_t38_packet_conv_info -> packet_lost = packet_lost ;
 p_t38_packet_conv_info -> burst_lost = burst_lost ;
 return fd_head ;
 }