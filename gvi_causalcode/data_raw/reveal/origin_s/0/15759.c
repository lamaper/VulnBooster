static bool left_is_superset ( DTCollation * left , DTCollation * right ) {
 if ( left -> collation -> state & MY_CS_UNICODE && ( left -> derivation < right -> derivation || ( left -> derivation == right -> derivation && ( ! ( right -> collation -> state & MY_CS_UNICODE ) || ( left -> collation -> state & MY_CS_UNICODE_SUPPLEMENT && ! ( right -> collation -> state & MY_CS_UNICODE_SUPPLEMENT ) && left -> collation -> mbmaxlen > right -> collation -> mbmaxlen && left -> collation -> mbminlen == right -> collation -> mbminlen ) ) ) ) ) return TRUE ;
 if ( right -> repertoire == MY_REPERTOIRE_ASCII && ( left -> derivation < right -> derivation || ( left -> derivation == right -> derivation && ! ( left -> repertoire == MY_REPERTOIRE_ASCII ) ) ) ) return TRUE ;
 return FALSE ;
 }