static ENUM_PTRS_WITH ( device_memory_enum_ptrs , gx_device_memory * mptr ) {
 return ENUM_USING ( st_device_forward , vptr , sizeof ( gx_device_forward ) , index - 3 ) ;
 }