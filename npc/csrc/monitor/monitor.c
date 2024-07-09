#include <getopt.h>
#include <stdio.h>

static char *img_file = NULL;
static char *elf_file = NULL;

void init_img(char *img_file);
int init_runtime();
int run();

static int parse_args(int argc, char *argv[])
{
  const struct option table[] = {
      // {"batch"    , no_argument      , NULL, 'b'},
      // {"log"      , required_argument, NULL, 'l'},
      // {"diff"     , required_argument, NULL, 'd'},
      // {"port"     , required_argument, NULL, 'p'},
      // {"help"     , no_argument      , NULL, 'h'},
      {"elf-file", required_argument, NULL, 'e'},
      {0, 0, 0, 0},
  };
  int o;
  while ((o = getopt_long(argc, argv, "-e:", table, NULL)) != -1)
  {
    switch (o)
    {
      // case 'b': sdb_set_batch_mode(); break;
      // case 'p': sscanf(optarg, "%d", &difftest_port); break;
      // case 'l': log_file = optarg; break;
      // case 'd': diff_so_file = optarg; break;

    case 'e':
      elf_file = optarg;
      break;
    case 1:
      img_file = optarg;
      printf("%s", img_file);
      return 0;
    default:
      printf("Usage: %s [OPTION...] IMAGE [args]\n\n", argv[0]);
      // printf("\t-b,--batch              run with batch mode\n");
      // printf("\t-l,--log=FILE           output log to FILE\n");
      // printf("\t-d,--diff=REF_SO        run DiffTest with reference REF_SO\n");
      // printf("\t-p,--port=PORT          run DiffTest with port PORT\n");
      // printf("\t-e,--elf-file=FILE      input Elf File\n");
      printf("\n");
      exit(0);
    }
  }
  return 0;
}
void welcome(){
    printf("Welcome To npc(New Processor Core!)");
}

void init_monitor(int argc, char *argv[]){
    parse_args(argc, argv);
    init_img(img_file);
    init_runtime();
    welcome();
    run();
}