#include <iostream> 
#include <iomanip> 
#include <vector>
#include <fstream>
#include <string>

// Containers? Algorithms? LATER! 
// vector vs list!
// data locality
// the copy problem – emplace_back
// templates





// composite datatype - user defined
struct Player{ // same as class
    int jerseyNumber;
    std::string name;
    int born;
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



int main(){

    std::vector<Player> players; // "list" of players - kommer senare
    readFromFile(players); // load players from file if it exists


    int selection;
    std::string name;
    while(true){
        std::cout << "1. Create a player " << std::endl;
        std::cout << "2. Delete a player " << std::endl;
        std::cout << "3. List all players " << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter action:";
        std::cin >> selection;
        if(selection == 1){
            Player p = createPlayer(); // create a player struct
            players.push_back(p); // add the player to the list of players
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