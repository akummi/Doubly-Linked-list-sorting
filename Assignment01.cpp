// Author: Avery Nguyen
// Section: Section 1003
// Date Las Modiefied: 8/31/2021
// Program deescription: This program demonstrates an understanding of classed, doubly linked lists. This program takes a command line argument list of numbers and sorts them using a selection sort.

#include <iostream>
#include <fstream> 

using namespace std; 

template  <typename  type >
class LL {
    struct  node {
        type  data;
        node * prev;
        node * next;
    };
    
public:
    class  iterator {
        
        public:
            friend  class LL;
            iterator ();
            iterator(node *);
            type  operator *()  const;
            const  iterator& operator ++(int);
            const  iterator& operator --(int);
            bool  operator ==( const  iterator &)  const;
            bool  operator !=( const  iterator &)  const;
        private:
            node * current;
        };
        
        LL();
        LL(const LL <type >&);
        const LL <type >&  operator =(const LL<type >&);
        ~LL();
        
        void  headInsert(const  type &);
        void  tailInsert(const  type &);
        iterator  begin() const;
        iterator  end() const;
        void  swapNodes(iterator&, iterator &);
    private:
    node * head;
    node * tail;
};

//*********************************************
// ITERATOR CLASS CONSTRUCTORS/FUNCTIONS 
//*********************************************


//defualt constructor: sets current to NULL

template <typename type>
LL<type>::iterator::iterator() {

    this ->current = NULL; 
}

//constructor: sets current to passed ptr

template <typename type>
LL<type>::iterator::iterator(node * ptr) {

    this -> current = ptr;
}

//dereference operator: returns current->data

template <typename type>
type LL<type>::iterator::operator*() const {

    return current -> data;
}

//++operator: moves iterator over one right 

template <typename type>
const typename LL<type>::iterator& LL<type>::iterator::operator++(int) {

    this->current = this->current->next; 

    return *this;
}

//--operator: moves iterator over one left 

template <typename type>
const typename LL<type>::iterator& LL<type>::iterator::operator--(int) {

    this->current = this->current->prev; 
    return *this;
}

//==operator: returns true if equal, false if not. 

template <typename type>
bool LL<type>::iterator::operator==(const iterator& rhs) const {
    
    if(this->current == rhs.current){
        return true;
    }
    else{
        return false;
    }
}

//!=operator: returns true if not euqal and false if else

template <typename type>
bool LL<type>::iterator::operator!=(const iterator& rhs) const {

    if(this->current != rhs.current){
        return true;
    }
    else{
        return false;
    }
}

//*********************************************
// LL CLASS CONSTRUCTIORS/FUNCTIONS
//*********************************************


// default constructor: sets head/tail to null 

template <typename type>
LL<type>::LL(){

    this -> head = NULL;
    this -> tail = NULL;
}

// deep copy constructor: performs a deep copy of list to this list

template <typename type>
LL<type>::LL(const LL<type>& copy) {
    
    LL<int>::iterator copying;
    copying = copy.begin(); 

    this->head = NULL; 
    this->tail = NULL; 

    while (copying != NULL){
        this->tailInsert(*copying);
        copying++;
    }


}
// =operator: performs a deep copy with operator

template <typename type>
const LL<type>& LL<type>::operator=(const LL<type>& rhs){

    if(this == rhs){
        return *this;
    }
    if(this->head != NULL && this->tail != NULL){
        this->head = NULL;
        this->tail = NULL;
    }
    LL<int>::iterator copying;
    copying = rhs.begin(); 
    
    while (copying != NULL){
        this->tailInsert(*copying);
        copying++;
    }
}
 
//deconstructor: deconstructs linked list 

template <typename type>
LL<type>::~LL(){
node *remove = this->head;
while(remove != NULL){
    node* next = remove->next; 
    delete remove; 
    remove = next; 
} 
this->head = NULL; 
this->tail = NULL;
}

//headinsert: puts in item as a new head

template <typename type>
void LL<type>::headInsert(const type& item){
    
    if(this->head == NULL && this->tail == NULL){
        node *ins = new node(); 
        ins->data = item; 
        this->head = ins; 
        this->tail = ins; 
    }
    else{
        node *ins = new node();
        ins->data = item;
        ins->prev = NULL; 
        ins->next = this->head; 
        this->head->prev = ins;
        this->head = ins; 
        

    }
}

//tailinset: puts in item as a new tail 

template <typename type>
void LL<type>::tailInsert(const type& item){

    if(this->head == NULL && this->tail == NULL){
        node *ins = new node(); 
        ins->data = item; 
        this->head = ins; 
        this->tail = ins; 
    }
    else{
        node *ins = new node();
        ins->data = item;
        ins->prev = this->tail; 
        ins->next = NULL; 
        this->tail->next = ins;
        this->tail = ins; 
    }
}

//begin: returns a iterator who's current is the head 

template <typename type>
typename LL<type>::iterator LL<type>::begin() const{

iterator it(this->head); 
return it; 
}

//end: returns a iterator who's current is the tail 

template <typename type>
typename LL<type>::iterator LL<type>::end() const{

iterator it(this->tail); 
return it; 
}

//swapnodes: swaps the location of two nodes 

