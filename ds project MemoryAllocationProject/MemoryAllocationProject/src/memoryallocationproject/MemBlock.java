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
public class MemBlock {
    
   public int size;
   private linkedList heap = new linkedList();
    
    
    public MemBlock(int size){
     Node Block = new Node(size,0,(size-1));
     this.size = size;
     heap.InsertChunk(Block);
    }
     
    public Node allocate(int size){
        
        return  heap.UseChunk(size);
        
    }
    
    public void free (Node free){
        
        heap.InsertChunk(free);
    }
   
    
    
}
