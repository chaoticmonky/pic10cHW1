/* *************************************************
   Ricardo Salazar
   July 2017

   Driver for the Pic10b::vector<double> class.
   ************************************************* */

#include "templated_vector.h"   // Pic10b::vector<ItemType>
#include <iostream>          // std::cout
#include <iomanip>           // std::boolalpha
#include <string>            // std::string
#include <cmath>             // sqrt(...)

using std::cout;
using std::boolalpha;
using std::string;
using Pic10b::vector;


int main(){
    const string itemType = "double";
    const int SIZE = 7;
    const double PI = 3.1416;
    const int newEntry = 100;

    cout << "Statement:\tvector<double> v1;\n";
    vector<double> v1;

    cout << "\nAction(s):\tv1 is populated with " << SIZE 
         << " " + itemType + " values\n";
    for ( int i = 1 ; i <= SIZE ; ++i )
        v1.push_back( i * PI );

    cout << "\nStatement:\tvector<double> v2(v1);\n";
    vector<double> v2(v1);

    cout << "\nStatement:\tvector<int> v3 = v1;\n";
    vector<double> v3 = v1;

    cout << "\nAction(s):\t3rd entry of v1 is modified (" << PI * newEntry << ")"
         << "\n\t\tone more " << itemType + " value is pushed back ("
         << 2 * PI * newEntry << ")\n" << "\t\tv1 is displayed\n";
    v1[2] = PI * newEntry ;
    v1.push_back( 2 * PI * newEntry );
    cout << "\tv1 = " << v1 << '\n';

    cout << "\nAction(s):\tv2 is displayed\n";
    cout << "\tv2 = " << v2 << '\n';

    cout << "\nStatement:\tv3 = v2 = v1;\n";
    v3 = v2 = v1; 

    cout << "\nStatement:\tv1 = ( 2.0 * v2 ) * 3.0;\n";
    v1 = ( 2.0 * v2 ) * 3.0;

    cout << "\nAction(s):\tv1, v2, and v3 are displayed\n";
    cout << "\tv1 = " << v1 << '\n';
    cout << "\tv2 = " << v2 << '\n';
    cout << "\tv3 = " << v3 << '\n';

    cout << "\nStatement:\tv2 = v3 + v3;\n";
    v2 = v3 + v3;

    cout << "\nStatement:\tv3 += v2;\n";
    v3 += v2;

    cout << "\nAction(s):\tv1, v2, and v3 are displayed\n";
    cout << "\tv1 = " << v1 << '\n';
    cout << "\tv2 = " << v2 << '\n';
    cout << "\tv3 = " << v3 << '\n';

    cout << "\nAction(s):\tEntries 2--"<< SIZE 
         <<" in v1, v2, and v3 replaced by 0\n";
    for ( int i = 2 ; i < v1.size() ; ++i )
        v1[i] = v2[i] = v3[i] = 0.0;

    cout << "\nAction(s):\tv1, v2, and v3 are displayed\n";
    cout << "\tv1 = " << v1 << '\n';
    cout << "\tv2 = " << v2 << '\n';
    cout << "\tv3 = " << v3 << '\n';

    cout << "\nAction(s):\tThe dot product of v2 and v3 is displayed\n";
    cout << "\tv2 * v3 = " << v2 * v3 << '\n';

    cout << "\nAction(s):\tThe norms of v1, v2, and v3 are displayed\n";
    cout << "\t|| v1 || = " << sqrt(v1*v1) << '\n';
    cout << "\t|| v2 || = " << sqrt(v2*v2) << '\n';
    cout << "\t|| v3 || = " << sqrt(v3*v3) << '\n';

    cout << "\nAction(s):\tBoolean comparisons involving v1, v2, and v3\n";
    cout << std::boolalpha
         << "\tv1 <  v2 is " << ( v1 <  v2 ) << " because || v1 || >  || v2 ||\n"
         << "\tv2 <= v1 is " << ( v2 <= v1 ) << "  because || v2 || <= || v1 ||\n"
         << "\tv1 >  v3 is " << ( v1 >  v3 ) << "  because || v1 || >  || v3 ||\n"
         << "\tv3 >= v1 is " << ( v3 >= v1 ) << " because || v3 || <  || v1 ||\n"
         << "\tv2 == v3 is " << ( v2 == v3 ) << '\n'
         << "\tv2 != v3 is " << ( v2 != v3 ) << '\n';
    cout << '\n';

    cout << "\tv1 == 3.0 * v2 is " << ( v1 == 3.0 * v2 ) << '\n';
    cout << '\n';
    cout << "\t2.0 * v3 == v2 * 3.0 is " << ( 2.0 * v3 == v2 * 3.0 ) << '\n';

    cout << "\nStatement:\treturn 0;\n";
    return 0;
}