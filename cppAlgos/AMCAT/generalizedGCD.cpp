// INCLUDE HEADER FILES NEEDED BY YOUR PROGRAM
// SOME LIBRARY FUNCTIONALITY MAY BE RESTRICTED
// DEFINE ANY FUNCTION NEEDED
// FUNCTION SIGNATURE BEGINS, THIS FUNCTION IS REQUIRED

    // METHOD SIGNATURE BEGINS, THIS METHOD IS REQUIRED
    int gcd(int a, int b) 
    { 
    // Everything divides 0  
    if (a == 0) 
       return b; 
    if (b == 0) 
       return a; 
   
    // base case 
    if (a == b) 
        return a; 
   
    // a is greater 
    if (a > b) 
        return gcd(a-b, b); 
    return gcd(a, b-a); 
    }
    
    int generalizedGCD(int num, int* arr)
    {
        // WRITE YOUR CODE HERE
        if (num == 1) {
            return arr[0];
        }
        int first = arr[0];
        arr++;
        return gcd(first,generalizedGCD(num-1,arr));
    }
    // METHOD SIGNATURE ENDS

// FUNCTION SIGNATURE ENDS
