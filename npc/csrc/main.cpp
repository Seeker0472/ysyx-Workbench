

void init_monitor(int argc, char *argv[]);

int main(int argc, char **argv)
{
  init_monitor(argc, argv);
  sdb_mainloop();
  return 0;
}
