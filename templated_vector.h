#include <iostream>   // std::ostream, std::cout

namespace Pic10b{

    template<typename T>
    class vector{
      private:
        T* the_data;
        size_t the_size;
        size_t the_capacity;

        static const int INIT_CAP = 10;


      public:
        // The big 4 
        vector();
        vector( const vector& );
        vector& operator=( const vector& );
        ~vector();

        // Other members [public]
        bool empty() const;
        size_t size() const;
        size_t capacity() const;
        T front() const;
        T back() const; 
        T at( size_t index ) const;
        T& operator[]( size_t index );
        T operator[]( size_t index ) const;
        vector<T> operator+=(vector<T>&);
        void dump_data_to( std::ostream& out ) const;
        void dump_data() const;
        void push_back( T new_value );
        void pop_back();

      private:
        //Other members [private]
        void reserve( size_t new_capacity );

    }; // end Pic10b::vector


    /** ************************* THE BIG 4 ************************* **/
    template<typename T>
    vector<T>::vector() 
      : the_data(nullptr), the_size(0), the_capacity(INIT_CAP) {

        the_data = new T[the_capacity];
        std::cout << "xxxxxxxxxx Default constructor called" << std::endl;
    }

    template<typename T>
    vector<T>::vector( const vector& source )
      : the_data(nullptr), the_size(source.the_size), 
        the_capacity(source.the_capacity) {

        the_data = new T[the_capacity];

        // Deep copy of internal array
        for ( int i = 0 ; i < the_size ; ++i ){
            the_data[i] = source.the_data[i];
        }
        std::cout << "xxxxxxxxxx Copy constructor called" << std::endl;
    }

    template<typename T>
    vector<T>& vector<T>::operator=( const vector& rhs ) {
        if ( this != &rhs ) {     // Self-assignment?
            // Release old memory and request more 
            delete[] the_data;
            the_data = new T[rhs.the_capacity];

            // Shallow copy non-pointers
            the_size = rhs.the_size;
            the_capacity = rhs.the_capacity;

            // Deep copy internal array
            for ( int i = 0 ; i < the_size ; ++i )
                the_data[i] = rhs.the_data[i];
        }
        std::cout << "xxxxxxxxxx Assignment operator called" << std::endl;
        return *this;
    }
    template<typename T>
    vector<T>::~vector(){
        delete[] the_data;
        std::cout << "xxxxxxxxxx Destructor called" << std::endl;
    }

    /** *********************** OTHER MEMBERS *********************** **/
    template<typename T>
    bool vector<T>::empty() const {
        return the_size == 0;
    }

    template<typename T>
    size_t vector<T>::size() const {
        return the_size;
    }

    template<typename T>
    size_t vector<T>::capacity() const {
        return the_capacity;
    } 

    template<typename T>
    T vector<T>::front() const {
        return *the_data;
    }

    template<typename T>
    T vector<T>::back() const {
        return *(the_data + the_size - 1);
    } 

    template<typename T>
    T vector<T>::at( size_t index ) const {
        if ( index < the_size )
            return the_data[index];
        return the_data[0];
    }

    template<typename T>
    T& vector<T>::operator[]( size_t index ){
        return the_data[index];
    }
    template<typename T>
    T vector<T>::operator[]( size_t index ) const {
        return the_data[index];
    }

    template<typename T>
    void vector<T>::dump_data_to( std::ostream& out ) const {
        out << "Vector (dump): ";
        for ( size_t i = 0 ; i < the_capacity ; ++i )
            out << the_data[i] << ' ';
        out << '\n';
    }
    template<typename T>
    void vector<T>::dump_data() const {
        dump_data_to( std::cout );
    }


    template<typename T>
    void vector<T>::push_back( T new_value ){
        if ( the_size == the_capacity ) 
            reserve( the_capacity + 1 );     // `the_data` is reassigned

        the_data[the_size++] = new_value;
    }

    // This implementation does not shrink the vector (ever)
    template<typename T>
    void vector<T>::pop_back(){
        if ( the_size > 0 )
            --the_size;
    }


    template<typename T>
    void vector<T>::reserve( size_t new_capacity ){
        if ( new_capacity > the_capacity ) {
            if ( new_capacity <= 2 * the_capacity )
                new_capacity = 2 * the_capacity;

            T* old_location = the_data;

            the_data = new T[new_capacity];
            the_capacity = new_capacity;

            for ( size_t i = 0 ; i < the_size ; ++i )
                the_data[i] = old_location[i];

            delete old_location;
        }
    }