template <typename type>
void LL<type>::swapNodes(iterator& it1, iterator& it2){

        //initalizes pointers for i1's current, next, and previous
        node *i1 = it1.current; 
        node *i1_prev = i1->prev;
        node *i1_next = i1->next; 

        //initalizes pointers for i2's current, next, and previous
        node *i2 = it2.current; 
        node *i2_prev = i2->prev;
        node *i2_next = i2->next; 

        //checks if i1 is next to i2 (i1 is leftmost)
        if(i1->next == i2){

            //swaps i1/i2 next and previous
            i1->next = i2_next; 
            i2->next = i1; 
            i1->prev = i2;
            i2->prev = i1_prev; 

            //checks if i2 is the tail, and sets i1 to tail if true
            if(i2 == this->tail){
                this->tail = i1;
            }
            //otherwise, sets i2's next nodes previous to i1
            else{
                i2_next->prev = i1; 
            }

            //checks if i1 is the head, and sets i2 to the head if true
            if(i1 == this->head){
                this->head = i2;
            }
            //otherwise, sets i1's previous nodes next to i2 
            else{
                i1_prev->next = i2; 
            }

            //swaps it1 and it2's current 
            it1.current = i2;
            it2.current = i1; 
        }

        //checks if i2 is next to i1 (i2 is left most)
        else if(i2->next == i1){

            //swaps i2 and i1 next and prev
            i2->next = i1_next; 
            i1->next = i2; 
            i2->prev = i1;
            i1->prev = i2_prev; 

            //checks if i1 is the tail and sets i2 to the tail if true
            if(i1 == this->tail){
                this->tail = i2;
            }
            //otherwise, sets i1's next nodes previous to i2 
            else{
                i1_next->prev = i2; 
            }

            //checks if i2 is the head and sets i1 to head if true
            if(i2 == this->head){
                this->head = i1; 
            }
            //otherwise, sets i2's previous nodes next to i1
            else{
                i2_prev->next = i1; 
            }


            //swaps it1 and it2's current 
            it1.current = i2;
            it2.current = i1; 
        }

        //general case (nodes are not adjacent)
        else{

        //swaps i1's next and previous to i2's
        i1->next = i2_next; 
        i1->prev = i2_prev; 

        //swaps i2's next and previous to i1's
        i2->next = i1_next; 
        i2->prev = i1_prev; 

        //checks if i1 is the head
        if(i1 == this->head){
        }
        //otherwise, sets i1's previous nodes next to i2 
        else{
        i1_prev->next = i2; 
        }

        //checks if i1 is the tail
        if(i1 == this->tail){
        }
        //otherwise sets i1s next nodes previous to i2
        else{
        i1_next->prev = i2;
        }

        //checks if i2 is the head
        if(i2 == this->head){
        }
        //otherwise, sets i2's previous nodes next to i1
        else{
        i2_prev->next = i1; 
        }

        //checks if i2 is the tail
        if(i2 == this->tail){
        }
        //otherwise sets i2s next nodes previous to i1
        else{
        i2_next->prev = i1;
        }

        //replacs respective head/tail if needed
        if(i1 == this->head){
            this->head = i2;
        }
        else if(i2 == this->head){
            this->head = i1; 
        }

        if(i1 == this->tail){
            this->tail = i2;
        }
        else if(i2 == this->tail){
            this->tail = i1; 
        }

        //swaps it1 and it2's current 
        it1.current = i2;
        it2.current = i1; 
        }
}

//*********************************************
//START OF MAIN 
//*********************************************

int main(int argc, char *argv[]){

    //ensures user inputs the correct number of arguments
    if (argc != 2) {
        cout << "ERROR: Invalid number of arguments \n ./a.out sometextfile.txt" << endl;
    }

    ifstream infile; 
    infile.open(argv[1]);
    if(!infile.is_open()){
        cout << "ERROR: file failed to open" << endl; 
        return 0; 
    }  

    LL<int> list; 

    //populates the linked list with ints read from file
    while(!infile.eof()){
        int in; 
        infile >> in; 
        if(infile.eof()){
            break; 
        }
        
        list.tailInsert(in);
    }

   
    //selection sort 

    //initializing variables 
    LL<int>::iterator sort; 
    LL<int>::iterator finalsort;
    LL<int>::iterator n(NULL); 
    LL<int>::iterator maxcurrent; 
    int max; 
    finalsort = n; 

    //loops until the unsorted head of list reaches the sorted tail
    for(sort = list.begin(); sort != finalsort; finalsort--){
        sort = list.begin();
        maxcurrent = sort;
        max = *sort; 
        sort++;
        //checks for new max through unsorted section of list
        while(sort != finalsort){
            if(max < *sort){
                max = *sort;
                maxcurrent = sort; 
            }
            sort++;
        }
        //sets tail to end of list if it was NULL
        if(finalsort == n){
            finalsort = list.end();
        }
        //checks if the tail is the max value
        else{
            if(max < *finalsort){
                max = *finalsort;
                maxcurrent = finalsort; 
            }
        }
        //swaps the max with the current tail 
        list.swapNodes(maxcurrent, finalsort);
        sort = list.begin();
    }

    //prints out the entire linked list 

    LL<int>::iterator begin;     
    begin = list.begin();
    LL<int>::iterator end; 
    end = list.end(); 
    end++;
    while(begin != end){
   
        cout<< *begin << endl; 
        begin++;
    }
    return 0;
}