static UBool sameScript ( UScriptCode scriptOne , UScriptCode scriptTwo ) {
 return scriptOne <= USCRIPT_INHERITED || scriptTwo <= USCRIPT_INHERITED || scriptOne == scriptTwo ;
 }