static StkId adjust_varargs ( lua_State * L , Proto * p , int actual ) {
 int i ;
 int nfixargs = p -> numparams ;
 Table * htab = NULL ;
 StkId base , fixed ;
 for ( ;
 actual < nfixargs ;
 ++ actual ) setnilvalue ( L -> top ++ ) ;

 int nvar = actual - nfixargs ;
 lua_assert ( p -> is_vararg & VARARG_HASARG ) ;
 luaC_checkGC ( L ) ;
 luaD_checkstack ( L , p -> maxstacksize ) ;
 htab = luaH_new ( L , nvar , 1 ) ;
 for ( i = 0 ;
 i < nvar ;
 i ++ ) setobj2n ( L , luaH_setnum ( L , htab , i + 1 ) , L -> top - nvar + i ) ;
 setnvalue ( luaH_setstr ( L , htab , luaS_newliteral ( L , "n" ) ) , cast_num ( nvar ) ) ;
 }

 base = L -> top ;
 for ( i = 0 ;
 i < nfixargs ;
 i ++ ) {
 setobjs2s ( L , L -> top ++ , fixed + i ) ;
 setnilvalue ( fixed + i ) ;
 }
 if ( htab ) {
 sethvalue ( L , L -> top ++ , htab ) ;
 lua_assert ( iswhite ( obj2gco ( htab ) ) ) ;
 }
 return base ;
 }