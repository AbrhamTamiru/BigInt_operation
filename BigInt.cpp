// Name Abrham Tamiru
// Class (CECS 325-02)
// Project Name (Prog 7 – 3n+1(BigInt))
// Due Date (5/4/2023)
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.
#include <iostream>
#include<limits.h>
#include <vector>
#include<algorithm> 
#include <string>
using namespace std;

class BigInt {
private:
    vector<int> v;
public:
    BigInt(); // default constructor – set value to 0
    BigInt(int); // int constractor 
    BigInt(string); //string constractor 
    BigInt operator+(BigInt); //adding two BigInt
    BigInt operator++();    // prefix increament 
    BigInt operator++(int); // postfix increament 
    BigInt operator*(BigInt);  // multiplication operator 
    BigInt half(); // return half the value
    bool isOdd(); // check if it is odd
    bool isEven();  // check if it is even
  
    bool operator==(BigInt); // equal operator 
    bool operator<(BigInt); //less operator
    friend ostream& operator<<(ostream&, const BigInt&) ;
};

BigInt::BigInt() {
    v={};
}
BigInt::BigInt(int x) {
    while (x > 0) {
        v.push_back(x % 10);
        x /= 10;
    }
}

BigInt::BigInt(string s) {
    for (int i = s.size() - 1; i >= 0; i--) {
        v.push_back(s[i]);
    }
}

BigInt BigInt::operator+(BigInt b) {
    BigInt sum;
    int carry = 0;
    int i = 0, j = 0;
    int digit;
    while (i < v.size() || j < b.v.size() || carry > 0) {
        int result = carry;
        if (i < v.size()) {
            result += v[i];
            i++;
        }
        if (j < b.v.size()) {
            result += b.v[j];
            j++;
        }
        carry = result / 10;
        digit = result % 10;
        sum.v.push_back(digit);
    
    }
    return sum;
}

BigInt BigInt::operator++() {
    BigInt result = operator+(1);
    operator=(result);
    return result;
}

BigInt BigInt::operator++(int) {
    BigInt temp = *this;
    *this = *this + 1;
    return temp;
}

BigInt BigInt::operator*(BigInt b) {
    BigInt product;
    if (b == 0) {
        return BigInt(0);
    }
    int carry = 0;
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < b.v.size() || carry > 0; j++) {
            if (j < b.v.size()) {
                carry += v[i] * b.v[j];
            }
            if (product.v.size() < i + j + 1) {
                product.v.push_back(0);
            }
            carry += product.v[i + j];
            product.v[i + j] = carry % 10;
            carry /= 10;
        }
    }
    while (product.v.size() > 1 && product.v.back() == 0) {
        product.v.pop_back();
    }
    
    return product;
}

BigInt BigInt::half() {
    BigInt result;
    int carry = 0;
    for (int i = v.size() - 1; i >= 0; i--) {
        int val = carry * 10 + v[i];
        int digit = val / 2;
        carry = val % 2;
        result.v.push_back(digit);
    }
    reverse(result.v.begin(), result.v.end());
    while (result.v.size() > 1 && result.v.back() == 0) {
        result.v.pop_back();
    
    }
  
    return result;
}


bool BigInt::isOdd() 
{
    return v[0]& 1; 
}
bool BigInt::isEven() 
{
   
    return !isOdd();
}

bool BigInt::operator==( BigInt c)
{ 
    if(v.size()!=c.v.size())
    {
        return false;
    }
    for (int i =0;i<v.size();i++){
        if(v[i]!=c.v[i])
        {
            return false;
        }
    }
    return true;
} 
bool BigInt::operator<( BigInt d)  {
    if (v.size() < d.v.size())
    {
        return true;
    } 
    else if (v.size() > d.v.size()) 
    {
        return false;
    } 
    else 
    {
        for (int i =0; i<v.size();i++)
        {
            if(v[i]<d.v[i])
            {
                return true;
            }
        }
        return true;
    }
}

std::ostream& operator<<(std::ostream& out, const BigInt& num)
{
    if (num.v.size() > 8) {
        int exponent = num.v.size() - 1;
        out << num.v[num.v.size() - 1] << ".";
        for (int i =num.v.size()-2 ; i >=num.v.size()-8 ; i--) // 7 digits after " ."
        {
        
            out << num.v[i];
        }
        out << "e" << exponent;
    } 
    else {
        for (int i = num.v.size() - 1; i >= 0; i--) {
            out << num.v[i];
        }
    }
    return out;
}

struct ThreeNp1 {
    BigInt start;
    BigInt steps;
    BigInt max;
    BigInt odd;
    BigInt even;
};

void findthreeN(BigInt n, ThreeNp1 &Np1, bool printSteps=false)
{
    if(printSteps)
    {
        cout << "->(" << n << ")";
    }
    
    if (n == 1) // BigInt::operator==( )

    {
        return;
    }

    else if (n.isEven()) // BigInt::isEven() 
    {
        if (Np1.max < n) //BigInt::operator<( )
            Np1.max = n;
        Np1.even++; // BigInt::operator++( )
        Np1.steps++;
        n= n.half();  //BigInt::half( ) 
        findthreeN(n, Np1);
        
    }
   
    else if(n.isOdd()) // BigInt::isodd() 
    {
        if (Np1.max < n)
            Np1.max = n;
        Np1.odd++;   
        Np1.steps++;
        n = n*BigInt(3)+BigInt(1);  //BigInt::operator*( )  and BigInt::operator+( )
        findthreeN(n, Np1);
    }
    else
    {
        cout<<"How I get here"<<endl;  
    }
}

void print(BigInt start, ThreeNp1 &Np1)
{
    Np1.start = start;  // initialize start field
    findthreeN(start, Np1);
}

int main()
{
    BigInt MAX(INT_MAX);
    cout << "The largest integer is " << MAX << endl;
    cout << "Twice the largest integer is " << MAX + MAX << endl;
    
    BigInt start(INT_MAX);
    bool printSteps=true;
    ThreeNp1 N {start, 0, 0, 0, 0};  // initialize struct fields
    print(start, N);
    cout << endl;
    cout << "start: " << N.start << endl;
    cout << "steps: " << N.steps << endl;
    cout << "max: " << N.max << endl;
    cout << "odds: " << N.odd << endl;
    cout << "evens: " << N.even << endl;
    return 0;
}


