char op_volatile ( Oid opno ) {
 RegProcedure funcid = get_opcode ( opno ) ;
 if ( funcid == ( RegProcedure ) InvalidOid ) elog ( ERROR , "operator %u does not exist" , opno ) ;
 return func_volatile ( ( Oid ) funcid ) ;
 }