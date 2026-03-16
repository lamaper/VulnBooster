static int _reload_python_objects ( PyObject * module ) {
 struct module_state * state = GETSTATE ( module ) ;
 if ( _reload_object ( & state -> Binary , "bson.binary" , "Binary" ) || _reload_object ( & state -> Code , "bson.code" , "Code" ) || _reload_object ( & state -> ObjectId , "bson.objectid" , "ObjectId" ) || _reload_object ( & state -> DBRef , "bson.dbref" , "DBRef" ) || _reload_object ( & state -> Timestamp , "bson.timestamp" , "Timestamp" ) || _reload_object ( & state -> MinKey , "bson.min_key" , "MinKey" ) || _reload_object ( & state -> MaxKey , "bson.max_key" , "MaxKey" ) || _reload_object ( & state -> UTC , "bson.tz_util" , "utc" ) || _reload_object ( & state -> RECompile , "re" , "compile" ) ) {
 return 1 ;
 }
 if ( _reload_object ( & state -> UUID , "uuid" , "UUID" ) == 1 ) {
 state -> UUID = NULL ;
 PyErr_Clear ( ) ;
 }
 state -> REType = PyObject_CallFunction ( state -> RECompile , "O" , # if PY_MAJOR_VERSION >= 3 PyBytes_FromString ( "" ) ) -> ob_type ;


 }