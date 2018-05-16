#include <stdio.h>
#include <unistd.h>

void child_A_proc()
{
  while (1) {
    fprintf(stdout, "%s", "A");
    fflush(stdout);
  }
}

void child_B_proc()
{
  while (1) {
    fprintf(stdout, "%s", "C");
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
  int child_B;

  child_A = fork();  
  child_B = fork();               /* neuen Prozess starten                          */
  if (child_A == 0){
    child_A_proc();
  }                 /* Bin ich der Sohnprozess?                       */
    
  if(child_B == 0){
    child_B_proc();
  }                 /* ... dann child-Funktion ausfuehren             */
  else{
    parent_proc();                  /* ... sonst parent-Funktion ausfuehren           */
  }
  return 0;
}
