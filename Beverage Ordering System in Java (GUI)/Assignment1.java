
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JRadioButton;
import javax.swing.JTextField;


public class Assignment1 extends JFrame implements ActionListener {
    
    
    //  Global Variables 
    
    private JButton bttn1,bttn2 ;
    private JTextField txt1 ;
    private JRadioButton radio1,radio2,radio3,radio4 ;
    private JLabel lbl1,lbl2,lbl3,lbl4 ;
    private JComboBox cmbox ;
    private ButtonGroup bg ;
    private JFrame f;
    private ArrayList<Beverage> list = new ArrayList<>();
    
    
    public Assignment1(){
    
      
       // our frame window's features 
        
      f = new JFrame("Welcome To CoffeeLand ") ;
      f.setLayout(null) ;  
      f.setSize(400,400) ;
      f.setDefaultCloseOperation(EXIT_ON_CLOSE);
      f.setResizable(false);
      initializations() ;
      f.setVisible(true) ;
      
      
      
     
      
    }
    
    
    
     //  I did  initializations here.
    
    
    public void initializations(){
                                       
    String[] sizes = {"Small","Medium","Large"}  ;
   
    
    cmbox = new JComboBox(sizes);
    cmbox.setSize(100,25);
    cmbox.setLocation(50,50);
    f.add(cmbox);
    
    
    lbl1 = new JLabel("Select Size");
    lbl1.setSize(75,50);
    lbl1.setLocation(50,10);
    f.add(lbl1);   
        
        
    lbl2 = new JLabel("Select which type of beverage you want to order");
    lbl2.setSize(300,100);
    lbl2.setLocation(50,50);
    f.add(lbl2);
    
    lbl3 = new JLabel("Select how many glasses you want to order");
    lbl3.setSize(300,100);
    lbl3.setLocation(50,130);
    f.add(lbl3);
    
    radio1 = new JRadioButton("Juice");
    radio1.setSize(70,60);
    radio1.setLocation(45,110);
    f.add(radio1);
    
    radio2 = new JRadioButton("Water");
    radio2.setSize(70,60);
    radio2.setLocation(140,110);
    f.add(radio2);
    
    radio3 = new JRadioButton("Tea");
    radio3.setSize(70,60);
    radio3.setLocation(240,110);
    f.add(radio3);
    
    radio4 = new JRadioButton("Coffee");
    radio4.setSize(70,60);
    radio4.setLocation(310,110);
    f.add(radio4);
    
    
    bg = new ButtonGroup() ;
    bg.add(radio1); bg.add(radio2); bg.add(radio3); bg.add(radio4);
    
    
    txt1 = new JTextField();
    txt1.setSize(300,30);
    txt1.setLocation(50,195);
    f.add(txt1);
    
    
    bttn1 = new JButton("Add");
    bttn1.setSize(80,40);
    bttn1.setLocation(50,230);
    f.add(bttn1);      
    bttn1.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e){
            
            add();
 
        }});
    
    bttn2 = new JButton("Order");
    bttn2.setSize(100,40);
    bttn2.setLocation(250,230);
    f.add(bttn2);   
    bttn2.addActionListener(new ActionListener() {  
    
    public void actionPerformed(ActionEvent e){
    
     
       order();  
    
    
    }});
            
    
    lbl4 = new JLabel();
    lbl4.setSize(300,100);
    lbl4.setLocation(50,240);
    f.add(lbl4);   
        
    
    
    
    
    
    
    
    
    }
    
    
   
    
    // this is what happens when user click order button
    
    public void order(){
    
      String details = "" ;
        
      for(int i = 0 ; i < list.size() ; i++){
      
      
      details = details +list.get(i).getQuantity()+" "+list.get(i).getName()+" "+String.valueOf(list.get(i).getPrice())+" (price for one piece)"+System.lineSeparator() ;
			
      
      
      }
        
      JOptionPane.showMessageDialog(f,details,"Order Details",JOptionPane.INFORMATION_MESSAGE); 
      JOptionPane.showMessageDialog(f,"You should pay "+expenditure(),"Expenditure",JOptionPane.INFORMATION_MESSAGE);
    
    }
            
     
   
    
    public void reset() {
    
        list.clear();
        txt1.setText("");
        radio1.setSelected(false);
        radio2.setSelected(false);
        radio3.setSelected(false);
        radio4.setSelected(false);
    }
    
    
    // this shows us how much we have to pay  
    
    public String expenditure(){
    
    double sum = 0.0 ;
    
    for(int i = 0 ; i < list.size() ; i++ ){
    
    sum = sum + list.get(i).getQuantity()*list.get(i).getPrice() ;
    
    
    }
    
    return String.valueOf(sum);
    
    }
    
     // this is what happens when user click add button
    public void add(){
    
     String[] fruits = {"Apple","Orange","Pineapple"} ;    
        
        
        if(txt1.getText().equals("")&&(radio1.isSelected()||radio2.isSelected()||radio3.isSelected()||radio4.isSelected()))  {
    
     JOptionPane.showMessageDialog(f,"Choose a beverage and enter an amount","Message",JOptionPane.ERROR_MESSAGE);
 }
        
 else {
  
     if(radio1.isSelected()){
      
         
         
         
  String fruit = (String) JOptionPane.showInputDialog(f,"Select a fruit ","Selection",JOptionPane.QUESTION_MESSAGE,null,fruits,fruits[0]) ;   
  
  if(fruit == "Apple") {
            lbl4.setText(txt1.getText()+" glass(es) of "+fruit+" juice added"); 
            Beverage beverage = new Beverage("Juice", (String) cmbox.getItemAt(cmbox.getSelectedIndex()), Integer.valueOf(txt1.getText()),false) ;
            list.add(beverage) ;
    
  
  
  }
  
  
  
  else if(fruit == "Orange") {
            lbl4.setText(txt1.getText()+" glass(es) of "+fruit+" juice added");
            Beverage beverage = new Beverage("Juice", (String) cmbox.getItemAt(cmbox.getSelectedIndex()), Integer.valueOf(txt1.getText()),false) ;
            list.add(beverage) ;  }
  
  
   else if(fruit == "Pineapple") {
            lbl4.setText(txt1.getText()+" glass(es) of "+fruit+" juice added");
            Beverage beverage = new Beverage("Juice", (String) cmbox.getItemAt(cmbox.getSelectedIndex()), Integer.valueOf(txt1.getText()),false) ;
            list.add(beverage) ; 
  
   
   }
     }
 
     
     
  
       if(radio2.isSelected()) {
       
      int a = JOptionPane.showConfirmDialog(f,"Would you like ice ?","İce Selection",JOptionPane.YES_NO_OPTION);
       
       if(a == JOptionPane.YES_OPTION) {
               lbl4.setText(txt1.getText()+" glass(es) of water with ice added"); 
     Beverage beverage = new Beverage("Water", (String) cmbox.getItemAt(cmbox.getSelectedIndex()), Integer.valueOf(txt1.getText()),true) ;
            list.add(beverage) ; 
       
       
       
       
       }
       
       
       
       else {
            lbl4.setText(txt1.getText()+" glass(es) of water with no ice added"); 
         Beverage beverage = new Beverage("Water", (String) cmbox.getItemAt(cmbox.getSelectedIndex()), Integer.valueOf(txt1.getText()),false) ;
            list.add(beverage) ; 
       
       
       
       
       }
       }
     
       
       if(radio3.isSelected()) {
       
           int a = JOptionPane.showConfirmDialog(f,"Would you like sugar ?","Sugar Selection",JOptionPane.YES_NO_OPTION);

       if(a == JOptionPane.YES_OPTION) {
               lbl4.setText(txt1.getText()+" glass(es) of tea with sugar added"); 
        Beverage beverage = new Beverage(radio3.getText(), (String) cmbox.getItemAt(cmbox.getSelectedIndex()), Integer.valueOf(txt1.getText()),true) ;
            list.add(beverage) ; }
       
       
       else {
            lbl4.setText(txt1.getText()+" glass(es) of tea with no sugar added");
       Beverage beverage = new Beverage(radio4.getText(), (String) cmbox.getItemAt(cmbox.getSelectedIndex()), Integer.valueOf(txt1.getText()),false) ;
            list.add(beverage) ;
       
       
       }
       
       }
       
       
       
       
       if(radio4.isSelected()) {
       
           int a = JOptionPane.showConfirmDialog(f,"Would you like milk ?","Milk Selection",JOptionPane.YES_NO_OPTION);

       if(a == JOptionPane.YES_OPTION) {
               lbl4.setText(txt1.getText()+" glass(es) of coffee with milk added"); 
       Beverage beverage = new Beverage(radio4.getText(),(String)cmbox.getItemAt(cmbox.getSelectedIndex()), Integer.valueOf(txt1.getText()),true) ;
            list.add(beverage) ;
       
       
       }
       
       
       
       else {
            lbl4.setText(txt1.getText()+" glass(es) of tea coffee with no milk added"); 
          Beverage beverage = new Beverage(radio4.getText(), (String) cmbox.getItemAt(cmbox.getSelectedIndex()), Integer.valueOf(txt1.getText()),false) ;
            list.add(beverage) ;
       
       }
       
       }
     
 } 
     
      
        
    
    
    }
    
    
    
    public static void main(String[] args){
    
    
     Assignment1 assignment1 = new Assignment1() ;
    
    
    
    }

  
    public void actionPerformed(ActionEvent e) {
        
    }

  
    
    
}

