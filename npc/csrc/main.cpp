
void sdb_mainloop();

void init_monitor(int argc, char *argv[]);

int is_exit_status_bad();

int main(int argc, char **argv)
{
  init_monitor(argc, argv);
  sdb_mainloop();
  return is_exit_status_bad();
}
