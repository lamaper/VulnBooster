int vp9_alloc_internal_frame_buffers ( InternalFrameBufferList * list ) {
 assert ( list != NULL ) ;
 vp9_free_internal_frame_buffers ( list ) ;
 list -> num_internal_frame_buffers = VP9_MAXIMUM_REF_BUFFERS + VPX_MAXIMUM_WORK_BUFFERS ;
 list -> int_fb = ( InternalFrameBuffer * ) vpx_calloc ( list -> num_internal_frame_buffers , sizeof ( * list -> int_fb ) ) ;
 return ( list -> int_fb == NULL ) ;
 }