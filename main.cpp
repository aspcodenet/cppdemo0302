#include <iostream> 
#include <iomanip> 
#include <vector>
#include <fstream>
#include <string>
#include <list>
#include <stack>
#include <queue>

// Containers? Algorithms? LATER! 
//         we needs one thing (with a common name) to contain many thing        
//  // dynamic  as in we dont know on beforehand how many players we will have - we need a container that can grow and shrink as needed - we can use a vector or a list - vector is more efficient for random access and cache locality, but list is more efficient for inserting and deleting elements in the middle of the container - we will use a vector for this example, but we will also look at lists later
//   std::vector<Child> myChildren;

// an array by definition is a *contiguous* block of memory that can hold a fixed number of elements of the same type
// c++ std::array<>, std::vector (is an array but its dynamic in size)
//       static in size  ,            vector is dynamic in size

// std::list - doubly linked list - each element is a node that contains a value and a pointer to the next and previous node - efficient for inserting and deleting elements in the middle of the container, but not efficient for random access - we will use a vector for this example, but we will also look at lists later
// std::list = really fast  for insert and delete - but reallty slow for random access
// UTILIZES CACHE REALLY BAD!!!!!

// vector vs list!
//    vector - list  = GENERIC store all customers, all players

// Vector with smart pointers? Is that a good thing?
// yes, if we need polymorphism 
// no in all other cases - pointers will be contigous but the objects they point to will not be contigous - this can lead to cache misses and poor performance - we can use a vector of objects instead of a vector of pointers in most cases - if we need polymorphism, we can use a vector of unique_ptrs or shared_ptrs - but we should be careful with memory management and avoid memory leaks


// USE VECTOR - STORE OBJECTS DIRECTLY IN THE VECTOR - THIS IS MORE EFFICIENT FOR CACHE LOCALITY AND AVOIDING MEMORY LEAKS - UNLESS WE NEED POLYMORPHISM, THEN WE CAN USE A VECTOR OF UNIQUE_PTRS OR SHARED_PTRS - BUT WE SHOULD BE CAREFUL WITH MEMORY MANAGEMENT AND AVOID MEMORY LEAKS
// data locality
// the copy problem – emplace_back

// 17:25

//  queue, stack data structures
// templates





// composite datatype - user defined
struct Player{ // same as class
    int jerseyNumber;
    std::string name;
    int born;
public: // public by default in struct, private by default in class
    Player(int jerseyNumber = 0, std::string name = "", int born = 0) : jerseyNumber(jerseyNumber), name(name), born(born) {} // default constructor - initializes the members to default values    
};


Player createPlayer(){

    std::cout << "Creating a new player..." << std::endl;
    
    Player p; // Creating a new player "object""

    std::cout << "Enter a name:" ;
    
    std::getline(std::cin >> std::ws, p.name);
    // can add space and then read the name - std::ws - consume any leading whitespace characters before reading the name

    std::cout << "Enter a jersey number:" ;
    std::cin >> p.jerseyNumber;
    std::cout << "Enter a birth year:" ;
    std::cin >> p.born;

    return p; // return a player struct
}


void listAllPlayers(const std::vector<Player> &players){ 
    std::cout << "Listing all players..." << std::endl;
    for(const Player &p : players){  // players[0] = "Foppa" p is a copy of the player in the vector - we can use references to avoid this - const std::vector<Player> &players - we can also use pointers - const std::vector<Player> *players
        std::cout << "Name: " << p.name << ", Jersey Number: " << p.jerseyNumber << ", Born: " << p.born << std::endl; // output the player's information
    }
}


void saveToFile(const std::vector<Player> &players) {
    std::ofstream outFile("players.txt"); // Creates or overwrites players.txt

    if (outFile.is_open()) {
        for (const Player &p : players) {
            // Writing data separated by spaces or newlines
            outFile << p.name << " " << p.jerseyNumber << " " << p.born << "\n";
        }
        outFile.close();
        std::cout << "Data saved successfully!\n";
    } else {
        std::cerr << "Unable to open file for writing.\n";
    }
}




void readFromFile(std::vector<Player> &players) {
    std::ifstream inFile("players.txt");
    Player p;

    if (inFile.is_open()) {
        players.clear(); 
        while (inFile >> p.name >> p.jerseyNumber >> p.born) {
            players.push_back(p);
        }
        inFile.close();
        std::cout << "Data loaded successfully!\n";
    } else {
        std::cout << "No save file found. Starting fresh.\n";
    }
}

