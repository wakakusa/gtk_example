#include "advisor-annotate.h" // Add to each module that contains Intel Advisor XE annotations
#define num_steps 1000000000
double step;

main ()
{
  int i; double x, pi, sum = 0.0;
  step = 1.0/(double) num_steps;

 ANNOTATE_SITE_BEGIN( MySite1 ); // Place before the loop control statement 
   for (i=1;i<= num_steps; i++)
  {
    ANNOTATE_ITERATION_TASK( MyTask1-1 ); // Place at the start of loop body. This iterative-task annotation identifies an entire body as a task. 
    x = (i-0.5)*step;
    sum = sum + 4.0/(1.0+x*x);
    ANNOTATE_TASK_END(MyTask1-1);
  }
  pi = step * sum;

   for (i=1;i<= num_steps; i++)
  {
    ANNOTATE_ITERATION_TASK( MyTask1-2 ); // Place at the start of loop body. This iterative-task annotation identifies an entire body as a task. 
    sum = sum + i;
    ANNOTATE_TASK_END(MyTask1-2);
  }
   ANNOTATE_SITE_END(MySite1); // End the parallel code region, after task execution completes


 ANNOTATE_SITE_BEGIN( MySite2 ); // Place before the loop control statement 
   for (i=1;i<= num_steps/100; i++)
  {
    ANNOTATE_ITERATION_TASK( MyTask2-1 ); // Place at the start of loop body. This iterative-task annotation identifies an entire body as a task. 
    x = (i-0.5)*step;
    sum = sum + 4.0/(1.0+x*x);
    ANNOTATE_TASK_END(MyTask2-1);
  }
  pi = step * sum;

   for (i=1;i<= num_steps/100; i++)
  {
    ANNOTATE_ITERATION_TASK( MyTask2-2 ); // Place at the start of loop body. This iterative-task annotation identifies an entire body as a task. 
    sum = sum + i;
    ANNOTATE_TASK_END(MyTask2-2);
  }
   ANNOTATE_SITE_END(MySite2); // End the parallel code region, after task execution completes
  
  
  
} 
