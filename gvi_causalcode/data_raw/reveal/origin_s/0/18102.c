bool op_strict ( Oid opno ) {
 RegProcedure funcid = get_opcode ( opno ) ;
 if ( funcid == ( RegProcedure ) InvalidOid ) elog ( ERROR , "operator %u does not exist" , opno ) ;
 return func_strict ( ( Oid ) funcid ) ;
 }