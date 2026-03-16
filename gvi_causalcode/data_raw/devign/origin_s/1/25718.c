static int decode_i_picture_secondary_header(VC9Context *v)

{

    int status;


    if (v->profile > PROFILE_MAIN)

    {

        v->s.ac_pred = get_bits(&v->s.gb, 1);

        if (v->postprocflag) v->postproc = get_bits(&v->s.gb, 1);

         

        if (v->overlap && v->pq<9)

        {

            v->condover = get_bits(&v->s.gb, 1);

            if (v->condover)

            {

                v->condover = 2+get_bits(&v->s.gb, 1);

                if (v->condover == 3)

                {

                    status = bitplane_decoding(&v->over_flags_plane, v);

                    if (status < 0) return -1;


                    av_log(v->s.avctx, AV_LOG_DEBUG, "Overflags plane encoding: "

                           "Imode: %i, Invert: %i\n", status>>1, status&1);


                }

            }

        }

    }




     

    return 0;

}
