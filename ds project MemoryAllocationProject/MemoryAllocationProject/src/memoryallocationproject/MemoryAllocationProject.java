/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package memoryallocationproject;

/**
 *
 * @author hp
 */
import java.util.Random;

public class MemoryAllocationProject {

    /**
     * @param args the command line arguments
     */
    /* Global Variable */
    static StartingQueue starting = new StartingQueue();   /* Queue for strating Processes */
     static RunningList Running = new RunningList();       /* List Contaion Running Processe */    
     static WaitingQueue Waiting = new WaitingQueue(20);    /* Queue Contaiong waiting Processe which not found required request of memeory */
     static MemBlock memory = new MemBlock(1024);           /* Block Of memory */
     static int j =0;
     static int NumOfProceeses = 20;
    public static void main(String[] args) throws InterruptedException {
        // TODO code application logic here
        /*  Create Processes  */
        int i;
        for(i=1;i<=NumOfProceeses;i++){
            Processes process = new Processes(i);
            starting.Enqueue(process);
        } 
        /* Start Execution of Processes untill all processes ends */
       while(!starting.IsEmpty() || !Waiting.IsEmpty() || !Running.IsEmpty()){
           /* display all lists of processes  */
           display();
           /* Check if startinglist not empty take one process to start execution */
           if(!starting.IsEmpty()){
           Processes p = starting.Dequeue();
           if(p != null){
               /* try to allocate required memory for process */
            p.block = memory.allocate(p.size);
            /* there is no enough space for this request */
           if(p.block == null){
               /* put this process in waiting list untill find space for it's request*/
               Waiting.Enqueue(p);
           } else {
                /* there enough space for this request process start running */
               Running.InsertFirst(p);
           }
         }
        }
           /* this function update time for running processes and check if one process
             end , free it's space 
           */
           updateRunning();
           /* Check if waiting queue not empty take one process to start execution */
           if(!Waiting.IsEmpty()){
           Processes Wait = Waiting.Dequeue();
           /* try to allocate required memory for process */
           Wait.block = memory.allocate(Wait.size);
           if(Wait.block == null){
               /* there is no enough space for this request */
               /* return this process into waiting list untill find space for it's request*/
               Waiting.Enqueue(Wait);
           } else {
                /* there enough space for this request process start running */
               Running.InsertFirst(Wait);
           }
          }
           Thread.sleep(1000);
       }
       display();
    }
    public static void display(){
        System.out.println("Time: "+ ++j);
        System.out.println("Running: ");
        Running.display();
        System.out.println("_________");
        System.out.println("Waiting: ");
         Waiting.display();

         System.out.println("_________");
    }
    public static void updateRunning(){
        
        Processes Current = Running.Peek();
        while(Current != null){
            Current.time-=1000;
            if(Current.time <= 0){
                Running.delete(Current);
                memory.free(Current.block);
            }
            Current=Current.next;
        }
        
    }
    
    
}
