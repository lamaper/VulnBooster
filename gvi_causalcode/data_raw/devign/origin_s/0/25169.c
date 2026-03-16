static void slirp_receive(void *opaque, const uint8_t *buf, size_t size)

{


    printf("slirp input:\n");

    hex_dump(stdout, buf, size);


    slirp_input(buf, size);

}
