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
public class RunningList extends linkedList{
    
    private Processes first;
    
    
    public RunningList(){
        first = null;
        
    }
    public boolean IsEmpty(){
        
        return (first == null);
    }
    public void InsertFirst(Processes process){
        
        process.next = first;
        first = process;
       
    }
  
    public void delete (Processes process){
        Processes previous , Current;
        Current = first;
        if(process == first){
            first = first.next;
            return;
        }
        previous = Current;
        Current = Current.next;
        while(Current != null){
            if(Current == process){
                previous.next = Current.next;
                return;
            }
        previous = Current;
        Current = Current.next;
        }
    }
    public void display(){
      Processes Current = first;
        while(Current != null){
           Current.ToString();
            Current=Current.next;
        }  
    }
    
    public Processes Peek (){
        return first;
    }
    
}
