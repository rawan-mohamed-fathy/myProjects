/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package memoryallocationproject;

import java.util.Random;

/**
 *
 * @author hp
 */
public class Processes {
    
    int id;
    int size;
    int time;
    Node block;
    Processes next;
    
    public Processes(int id){
        Random r = new Random();
        this.id = id;
        this.size = r.nextInt(256);
        this.time = r.nextInt(20000);
    }
    
    
    public void ToString() {
        System.out.println("Process "+id+" with size "+size);
    }
    
}
