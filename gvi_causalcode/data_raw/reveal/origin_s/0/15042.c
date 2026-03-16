float * qcms_chain_transform ( qcms_profile * in , qcms_profile * out , float * src , float * dest , size_t lutSize ) {
 struct qcms_modular_transform * transform_list = qcms_modular_transform_create ( in , out ) ;
 if ( transform_list != NULL ) {
 float * lut = qcms_modular_transform_data ( transform_list , src , dest , lutSize / 3 ) ;
 qcms_modular_transform_release ( transform_list ) ;
 return lut ;
 }
 return NULL ;
 }