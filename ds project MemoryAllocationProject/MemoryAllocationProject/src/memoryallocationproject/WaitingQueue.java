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
public class WaitingQueue {
    private int MaxSize;
    private Processes[]Queue;
    private int nItems;
    
    public WaitingQueue(int MaxSize){
        this.MaxSize = MaxSize;
        this.Queue = new Processes[MaxSize];
        this.nItems =0;
    }
    public boolean IsFull(){
        return (nItems == MaxSize);
    }
    public boolean IsEmpty(){
        return (nItems == 0);
    }
    
    public void Enqueue (Processes item){
        int i = nItems;
        if(nItems == 0){
            Queue[i++]=item;
        } else {
            for(i=nItems-1;i>=0;i--){
             if(item.size> Queue[i].size){
                Queue[i+1]=Queue[i];
               
            } else {
                break;
           }
        }
      }
        Queue[i+1] = item;   
        nItems++;
    }
    public Processes Dequeue (){
        Processes deletedItem = Queue[--nItems];
        return deletedItem;
    }
    public void display(){
        int i;
        for(i=0;i<nItems;i++){
            Queue[i].ToString();
        }
    }
}
