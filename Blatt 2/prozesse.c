#include <stdio.h>
#include <unistd.h>

void child_A_proc()
{
  while (1) {
    fprintf(stdout, "%s", "A");
    fflush(stdout);
  }
}

void parent_proc()
{
  while (1) {
    write(1, "B", 1);
  }
}

int main(void)
{
  int child_A;

  child_A = fork();                 /* neuen Prozess starten                          */
  if (child_A == 0)                 /* Bin ich der Sohnprozess?                       */
    child_A_proc();                 /* ... dann child-Funktion ausfuehren             */
  else
    parent_proc();                  /* ... sonst parent-Funktion ausfuehren           */

  return 0;
}
