int reverse(int x){
    int reversed;
    int sign;
    int rem;

    reversed = 0;

    if(x < 0) {
        sign = -1;
        x = -x;
    }
    else{
        sign = 1;
    }

    while(x > 0) {
        rem = x-(x/10)*10; 
        reversed = (reversed*10)+rem;
        x = x/10;
    }
    
    reversed = reversed * sign;
    return reversed; /*vai funcionar para número negativo?*/
}

void main(void){
    int num;
    int rev_num;

    num = input();
    rev_num = reverse(num);

    output(rev_num);
}