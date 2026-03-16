static MIMEFieldSDKHandle * sdk_alloc_field_handle ( TSMBuffer , MIMEHdrImpl * mh ) {
 MIMEFieldSDKHandle * handle = mHandleAllocator . alloc ( ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) handle ) == TS_SUCCESS ) ;
 obj_init_header ( handle , HDR_HEAP_OBJ_FIELD_SDK_HANDLE , sizeof ( MIMEFieldSDKHandle ) , 0 ) ;
 handle -> mh = mh ;
 return handle ;
 }