    /**
    Templated unitary sum operator adds a vector to a given vector
    @tparam T the type of the vector
    @param right is the vector to be added
    @return copy of the sum of the vector
    */
    template<typename T>
    vector<T> vector<T>::operator+=(vector<T>& right){
        size_t c = (this->size()>right.size())? right.size(): this->size();//the bigger vector of the two is the limit of the for loop 
        for (int i = 0; i < c; ++i)
        {
            this->the_data[i] = this->the_data[i] + right[i];
        }
        return *this;
    }

} // end Pic10b namespace



/** ************************ OTHER FUNCTIONS ************************ **/
template<typename T>
std::ostream& operator<<( std::ostream& out, const Pic10b::vector<T>& v ){
    for ( size_t i = 0 ; i < v.size() ; ++i )
        out << v[i] << ' ';
    return out;
}

/**
Template operator multiplies all elements of vector by a factor
@tparam T the type of the vector
@param mult the multiplication factor
@param v the vector
@return the vector multiplied by the factor
*/
template<typename T>
Pic10b::vector<T> operator *( int mult, Pic10b::vector<T> v ){
    for (size_t i = 0; i < v.size(); ++i)
    {
        v[i] = v[i] * mult;
    }
    return v;
}

/**
Template operator multiplies all elements of vector by a factor
@tparam T the type of the vector
@param mult the multiplication factor
@param v the vector
@return the vector multiplied by the factor
*/

template<typename T>
Pic10b::vector<T> operator *( Pic10b::vector<T> v, int mult ){
    for (size_t i = 0; i < v.size(); ++i)
    {
        v[i] = v[i] * mult;
    }
    return v;
}

/**
Template operator returns the dot product between two vectors
@tparam T the type of the arguments
@param left the first vector
@param right the second vector
@return the dot product
*/
template<typename T>
T operator *( const Pic10b::vector<T>& left, const Pic10b::vector<T>& right ){
    T product=0;
    for (size_t i = 0; i < left.size(); ++i)
    {
        product += left[i] * right[i];
    }
    return product;
}

/**
Template operator adds two vectors together
@tparam T the type of the vector
@param left the first vector
@param right the second vector
@return the sum of two vectors
*/
template<typename T>
Pic10b::vector<T> operator +( Pic10b::vector<T> left, Pic10b::vector<T>& right ){
    return left+=right;
}

/**
Templated operator compares two vectors together
@tparam T the type of the vector
@param left the first vector
@param right the second vector
@return boolean true if left is smaller than right
*/
template<typename T>
bool operator < (const Pic10b::vector<T>& left, const Pic10b::vector<T>& right){
    return (left*left < right*right)? true:false;
}

/**
Templated operator compares two vectors together
@tparam T the type of the vector
@param left the first vector
@param right the second vector
@return boolean true if left is bigger than right
*/
template<typename T>
bool operator > (const Pic10b::vector<T>& left, const Pic10b::vector<T>& right){
    return right < left;
}

/**
Templated operator compares two vectors together
@tparam T the type of the vector
@param left the first vector
@param right the second vector
@return boolean true if left is equal to right
*/
template<typename T>
bool operator == (const Pic10b::vector<T>& left, const Pic10b::vector<T>& right){
    return (!(left < right) && !(right < left));
}

/**
Templated operator compares two vectors together
@tparam T the type of the vector
@param left the first vector
@param right the second vector
@return boolean true if left is not equal to right
*/
template<typename T>
bool operator != (const Pic10b::vector<T>& left, const Pic10b::vector<T>& right){
    return !(left == right);
}

/**
Templated operator compares two vectors together
@tparam T the type of the vector
@param left the first vector
@param right the second vector
@return boolean true if left is less than or equal to right
*/
template<typename T>
bool operator <= (const Pic10b::vector<T>& left, const Pic10b::vector<T>& right){
    return (left < right) || (left == right);
}

/**
Templated operator compares two vectors together
@tparam T the type of the vector
@param left the first vector
@param right the second vector
@return boolean true if left is greater than or equal to right
*/
template<typename T>
bool operator >= (const Pic10b::vector<T>& left, const Pic10b::vector<T>& right){
    return (right < left) || (left == right);
}

template<typename T>
void print_vector( const Pic10b::vector<T>& v ){
    if ( v.empty() )
        std::cout << "Vector is empty\n";
    else
        std::cout << "Vector (contents): " << v << '\n' ;
} 