// I created a class for beverages. I hold beverage's features here.
 class Beverage{

private String name ;
private String size ;
private double quantity ;
private boolean additionalFeature ;
private double price ;

// Beverage's price may differ according to its size or additionial request (Milk,sugar,ice)


    public Beverage(String name, String size, double quantity, boolean additionalFeature) {
        this.name = name;
        this.size = size;
        this.quantity = quantity;
        this.additionalFeature = additionalFeature;
        
        
        if(size == "Small" && name == "Juice" ) 
                                      this.price = 5.25 ; 
            
        else if(size == "Medium" && name == "Juice") 
                                       this.price = 7.25 ;
        
        
        else if(size == "Large" && name == "Juice")
                                        this.price = 9.25 ;
        
        
        else if(size == "Small" && name == "Water" ) {
        
        if(additionalFeature == false){
        
        this.price = 3.00 ;
                
        }
           else
             this.price = 5.00 ;
        
        }
        
     
        
        else if(size == "Medium" && name == "Water" ) {
        
        if(additionalFeature == false){
        
        this.price = 6.00 ;
                
        }
        
        else
            this.price = 8.00 ;
        
        }
        
      
        else if(size == "Large" && name == "Water" ) {
        
        if(additionalFeature == false){
        
        this.price = 9.00 ;
                
        }
        
        else
             this.price = 9.50 ;
        
        }
        
        
        
        else if(size == "Small" && name == "Tea" ) {
        
        if(additionalFeature == false){
        
        this.price = 4.25 ;
                
        }
        
        else
             this.price = 5.0 ;
        
        }
        
        else if(size == "Medium" && name == "Tea" ) {
        
        if(additionalFeature == false){
        
        this.price = 5.25 ;
                
        }
        
        else
             this.price = 6.0 ;
        
        }
        
        else if(size == "Large" && name == "Tea" ) {
        
        if(additionalFeature == false){
        
        this.price = 7.25 ;
                
        }
        
        else
             this.price = 8.0 ;
        
        }
        
        
        else if(size == "Small" && name == "Coffee" ) {
        
        if(additionalFeature == false){
        
        this.price = 6.25 ;
                
        }
        
        else
             this.price = 9.0 ;
        
        }
        
        
        
         else if(size == "Medium" && name == "Coffee" ) {
        
        if(additionalFeature == false){
        
        this.price = 7.25 ;
                
        }
        
        else
             this.price = 11.25 ;
        
        }
        
        
        
        else if(size == "Large" && name == "Coffee" ) {
        
        if(additionalFeature == false){
        
        this.price = 10.25 ;
                
        }
        
        else
             this.price = 15.25 ;
        
        }
        
        
    }

    public double getQuantity() {
        return quantity;
    }

    public double getPrice() {
        return price;
    }

    public String getName() {
        return name;
    }


    
    








}
