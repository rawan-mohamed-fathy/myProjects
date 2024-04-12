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
public class linkedList {
     
    Node head;
    
    public linkedList(){
        this.head = null;

    }
    /* function used when free memory , try to merge free spaces if it helps */
    public void InsertChunk(Node freed_Chunk){
        
        Node Current;
        freed_Chunk.next = head;
         head = freed_Chunk;
          
        if(IsEmpty()){
            head =  freed_Chunk;
        } else {
            Current = head.next;
            while(Current != null ){
                if(Current.start_address == (freed_Chunk.end_address+1)){
                    Current.start_address = freed_Chunk.start_address;
                    Current.size+=freed_Chunk.size;
                    delete(freed_Chunk);
                    freed_Chunk = freed_Chunk.next;
                    Current= freed_Chunk.next;
                }else if(freed_Chunk.start_address ==(Current.end_address+1)){
                    Current.size+=freed_Chunk.size;
                    Current.end_address=freed_Chunk.end_address;
                     delete(freed_Chunk);
                    freed_Chunk = freed_Chunk.next;
                    Current= freed_Chunk.next;
                } else {
                Current = Current.next;
                }
            }
    }
 }
    
    private boolean IsEmpty (){
        return (head == null);
    }
    /* function used when allocate memory */
    public Node UseChunk (int size){
        
         Node Current = head;
         Node Previous = head;
         Node required = new Node(0,0,0);
         if(IsEmpty())
             return null;
        if(head.size == size){
            head = head.next;
            required = Current;
            return required;
        } else {
        while(Current != null){
            if(size < Current.size){
                required.size = size;
                required.start_address = Current.start_address;
                Current.size-=size;
                Current.start_address +=size;
                 required.end_address = (Current.start_address-1);
                return required;
            } else if(size == Current.size){
                Previous.next = Current.next;
                required = Current;
                return required;
            }
            Previous = Current;
            Current = Current.next;
        }  
    }
        return null;
  }
    
   private void delete (Node free){
       Node Previous,Current;
       if(free == head){
           head=head.next;
       } else {
           Previous = head;
           Current =  head.next;
           while(Current != null){
               if(free == Current){
                   Previous.next = Current.next;
                   return;
               }
               Current = Current.next;
           }
       }
   }
}