template<typename T>
T findBiggest(T i,T j, T k){
    if(i > j && i > k){
        return i;
    }
    if(j > i && j > k){
        return j;
    }
    return k;
}


template<typename T,int N>
class MyArray{
public: 
    MyArray(){
        antal = 0;
    }
    void add(T one){
        // om antalet > max 
        // return "ERROR - finns inte plats för mer"
        // 
        things[antal] = one;
        antal++;
    }

    int size(){
        return antal;
    }
    T getAt(int index){
        return things[index];
    }


private:
    int antal;
    T things[N]; // KAN INTE VÄXA/KRYMPA .- statisk i storlek  , INTE static
};






int main(){
    MyArray<int, 5> myArray; // create an array of integers with a maximum size of 5
    myArray.add(10);
    
    MyArray<float, 10> myArray11; // create an array of integers with a maximum size of 5
    myArray11.add(10.2f);

    int u = findBiggest<int>(10, 20, 30);
    std::cout << "The biggest number is: " << u << std::endl;

    float f = findBiggest<float>(10.2f, 20.234234f, 30.123f);


    std::string s = findBiggest<std::string>("Stefan", "Anna", "Zlatan"); // Zlatan


    std::queue<int> q; // queue of integers - first in, first out (FIFO) - we can use a queue to store the players in the order they were created - we can also use a stack to store the players in the order they were created - last in, first out (LIFO)
    int i = 0; // allocation i is a piece of memory in RAM
    // CPU must fetch the data from the I variable and store inside the CPU (register) 
    // set to 0  (THIS HAPPENS INSIDE THE CPU)
    // and stored in RAM at a specific address (e.g. 0x7ffdfc8b8c) - this is called the memory address of the variable i

    i = i + 1; // CPU must fetch the data from the I variable and store inside the CPU (register)
    // add by one (THIS HAPPENS INSIDE THE CPU
    // and stored in RAM at a specific address (e.g. 0x7ffdfc8b8c) - this is called the memory address of the variable i

    //std::list<Player> playerList; // "list" of players - kommer senare

    std::vector<Player> players; // "list" of players - kommer senare
    readFromFile(players); // load players from file if it exists


    int selection;
    std::string name;
    //Player p1(10, "Foppa", 1967); // create a player struct - this is called "emplace_back" - construct the player in place - more efficient than creating a player and then adding it to the vector - we can also use push_back but it will create a copy of the player and then add it to the vector - this can be inefficient for large data structures - we can use emplace_back to avoid this
    // p1 is one
    //players.push_back(p1); // add a player to the list of players - this is called "emplace_back" - construct the player in place - more efficient than creating a player and then adding it to the vector - we can also use push_back but it will create a copy of the player and then add it to the vector - this can be inefficient for large data structures - we can use emplace_back to avoid this
    // a variadic number of parameters - SAME AS YOUR CONSTRUCTOR - the parameters are passed to the constructor of the player struct - this is called "emplace_back" - construct the player in place - more efficient than creating a player and then adding it to the vector - we can also use push_back but it will create a copy of the player and then add it to the vector - this can be inefficient for large data structures - we can use emplace_back to avoid this
    players.emplace_back(10, "Foppa", 1967);
    while(true){
        std::cout << "1. Create a player " << std::endl;
        std::cout << "2. Delete a player " << std::endl;
        std::cout << "3. List all players " << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter action:";
        std::cin >> selection;
        if(selection == 1){
            Player p = createPlayer(); // create a player struct
            //players.push_back(p); // add the player to the list of players
            players.emplace_back(p.jerseyNumber, p.name, p.born); // emplace_back calls yours constructor directly - construct the player in place - more efficient than creating a player and then adding it to the vector - we can also use push_back but it will create a copy of the player and then add it to the vector - this can be inefficient for large data structures - we can use emplace_back to avoid this
                                // emplace_back() - construct the player in place - more efficient
        }else if(selection == 2){
            std::cout << "Delete a new player" << std::endl;
        }else if(selection == 3){ // players vector 1 000 000 players
            listAllPlayers(players);  // all function parameters are passed by value - a copy of the argument is made and passed to the function - in this case, a copy of the vector of players is made and passed to the function - this can be inefficient for large data structures - we can use references to avoid this
        }else if(selection == 4){
            saveToFile(players); // save players to file before exiting
            break;
        }
    }


}