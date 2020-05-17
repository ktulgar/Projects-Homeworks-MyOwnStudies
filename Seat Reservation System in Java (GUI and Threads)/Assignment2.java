
import java.awt.Color;
import java.util.List;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.Collections;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.ReentrantLock;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JTextField;

public class Assignment2 extends JFrame implements ActionListener,Runnable {

    // Global Variables
    private JTextField field1,field2,field3 ;
    private JButton bttn1,bttn2 ;
    private JFrame f ;
    private int width,height,maxwaitingTime,numberofThread ;
    private ArrayList<JTextField> seats ;
    private ReentrantLock lock ;  
                  
    public Assignment2(){
    
       initData() ;
  
    }   
    
    public void initData(){
             
         lock = new ReentrantLock() ; // I use reentrantlock because i wanted one thread to book one seat
         seats = new ArrayList<>(); // It holds seats.
                 
        // Features of our frame
         width = 1000 ;
         height = 600 ;
         f = new JFrame("Booking");
         f.setLayout(null);
         f.setSize(width,height);
         f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
         f.setResizable(false);
         
         // Features of text fields and buttons
         field1 = new JTextField("Number of Seats");
         field1.setSize(100,30);
         field1.setLocation(200,30);
         f.add(field1);
      
         field2 = new JTextField("Number of Agents");
         field2.setSize(110,30);
         field2.setLocation(320,30);
         f.add(field2);
          
         field3 = new JTextField("Max Waiting Time");
         field3.setSize(120,30);
         field3.setLocation(450,30);
         f.add(field3);    
       
         bttn1 = new JButton("Create Seats");
         bttn1.setSize(120,30);
         bttn1.setLocation(600,30);
         f.add(bttn1);
         bttn1.addActionListener(this); 
       
         bttn2 = new JButton("Book");
         bttn2.setSize(80,30);
         bttn2.setLocation(750,30);
         f.add(bttn2);
         bttn2.addActionListener(this);
        
         f.setVisible(true);
               
    }
    
    public void actionPerformed(ActionEvent e) {
          
        if(e.getActionCommand() == "Create Seats") {
        
              createSeat(); 
              
        }
    
        else { 
            
            book(); 
            
        } 
    }      
    
    public void run() {  
        
          for(int i=0 ; i<seats.size() ; i++) {
           
            lock.lock();          
            seats.get(i).setText("Booked by "+Thread.currentThread().getName());
            seats.get(i).setBackground(Color.red) ;      
            lock.unlock();
       
             try{
                
              Thread.currentThread().sleep(maxwaitingTime); }
             catch(InterruptedException e) {
                 e.getMessage() ; }  
              }  
          
    }
          
    // This is what happens when user clicks button of Create Seats .
    public void createSeat() {
        
            int seat = Integer.valueOf(field1.getText());
            int x = 15 ;
            int y = 75 ;

            for(int i=1 ; i<=seat ; i++){
                                
                JTextField txt = new JTextField("Not Booked");
                txt.setBackground(Color.yellow);
                txt.setSize(120,30);
                txt.setLocation(x,y);
                txt.setEditable(false);
                f.add(txt);
                seats.add(txt);
                x = x + 120 ;  
                
                if(x >= 900) {
                  x = 15 ;
                  y = y + 50 ;
                }
    } }
    
    // This is what happens when user clicks button of Book .
    public void book(){
    
        maxwaitingTime = Integer.valueOf(field3.getText()); 
        int numberofThread = Integer.valueOf(field2.getText());
          
           for(int i=1 ; i<=numberofThread ; i++) {
          
            Thread thread = new Thread(this);
            thread.setName("Agent "+i);
            thread.start();         
    
            }
           
           // To display a message i wait for completion of threads
          ScheduledExecutorService ses = Executors.newScheduledThreadPool(1);
          Runnable messageTask = () -> JOptionPane.showMessageDialog(f, message());
          ses.schedule(messageTask,(seats.size()*maxwaitingTime)+2000, TimeUnit.MILLISECONDS);

    }
    
    public static void main(String[] args){
    
        new Assignment2();
    
    }

    // This method finds how many seats are booked by threads 
    public String message(){
        
       String message = "";
       List<String> booked = new ArrayList<String>();
         
        for(int i = 0 ; i<seats.size() ; i++){
        
         booked.add(seats.get(i).getText().substring(10));

        }
        
       List<String> dublicates = new ArrayList<String>();
       
       for(int i=0 ; i<booked.size(); i++){
           
          if(dublicates.contains(booked.get(i))) {
            booked.remove(i);
            i--;
            continue;
          } 
           
         message = message + booked.get(i)+" booked "+Collections.frequency(booked,booked.get(i))+" seat(s)"+System.lineSeparator() ;
         dublicates.add(booked.get(i)) ;
         
       }
              
        return message ; 
    }
    
}
