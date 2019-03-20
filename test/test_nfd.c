#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "nfd.h"

int cmd_open_dialog(void)
{
    nfdchar_t *outPath = NULL;
    nfdresult_t result = NFD_OpenDialog(NULL, NULL, &outPath );
    if ( result == NFD_OKAY )
    {
        //puts("Success!");
        printf("%s", outPath);
        free(outPath);
        return 0;
    }
    else if ( result == NFD_CANCEL )
    {
        //puts("User pressed cancel.");
        return -1;
    }
    else 
    {
        printf("Error: %s\n", NFD_GetError() );
        return -1;
    }

}

int cmd_open_dialog_multiple(void)
{
    nfdpathset_t pathSet;
    nfdresult_t result = NFD_OpenDialogMultiple( NULL, NULL, &pathSet );
    if ( result == NFD_OKAY )
    {
        size_t i;
        for ( i = 0; i < NFD_PathSet_GetCount(&pathSet); ++i )
        {
            nfdchar_t *path = NFD_PathSet_GetPath(&pathSet, i);
            printf("%s\n", path);
        }
        NFD_PathSet_Free(&pathSet);
        return 0;
    }
    else if ( result == NFD_CANCEL )
    {
        //puts("User pressed cancel.");
        return -1;
    }
    else
    {
        printf("Error: %s\n", NFD_GetError() );
        return -1;
    }
}

int cmd_pick_folder(void)
{
    nfdchar_t *outPath = NULL;
    nfdresult_t result = NFD_PickFolder( NULL, &outPath );
    if ( result == NFD_OKAY )
    {
        //puts("Success!");
        printf("%s", outPath);
        free(outPath);
        return 0;
    }
    else if ( result == NFD_CANCEL )
    {
        //puts("User pressed cancel.");
        return -1;
    }
    else
    {
        printf("Error: %s\n", NFD_GetError() );
        return -1;
    }

}

int cmd_save_dialog(void)
{
    nfdchar_t *savePath = NULL;
    nfdresult_t result = NFD_SaveDialog( NULL, NULL, &savePath );
    if ( result == NFD_OKAY )
    {
        //puts("Success!");
        printf("%s", savePath);
        free(savePath);
        return 0;
    }
    else if ( result == NFD_CANCEL )
    {
        //puts("User pressed cancel.");
        return -1;
    }
    else
    {
        printf("Error: %s\n", NFD_GetError() );
        return -1;
    }
}

int cmd_help(void)
{
   printf("dialog   : open dialog\n");
   printf("multiple : open dialog multiple\n");
   printf("folder   : pick folder\n");
   printf("save     : save dialog\n");

   return 0;
}

struct command
{
  char *name;
  int (*run)(void);
};

static struct command cmds[] = {
  {"dialog", cmd_open_dialog},
  {"multiple", cmd_open_dialog_multiple},
  {"folder", cmd_pick_folder},
  {"save", cmd_save_dialog},

  {"help", cmd_help},
  {"-h", cmd_help},
};

#define ARRAY_SIZE(_a) (sizeof(_a) / sizeof(_a[0]))

int main(int argc, char **argv)
{
  int i, ret = 0;
  errno = 0;

  if(argc < 2) {
    cmd_help();
    goto out;
  }

  for(i = 0; i<ARRAY_SIZE(cmds); i++) {
    if(strcmp(argv[1], cmds[i].name) == 0) {
      ret = cmds[i].run();
      goto out;
    }
  }
  
  cmd_help();
out:
  return ret;
}
