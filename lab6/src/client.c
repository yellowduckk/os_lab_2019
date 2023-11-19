#include <.h>

int result = 1;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char **argv) {
  uint64_t k = -1;
  uint64_t mod = -1;
  char servers[255] = {'\0'}; // ip=2^8-1 в локальной сети
  while (true) {
    int current_optind = optind ? optind : 1;
    static struct option options[] = {{"k", required_argument, 0, 0},
                                      {"mod", required_argument, 0, 0},
                                      {"servers", required_argument, 0, 0},
                                      {0, 0, 0, 0}};
    int option_index = 0;
    int c = getopt_long(argc, argv, "", options, &option_index);
    bool f;
    if (c == -1)
    {
      break;
    }

    switch (c) {
    case 0: {
      switch (option_index) {
      case 0:
        f = ConvertStringToUI64(optarg, &k);
        // TODO: your code here
        if (!f) {
            printf("invalid value k\n");
            return -1;
        }
        break;
      case 1:
        f = ConvertStringToUI64(optarg, &mod);
        // TODO: your code here
        if (!f) {
            printf("invalid value mod\n");
            return -1;
        }
        break;
      case 2:
        memcpy(servers, optarg, strlen(optarg));
        break;
      default:
        printf("Index %d is out of options\n", option_index);
      }
    } break;
    case '?':
      printf("Arguments error\n");
      break;
    default:
      fprintf(stderr, "getopt returned character code 0%o?\n", c);
    }
  }

  if (k == -1 || mod == -1 || !strlen(servers)) {
    fprintf(stderr, "Using: %s --k 1000 --mod 5 --servers /path/to/file\n", argv[0]);
    return 1;
  }

  //Считываем адреса и разбиваем
  FILE* addresses = fopen("servers.txt", "r");
  if (addresses == NULL) {
    printf("cannot read addresses");
    return -1;
  }

  //Подсчитываем кол-во адресов
  char buf[256];
  unsigned int servers_num = 0;
  while(fgets(buf,256,addresses) != NULL)
    servers_num++;
  
  struct Server *to = malloc(sizeof(struct Server) * servers_num);
  fclose(addresses);

  FILE* addresses2 = fopen("servers.txt", "r");
  int i = 0;
  while ((!feof(addresses2))&&i!=2) {
    //printf("breakpoint\n");
    char* r = fgets(buf, sizeof(buf), addresses2);
    strcpy((*(to+i)).ip, strtok(buf,":"));
    (*(to+i)).port = atoi(strtok(NULL, ":"));
    i++;
  }
  fclose(addresses2);
  for (i = 0; i < servers_num; i++) {
    printf("server: %s:%d\n", (*(to+i)).ip, (*(to+i)).port);
  }
  sleep(1);

  pthread_t threads[servers_num];
  
  // Разделяем данные между потоками
  //printf("breakpoint\n");
  struct ThreadServerArgs args[servers_num];
  uint64_t begin = 1, end = k;
  for(int i = 0; i < servers_num; i++) {
   args[i].to_server = *(to+i);
   args[i].mod = mod;
  }
  if(servers_num == 1)
 {
     args[0].begin = begin;  
    args[0].end = end;  
  }
  else
  {
   uint64_t length = end - begin + 1;
   uint64_t step = length/servers_num;

   args[0].begin = begin;  
   args[0].end = begin + step; 
        
   for(int i = 1; i < servers_num - 1; i++) {
     args[i].begin = args[i - 1].end + 1;
     args[i].end = args[i].begin + step;
   }
    
    args[servers_num - 1].begin = args[servers_num - 2].end + 1;
		args[servers_num - 1].end = end;
   }
  
  for (i = 0; i < servers_num; i++) {
    if (pthread_create(&threads[i], NULL, (void *)ThreadServer, (void *)(args+i))) {
        printf("Error: pthread_create failed!\n");
        return 1;
    }
  }
  //Завершаем потоки
  for (i = 0; i < servers_num; i++) 
    pthread_join(threads[i], NULL);

  printf("---------------------------\nResult: %d\n", result);
  free(to);
  return 0;
}