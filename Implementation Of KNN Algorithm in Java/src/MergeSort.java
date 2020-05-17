public class MergeSort {
    
 // Why did i choose Merge Sort algorithm ? Why not bubble sort or insertion sort or quick sort.
 // Because closeness of new comer to applicants changes with the value of new comer.Maybe results will become partly sorted.
 // Maybe it will not .We can't predict.Thats why i chose MergeSort algoritm.It is better than other sorting algorithms 
 // in worst case .
     
     public void merge(Applicant arr[], int l, int m, int r) { 
		
		int n1 = m - l + 1; 
		int n2 = r - m; 
                
		Applicant L[] = new Applicant [n1]; 
		Applicant R[] = new Applicant [n2]; 
		                                       // I changed MergeSort a little bit. Because i have to sort an array                                                        
		for (int i=0; i<n1; ++i)               // which comprised of objects not just integers
			L[i] = arr[l + i]; 
		for (int j=0; j<n2; ++j) 
			R[j] = arr[m + 1+ j]; 	
	
		int i = 0, j = 0; 
		int k = l; 
                
		while (i < n1 && j < n2) 
		{ 
			if (L[i].result <= R[j].result) 
			{ 
				arr[k] = L[i]; 
				i++; 
			} 
			else
			{ 
				arr[k] = R[j]; 
				j++; 
			} 
			k++; 
		} 
		
		while (i < n1) 
		{ 
			arr[k] = L[i]; 
			i++; 
			k++; 
		} 

		while (j < n2) 
		{ 
			arr[k] = R[j]; 
			j++; 
			k++; 
		} 
	} 
     
     public void sort(Applicant arr[], int l, int r) { 
		if (l < r) 
		{ 			
			int m = (l+r)/2; 		 
			sort(arr, l, m); 
			sort(arr , m+1, r); 
			merge(arr, l, m, r); 
		} 
	}   
    
    
    
    
}
