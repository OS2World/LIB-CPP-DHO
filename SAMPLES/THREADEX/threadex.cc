#define INCL_DOSDATETIME
#define INCL_DOSPROCESS
#include<os2.h>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

#include<thread.h>

#define NUM_THREADS 5

void thread_func(ULONG Parm);



void main(void)
{

   TThread *proc[4];
   APIRET rc;
   DATETIME DateTime;
   ULONG seed;
   int i, rnum;

   rc = DosGetDateTime(&DateTime);
   seed =DateTime.hundredths;
   srand(seed);

   for (i=0; i<4; i++)
   {
      proc[i] = new TThread((PFNTHREAD)thread_func, (ULONG)0L, (ULONG)4096);
      if (!proc[i]->init(FALSE))
      {
        printf("Error creating thread");
        return;
      }   
      do {
        rnum=rand()-31; } while ((rnum>31) || (rnum<-31));
      if (proc[i]->setPriority(rnum))
      {
         printf("Error setting thread priority");
         return;
      }
   }
   
   for (i=0; i<NUM_THREADS; i++)
      proc[i]->resume();

   for (i=0; i<NUM_THREADS; i++)
   {
     printf("\nWaiting for thread %d.", proc[i]->inqThreadId());
     proc[i]->waitThread();
   }
}


void thread_func(ULONG Parm)
{
   int i,j;
   TID tid;
   APIRET rc;
   PTIB pptib;
   PPIB pppib;
   UCHAR ch;

   rc = DosGetInfoBlocks(&pptib, &pppib);
   tid = pptib->tib_ptib2->tib2_ultid;
   ch = toascii(32+tid);
   printf("\nStarting TID %d with character %c.\n", tid, ch);

for (i=1; i<100; i++)
   {

      printf("%c", ch);
   }

   printf("\nTID #%d Complete\n", tid);
   DosExit(EXIT_THREAD, 0);

}




