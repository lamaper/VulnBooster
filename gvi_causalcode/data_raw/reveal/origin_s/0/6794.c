void initkerberos ( void ) # endif {
 PyObject * m , * d ;



 if ( ! ( KrbException_class = PyErr_NewException ( "kerberos.KrbError" , NULL , NULL ) ) ) goto error ;
 PyDict_SetItemString ( d , "KrbError" , KrbException_class ) ;
 Py_INCREF ( KrbException_class ) ;
 if ( ! ( BasicAuthException_class = PyErr_NewException ( "kerberos.BasicAuthError" , KrbException_class , NULL ) ) ) goto error ;
 Py_INCREF ( BasicAuthException_class ) ;
 PyDict_SetItemString ( d , "BasicAuthError" , BasicAuthException_class ) ;
 if ( ! ( PwdChangeException_class = PyErr_NewException ( "kerberos.PwdChangeError" , KrbException_class , NULL ) ) ) goto error ;
 Py_INCREF ( PwdChangeException_class ) ;
 PyDict_SetItemString ( d , "PwdChangeError" , PwdChangeException_class ) ;
 if ( ! ( GssException_class = PyErr_NewException ( "kerberos.GSSError" , KrbException_class , NULL ) ) ) goto error ;
 Py_INCREF ( GssException_class ) ;
 PyDict_SetItemString ( d , "GSSError" , GssException_class ) ;
 PyDict_SetItemString ( d , "AUTH_GSS_COMPLETE" , PyInt_FromLong ( AUTH_GSS_COMPLETE ) ) ;
 PyDict_SetItemString ( d , "AUTH_GSS_CONTINUE" , PyInt_FromLong ( AUTH_GSS_CONTINUE ) ) ;
 PyDict_SetItemString ( d , "GSS_C_DELEG_FLAG" , PyInt_FromLong ( GSS_C_DELEG_FLAG ) ) ;
 PyDict_SetItemString ( d , "GSS_C_MUTUAL_FLAG" , PyInt_FromLong ( GSS_C_MUTUAL_FLAG ) ) ;
 PyDict_SetItemString ( d , "GSS_C_REPLAY_FLAG" , PyInt_FromLong ( GSS_C_REPLAY_FLAG ) ) ;
 PyDict_SetItemString ( d , "GSS_C_SEQUENCE_FLAG" , PyInt_FromLong ( GSS_C_SEQUENCE_FLAG ) ) ;
 PyDict_SetItemString ( d , "GSS_C_CONF_FLAG" , PyInt_FromLong ( GSS_C_CONF_FLAG ) ) ;
 PyDict_SetItemString ( d , "GSS_C_INTEG_FLAG" , PyInt_FromLong ( GSS_C_INTEG_FLAG ) ) ;
 PyDict_SetItemString ( d , "GSS_C_ANON_FLAG" , PyInt_FromLong ( GSS_C_ANON_FLAG ) ) ;
 PyDict_SetItemString ( d , "GSS_C_PROT_READY_FLAG" , PyInt_FromLong ( GSS_C_PROT_READY_FLAG ) ) ;
 PyDict_SetItemString ( d , "GSS_C_TRANS_FLAG" , PyInt_FromLong ( GSS_C_TRANS_FLAG ) ) ;
 error : if ( PyErr_Occurred ( ) ) PyErr_SetString ( PyExc_ImportError , "kerberos: init failed" ) ;

