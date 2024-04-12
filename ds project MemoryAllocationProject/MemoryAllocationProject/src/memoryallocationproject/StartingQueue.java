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
public class StartingQueue {
     
    private Processes Front;
    private  Processes Rear;
    
    public StartingQueue(){
        this.Front = null;
        this.Rear = null;
    }
    
    public boolean IsEmpty (){
        return (Front == null);
    }
    
    public void Enqueue(Processes process){
         process.next = null;
        if(Front == null){
            Front = process;
        } else {
            Rear.next = process;
        }
         Rear = process;
        
    } 
    public  Processes Dequeue(){
        Processes deletedNode = Front;
        if(Front.next == null)
            Rear = null;
        Front = Front.next;
        return deletedNode;
    }
}
