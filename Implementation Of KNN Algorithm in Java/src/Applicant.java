
    public class Applicant {
    
      double social ;          
      double algorithm ;    //  Features Of Applicant           
      double gpa  ;           
      double age ;            
      int y ;                
    
    
    double result ;   // Actually this is not a feature of applicant .This represents the closeness of the new applicant 
                      // to person who have already applied to job
   
    
    public Applicant(){
      // Default constructor
    }
    
    
     public Applicant(double social,double algorithm,double gpa,double age){
    
         this.social = social ;       // This constructor is for new comer. It doesn't accept feature of y.Because
         this.algorithm = algorithm ; // it is unknown whether he/she will be hired or not.      
         this.gpa = gpa ;
         this.age = age ;
    
    }
   
     
}

