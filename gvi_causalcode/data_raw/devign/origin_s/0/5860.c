real_parse_asm_rule(AVStream *st, const char *p, const char *end)

{

    do {


        if (sscanf(p, " %*1[Aa]verage%*1[Bb]andwidth=%d", &st->codec->bit_rate) == 1)


        if (sscanf(p, " %*1[Aa]verage%*1[Bb]andwidth=%"SCNd64, &st->codec->bit_rate) == 1)


            break;

        if (!(p = strchr(p, ',')) || p > end)

            p = end;

        p++;

    } while (p < end);

}
