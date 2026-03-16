static void utf8_string(void)

{

     

    static const struct {

        const char *json_in;

        const char *utf8_out;

        const char *json_out;    

        const char *utf8_in;     

    } test_cases[] = {

         



         

        {

             

            "\"Falsches \xC3\x9C" "ben von Xylophonmusik qu\xC3\xA4lt"

            " jeden gr\xC3\xB6\xC3\x9F" "eren Zwerg.\"",

            "Falsches \xC3\x9C" "ben von Xylophonmusik qu\xC3\xA4lt"

            " jeden gr\xC3\xB6\xC3\x9F" "eren Zwerg.",

            "\"Falsches \\u00DCben von Xylophonmusik qu\\u00E4lt"

            " jeden gr\\u00F6\\u00DFeren Zwerg.\"",

        },

        {

             

            "\"\xCE\xBA\xE1\xBD\xB9\xCF\x83\xCE\xBC\xCE\xB5\"",

            "\xCE\xBA\xE1\xBD\xB9\xCF\x83\xCE\xBC\xCE\xB5",

            "\"\\u03BA\\u1F79\\u03C3\\u03BC\\u03B5\"",

        },

         

         

         

        {

            "\"\\u0000\"",

            "",                  

            "\"\"",              

        },

         

        {

            "\"\xC2\x80\"",

            "\xC2\x80",

            "\"\\u0080\"",

        },

         

        {

            "\"\xE0\xA0\x80\"",

            "\xE0\xA0\x80",

            "\"\\u0800\"",

        },

         

        {

            "\"\xF0\x90\x80\x80\"",

            "\xF0\x90\x80\x80",

            "\"\\u0400\\uFFFF\"",  

        },

         

        {

            "\"\xF8\x88\x80\x80\x80\"",

            NULL,                         

            "\"\\u8200\\uFFFF\\uFFFF\"",  

            "\xF8\x88\x80\x80\x80",

        },

         

        {

            "\"\xFC\x84\x80\x80\x80\x80\"",

            NULL,                                

            "\"\\uC100\\uFFFF\\uFFFF\\uFFFF\"",  

            "\xFC\x84\x80\x80\x80\x80",

        },

         

         

        {

            "\"\x7F\"",

            "\x7F",

            "\"\177\"",

        },

         

        {

            "\"\xDF\xBF\"",

            "\xDF\xBF",

            "\"\\u07FF\"",

        },

         

        {

            "\"\xEF\xBF\xBF\"",

            "\xEF\xBF\xBF",

            "\"\\uFFFF\"",

        },

         

        {

            "\"\xF7\xBF\xBF\xBF\"",

            NULL,                  

            "\"\\u7FFF\\uFFFF\"",  

            "\xF7\xBF\xBF\xBF",

        },

         

        {

            "\"\xFB\xBF\xBF\xBF\xBF\"",

            NULL,                         

            "\"\\uBFFF\\uFFFF\\uFFFF\"",  

            "\xFB\xBF\xBF\xBF\xBF",

        },

         

        {

            "\"\xFD\xBF\xBF\xBF\xBF\xBF\"",

            NULL,                                

            "\"\\uDFFF\\uFFFF\\uFFFF\\uFFFF\"",  

            "\xFD\xBF\xBF\xBF\xBF\xBF",

        },

         

        {

             

            "\"\xED\x9F\xBF\"",

            "\xED\x9F\xBF",

            "\"\\uD7FF\"",

        },

        {

             

            "\"\xEE\x80\x80\"",

            "\xEE\x80\x80",

            "\"\\uE000\"",

        },

        {

             

            "\"\xEF\xBF\xBD\"",

            "\xEF\xBF\xBD",

            "\"\\uFFFD\"",

        },

        {

             

            "\"\xF4\x8F\xBF\xBF\"",

            "\xF4\x8F\xBF\xBF",

            "\"\\u43FF\\uFFFF\"",  

        },

        {

             

            "\"\xF4\x90\x80\x80\"",

            "\xF4\x90\x80\x80",

            "\"\\u4400\\uFFFF\"",  

        },

         

         

         

        {

            "\"\x80\"",

            "\x80",              

            "\"\\uFFFF\"",

        },

         

        {

            "\"\xBF\"",

            "\xBF",              

            "\"\\uFFFF\"",

        },

         

        {

            "\"\x80\xBF\"",

            "\x80\xBF",          

            "\"\\uFFFF\\uFFFF\"",

        },

         

        {

            "\"\x80\xBF\x80\"",

            "\x80\xBF\x80",      

            "\"\\uFFFF\\uFFFF\\uFFFF\"",

        },

         

        {

            "\"\x80\xBF\x80\xBF\"",

            "\x80\xBF\x80\xBF",  

            "\"\\uFFFF\\uFFFF\\uFFFF\\uFFFF\"",

        },

         

        {

            "\"\x80\xBF\x80\xBF\x80\"",

            "\x80\xBF\x80\xBF\x80",  

            "\"\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\"",

        },

         

        {

            "\"\x80\xBF\x80\xBF\x80\xBF\"",

            "\x80\xBF\x80\xBF\x80\xBF",  

            "\"\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\"",

        },

         

        {

            "\"\x80\xBF\x80\xBF\x80\xBF\x80\"",

            "\x80\xBF\x80\xBF\x80\xBF\x80",  

            "\"\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\"",

        },

         

        {

            "\"\x80\x81\x82\x83\x84\x85\x86\x87"

            "\x88\x89\x8A\x8B\x8C\x8D\x8E\x8F"

            "\x90\x91\x92\x93\x94\x95\x96\x97"

            "\x98\x99\x9A\x9B\x9C\x9D\x9E\x9F"

            "\xA0\xA1\xA2\xA3\xA4\xA5\xA6\xA7"

            "\xA8\xA9\xAA\xAB\xAC\xAD\xAE\xAF"

            "\xB0\xB1\xB2\xB3\xB4\xB5\xB6\xB7"

            "\xB8\xB9\xBA\xBB\xBC\xBD\xBE\xBF\"",

              

            "\x80\x81\x82\x83\x84\x85\x86\x87"

            "\x88\x89\x8A\x8B\x8C\x8D\x8E\x8F"

            "\x90\x91\x92\x93\x94\x95\x96\x97"

            "\x98\x99\x9A\x9B\x9C\x9D\x9E\x9F"

            "\xA0\xA1\xA2\xA3\xA4\xA5\xA6\xA7"

            "\xA8\xA9\xAA\xAB\xAC\xAD\xAE\xAF"

            "\xB0\xB1\xB2\xB3\xB4\xB5\xB6\xB7"

            "\xB8\xB9\xBA\xBB\xBC\xBD\xBE\xBF",

            "\"\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF"

            "\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF"

            "\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF"

            "\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF"

            "\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF"

            "\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF"

            "\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF"

            "\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\\uFFFF\""

        },

         

         

        {

            "\"\xC0 \xC1 \xC2 \xC3 \xC4 \xC5 \xC6 \xC7 "

            "\xC8 \xC9 \xCA \xCB \xCC \xCD \xCE \xCF "

            "\xD0 \xD1 \xD2 \xD3 \xD4 \xD5 \xD6 \xD7 "

            "\xD8 \xD9 \xDA \xDB \xDC \xDD \xDE \xDF \"",

            NULL,                

            "\"\\uFFFF \\uFFFF \\uFFFF \\uFFFF \\uFFFF \\uFFFF \\uFFFF \\uFFFF "

            "\\uFFFF \\uFFFF \\uFFFF \\uFFFF \\uFFFF \\uFFFF \\uFFFF \\uFFFF "

            "\\uFFFF \\uFFFF \\uFFFF \\uFFFF \\uFFFF \\uFFFF \\uFFFF \\uFFFF "

            "\\uFFFF \\uFFFF \\uFFFF \\uFFFF \\uFFFF \\uFFFF \\uFFFF \\uFFFF \"",

            "\xC0 \xC1 \xC2 \xC3 \xC4 \xC5 \xC6 \xC7 "

            "\xC8 \xC9 \xCA \xCB \xCC \xCD \xCE \xCF "

            "\xD0 \xD1 \xD2 \xD3 \xD4 \xD5 \xD6 \xD7 "

            "\xD8 \xD9 \xDA \xDB \xDC \xDD \xDE \xDF ",

        },

         

        {

            "\"\xE0 \xE1 \xE2 \xE3 \xE4 \xE5 \xE6 \xE7 "

            "\xE8 \xE9 \xEA \xEB \xEC \xED \xEE \xEF \"",

             

            "\xE0 \xE1 \xE2 \xE3 \xE4 \xE5 \xE6 \xE7 "

            "\xE8 \xE9 \xEA \xEB \xEC \xED \xEE \xEF ",

            "\"\\uFFFF \\uFFFF \\uFFFF \\uFFFF \\uFFFF \\uFFFF \\uFFFF \\uFFFF "

            "\\uFFFF \\uFFFF \\uFFFF \\uFFFF \\uFFFF \\uFFFF \\uFFFF \\uFFFF \"",

        },

         

        {

            "\"\xF0 \xF1 \xF2 \xF3 \xF4 \xF5 \xF6 \xF7 \"",

            NULL,                

            "\"\\uFFFF \\uFFFF \\uFFFF \\uFFFF \\uFFFF \\uFFFF \\uFFFF \\uFFFF \"",

            "\xF0 \xF1 \xF2 \xF3 \xF4 \xF5 \xF6 \xF7 ",

        },

         

        {

            "\"\xF8 \xF9 \xFA \xFB \"",

            NULL,                

            "\"\\uFFFF \\uFFFF \\uFFFF \\uFFFF \"",

            "\xF8 \xF9 \xFA \xFB ",

        },

         

        {

            "\"\xFC \xFD \"",

            NULL,                

            "\"\\uFFFF \\uFFFF \"",

            "\xFC \xFD ",

        },

         

         

        {

            "\"\xC0\"",

            NULL,                

            "\"\\uFFFF\"",

            "\xC0",

        },

         

        {

            "\"\xE0\x80\"",

            "\xE0\x80",            

            "\"\\uFFFF\\uFFFF\"",  

        },

         

        {

            "\"\xF0\x80\x80\"",

            "\xF0\x80\x80",      

            "\"\\u0000\"",       

        },

         

        {

             

            "\"\xF8\x80\x80\x80\"",  

            NULL,                    

            "\"\\u8000\\uFFFF\"",    

            "\xF8\x80\x80\x80",

        },

         

        {

            "\"\xFC\x80\x80\x80\x80\"",

            NULL,                         

            "\"\\uC000\\uFFFF\\uFFFF\"",  

            "\xFC\x80\x80\x80\x80",

        },

         

        {

            "\"\xDF\"",

            "\xDF",              

            "\"\\uFFFF\"",

        },

         

        {

            "\"\xEF\xBF\"",

            "\xEF\xBF",            

            "\"\\uFFFF\\uFFFF\"",  

        },

         

        {

            "\"\xF7\xBF\xBF\"",

            NULL,                

            "\"\\u7FFF\"",       

            "\xF7\xBF\xBF",

        },

         

        {

            "\"\xFB\xBF\xBF\xBF\"",

            NULL,                  

            "\"\\uBFFF\\uFFFF\"",  

            "\xFB\xBF\xBF\xBF",

        },

         

        {

            "\"\xFD\xBF\xBF\xBF\xBF\"",

            NULL,                         

            "\"\\uDFFF\\uFFFF\\uFFFF\"",  

            "\xFD\xBF\xBF\xBF\xBF",

        },

         

        {

            "\"\xC0\xE0\x80\xF0\x80\x80\xF8\x80\x80\x80\xFC\x80\x80\x80\x80"

            "\xDF\xEF\xBF\xF7\xBF\xBF\xFB\xBF\xBF\xBF\xFD\xBF\xBF\xBF\xBF\"",

            NULL,                

             

            "\"\\u0020\\uFFFF\\u0000\\u8000\\uFFFF\\uC000\\uFFFF\\uFFFF"

            "\\u07EF\\uFFFF\\u7FFF\\uBFFF\\uFFFF\\uDFFF\\uFFFF\\uFFFF\"",

            "\xC0\xE0\x80\xF0\x80\x80\xF8\x80\x80\x80\xFC\x80\x80\x80\x80"

            "\xDF\xEF\xBF\xF7\xBF\xBF\xFB\xBF\xBF\xBF\xFD\xBF\xBF\xBF\xBF",

        },

         

        {

            "\"\xFE\"",

            NULL,                

            "\"\\uFFFF\"",

            "\xFE",

        },

        {

            "\"\xFF\"",

            NULL,                

            "\"\\uFFFF\"",

            "\xFF",

        },

        {

            "\"\xFE\xFE\xFF\xFF\"",

            NULL,                  

             

            "\"\\uEFBF\\uFFFF\"",

            "\xFE\xFE\xFF\xFF",

        },

         

         

        {

            "\"\xC0\xAF\"",

            NULL,                

            "\"\\u002F\"",       

            "\xC0\xAF",

        },

        {

            "\"\xE0\x80\xAF\"",

            "\xE0\x80\xAF",      

            "\"\\u002F\"",       

        },

        {

            "\"\xF0\x80\x80\xAF\"",

            "\xF0\x80\x80\xAF",   

            "\"\\u0000\\uFFFF\""  

        },

        {

            "\"\xF8\x80\x80\x80\xAF\"",

            NULL,                         

            "\"\\u8000\\uFFFF\\uFFFF\"",  

            "\xF8\x80\x80\x80\xAF",

        },

        {

            "\"\xFC\x80\x80\x80\x80\xAF\"",

            NULL,                                

            "\"\\uC000\\uFFFF\\uFFFF\\uFFFF\"",  

            "\xFC\x80\x80\x80\x80\xAF",

        },

         

        {

             

            "\"\xC1\xBF\"",

            NULL,                

            "\"\\u007F\"",       

            "\xC1\xBF",

        },

        {

             

            "\"\xE0\x9F\xBF\"",

            "\xE0\x9F\xBF",      

            "\"\\u07FF\"",

        },

        {

             

            "\"\xF0\x8F\xBF\xBF\"",

            "\xF0\x8F\xBF\xBF",    

            "\"\\u03FF\\uFFFF\"",  

        },

        {

             

            "\"\xF8\x87\xBF\xBF\xBF\"",

            NULL,                         

            "\"\\u81FF\\uFFFF\\uFFFF\"",  

            "\xF8\x87\xBF\xBF\xBF",

        },

        {

             

            "\"\xFC\x83\xBF\xBF\xBF\xBF\"",

            NULL,                                

            "\"\\uC0FF\\uFFFF\\uFFFF\\uFFFF\"",  

            "\xFC\x83\xBF\xBF\xBF\xBF",

        },

         

        {

             

            "\"\xC0\x80\"",

            NULL,                

            "\"\\u0000\"",

            "\xC0\x80",

        },

        {

             

            "\"\xE0\x80\x80\"",

            "\xE0\x80\x80",      

            "\"\\u0000\"",

        },

        {

             

            "\"\xF0\x80\x80\x80\"",

            "\xF0\x80\x80\x80",    

            "\"\\u0000\\uFFFF\"",  

        },

        {

             

            "\"\xF8\x80\x80\x80\x80\"",

            NULL,                         

            "\"\\u8000\\uFFFF\\uFFFF\"",  

            "\xF8\x80\x80\x80\x80",

        },

        {

             

            "\"\xFC\x80\x80\x80\x80\x80\"",

            NULL,                                

            "\"\\uC000\\uFFFF\\uFFFF\\uFFFF\"",  

            "\xFC\x80\x80\x80\x80\x80",

        },

         

         

        {

             

            "\"\xED\xA0\x80\"",

            "\xED\xA0\x80",      

            "\"\\uD800\"",       

        },

        {

             

            "\"\xED\xAD\xBF\"",

            "\xED\xAD\xBF",      

            "\"\\uDB7F\"",       

        },

        {

             

            "\"\xED\xAE\x80\"",

            "\xED\xAE\x80",      

            "\"\\uDB80\"",       

        },

        {

             

            "\"\xED\xAF\xBF\"",

            "\xED\xAF\xBF",      

            "\"\\uDBFF\"",       

        },

        {

             

            "\"\xED\xB0\x80\"",

            "\xED\xB0\x80",      

            "\"\\uDC00\"",       

        },

        {

             

            "\"\xED\xBE\x80\"",

            "\xED\xBE\x80",      

            "\"\\uDF80\"",       

        },

        {

             

            "\"\xED\xBF\xBF\"",

            "\xED\xBF\xBF",      

            "\"\\uDFFF\"",       

        },

         

        {

             

            "\"\xED\xA0\x80\xED\xB0\x80\"",

            "\xED\xA0\x80\xED\xB0\x80",  

            "\"\\uD800\\uDC00\"",  

        },

        {

             

            "\"\xED\xA0\x80\xED\xBF\xBF\"",

            "\xED\xA0\x80\xED\xBF\xBF",  

            "\"\\uD800\\uDFFF\"",  

        },

        {

             

            "\"\xED\xAD\xBF\xED\xB0\x80\"",

            "\xED\xAD\xBF\xED\xB0\x80",  

            "\"\\uDB7F\\uDC00\"",  

        },

        {

             

            "\"\xED\xAD\xBF\xED\xBF\xBF\"",

            "\xED\xAD\xBF\xED\xBF\xBF",  

            "\"\\uDB7F\\uDFFF\"",  

        },

        {

             

            "\"\xED\xAE\x80\xED\xB0\x80\"",

            "\xED\xAE\x80\xED\xB0\x80",  

            "\"\\uDB80\\uDC00\"",  

        },

        {

             

            "\"\xED\xAE\x80\xED\xBF\xBF\"",

            "\xED\xAE\x80\xED\xBF\xBF",  

            "\"\\uDB80\\uDFFF\"",  

        },

        {

             

            "\"\xED\xAF\xBF\xED\xB0\x80\"",

            "\xED\xAF\xBF\xED\xB0\x80",  

            "\"\\uDBFF\\uDC00\"",  

        },

        {

             

            "\"\xED\xAF\xBF\xED\xBF\xBF\"",

            "\xED\xAF\xBF\xED\xBF\xBF",  

            "\"\\uDBFF\\uDFFF\"",  

        },

         

        {

             

            "\"\xEF\xBF\xBE\"",

            "\xEF\xBF\xBE",      

            "\"\\uFFFE\"",       

        },

        {

             

            "\"\xEF\xBF\xBF\"",

            "\xEF\xBF\xBF",      

            "\"\\uFFFF\"",       

        },

        {}

    };

    int i;

    QObject *obj;

    QString *str;

    const char *json_in, *utf8_out, *utf8_in, *json_out;



    for (i = 0; test_cases[i].json_in; i++) {

        json_in = test_cases[i].json_in;

        utf8_out = test_cases[i].utf8_out;

        utf8_in = test_cases[i].utf8_in ?: test_cases[i].utf8_out;

        json_out = test_cases[i].json_out ?: test_cases[i].json_in;



        obj = qobject_from_json(json_in);

        if (utf8_out) {

            g_assert(obj);

            g_assert(qobject_type(obj) == QTYPE_QSTRING);

            str = qobject_to_qstring(obj);

            g_assert_cmpstr(qstring_get_str(str), ==, utf8_out);

        } else {

            g_assert(!obj);

        }

        qobject_decref(obj);



        obj = QOBJECT(qstring_from_str(utf8_in));

        str = qobject_to_json(obj);

        if (json_out) {

            g_assert(str);

            g_assert_cmpstr(qstring_get_str(str), ==, json_out);

        } else {

            g_assert(!str);

        }

        QDECREF(str);

        qobject_decref(obj);



         

        if (0 && json_out != json_in) {

            obj = qobject_from_json(json_out);

            g_assert(obj);

            g_assert(qobject_type(obj) == QTYPE_QSTRING);

            str = qobject_to_qstring(obj);

            g_assert_cmpstr(qstring_get_str(str), ==, utf8_out);

        }

    }

}
