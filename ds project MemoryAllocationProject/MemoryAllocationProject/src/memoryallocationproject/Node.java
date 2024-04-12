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
public class Node {
    
    int size;
    int start_address;
    int end_address;
    Node next;
    
    public Node(int size,int start , int end){
        this.size = size;
        this.end_address = end;
        this.start_address = start;
    }
    
}
