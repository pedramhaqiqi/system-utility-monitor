#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdio.h>
#include <sys/sysinfo.h>

/* Array of long options that getopt_long() uses for command line parcing*/
static struct option long_options[] =
          {
            /* These are the input options from user. */
            {"system", no_argument, 0, 1},
            {"user", no_argument, 0, 2},
            {"graphics", no_argument, 0, 3},
            {"samples", required_argument, 0, 4},
            {"tdelay", required_argument, 0, 5},
            {0, 0, 0, 0} //the struct option requires a the last array to be zeros
          };

struct sysinfo systeminfo;

void memory_usage(){
  sysinfo(&systeminfo);
  double free_ram = (double)(systeminfo.freeram * systeminfo.mem_unit)/((double) (1<<30));
  double total_ram = (double)(systeminfo.totalram * systeminfo.mem_unit)/((double) (1<<30));
  double free_swap = (double)(systeminfo.freeswap * systeminfo.mem_unit)/((double) (1<<30));
  double total_swap =(double)(systeminfo.totalswap * systeminfo.mem_unit)/((double) (1<<30));

  printf("### Memory ### (Phys.Used/Tot -- Virtual Used/Tot\n");
  printf("%0.2lf GB / %0.2lf GB  -- %0.2lf GB / %0.2lf GB\n", total_ram - free_ram, total_ram, total_ram + total_swap - free_swap - free_ram, total_ram+total_swap);
  
}

int* cmd_parsing_function(int argc, char *argv[]) {
  int opt;
  int option_index = 0;
  int *flag_arr;
  flag_arr = (int*) calloc(5, sizeof(int));
 

    while ((opt = getopt_long (argc, argv, "g",
                       long_options, &option_index) )!= -1)
      {
        /* Detect the end of the options. */
          switch (opt)
          {
          case 1:
            printf ("option %s\n", long_options[option_index].name);
            flag_arr[0] = 1;
            break;

          case 2:
            printf ("option %s\n", long_options[option_index].name);
            flag_arr[1] = 1;
            break;

          case 3:
            printf ("option %s\n", long_options[option_index].name);
            flag_arr[2] = 1;
            break;

          case 4:
            printf ("option %s\n", long_options[option_index].name);
            if ((strtol(optarg, NULL, 10) != 0)){
              flag_arr[3] = 1;
              printf(" with arg %s\n", optarg);
              break;} 
            else {
              printf(" --samples argument must be a positive integer %s\n", optarg);
              break;
            }
          case 5:
            printf ("option %s\n", long_options[option_index].name);
            if ((strtol(optarg, NULL, 10) != 0)){
              flag_arr[4] = 1;
              printf(" with arg %s\n", optarg);
              break;} 
              else 
              {
                printf(" --tdelay argument must be a positive integer %s\n", optarg); 
                break;
              }
          case '?':
            /* getopt_long prints and error message on its own. */
            printf("%s\n","Usage is [--system | --user ] *[--samples=] *[--tdelay=]"); //Usage comment to use
            exit(1);

          default:
            printf("%s","ERROR in identifiying command line command, pass read user manual");
            exit(1);
          }
       
    }
   return flag_arr;
}
int main(int argc, char **argv){
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
  int *cmd_flags;
  cmd_flags = cmd_parsing_function(argc, argv);
   for(int i=0; i<5; i++) {
     printf("%d ", cmd_flags[i]);
  }
  printf("\n");
  /* Accessing any remaining command line arguments */
  memory_usage();
  

  if (optind < argc)
    {
      printf("%s", "non-option ARGV-elements: ");
      printf("\n");
      while (optind < argc)
        printf ("%s\n ", argv[optind++]);
      
    }
  exit (0);
}
