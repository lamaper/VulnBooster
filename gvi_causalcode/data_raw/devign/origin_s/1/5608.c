void gdb_exit(CPUArchState *env, int code)

{

  GDBState *s;

  char buf[4];



  s = gdbserver_state;

  if (!s) {

      return;

  }


  if (gdbserver_fd < 0 || s->fd < 0) {

      return;

  }




  snprintf(buf, sizeof(buf), "W%02x", (uint8_t)code);

  put_packet(s, buf);


  if (s->chr) {

      qemu_chr_delete(s->chr);

  }


}
