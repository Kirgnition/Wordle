/*
WORDLE

The player must guess a 6 letter word in no more than 6 tries
- if a letter of the typed word is in the secret word, the program should say so
- if a letter of the typed word is in the secret word and is in the right place, the program should say so

~Interface~
Let secret word = letter
# = letter in secret word but not in the right place
@ = letter in secret word and in the right place

example:

# #        
L E T T E R
T R O P H Y

*/
#include<iostream>
#include<cstring>
#include<fstream>
#include<random>

const std::string path = "./words.txt";

//get a random word from the file words.txt
std::string random_word() {
    std::ifstream input(path);
    std::string buffer;

    // initialize random()
    srand(time(NULL));

    // get number of lines in file
    int lines = 0;
    while(std::getline(input, buffer)) {
        lines++;
    }
    // return to beginning of file
    input.clear();
    input.seekg(0);
    int random_index = random()%lines + 1;

    //get random word
    lines = 0;
    while(std::getline(input,buffer)) {
        if(lines == random_index) {
            return buffer;
        }
        lines++;
    }
}

/*
check if inputted word has one or more characters present in secret_word too, returns an array
with three possible values at each secret word's index: 0 if the guessed letter is not present, 1 if present but not in the right place, 2 if present and in the right place
eg:
secret word: DALILA
guess: PLANTY
return: {0,1,1,0,0,0}

secret word: DALILA
guess: MANILA
return: {0,2,0,2,2,2}
*/
void check(const std::string guess, const std::string secret_word, int* array) {
    //for each letter in guess, loop through secret_word and set indexes[i] to 1 if the letter is in secret_word, 2 if it is and it's in the same position too
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            if (i == j && guess[i] == secret_word[j]) {
                array[i] = 2;
                break;
            }
            else if (guess[i] == secret_word[j]) {
                array[i] = 1;
            }
        }
    }
}


//prints ' ' if the letter isn't present, '#' if it is in the wrong position, '@' if it is in the right position
void print_check(const int array[]) {
    for(int i = 0; i < 6; i++) {
        switch (array[i])
        {
        case 0:
            std::cout << "_ ";
            break;
        case 1:
            std::cout << "# ";
            break;
        case 2: 
            std::cout << "@ ";
            break;
        }
    }
    std::cout << std::endl;
}

//print a word with each character separated by whitespace
void print_word(const std::string word) {
    for (int i = 0; i < 6; i++) {
        std::cout << word[i] << " ";
    }
}

//set all elements in an array of length 6 to 0
void reset(int array[]) {
    for(int i = 0; i < 6; i++) {
        array[i] = 0;
    }
}

//check if won (ie all elements in the array are equal to 2)
bool won(const int array[]) {
    bool flag = true;
    for(int i = 0; i < 6; i++) {
        if (array[i] != 2) return false;
    }
    return true;
}

int main() {
    bool flag = true;
    //main game loop
    while(flag) {
        //get random word
        std::string secret_word = random_word();
        std::string guess, play_again;
        
        std::cout << "GUESS THE WORD!\n" << std::endl;
        bool guessed = false;
        //cycle 6 times (6 guesses)
        for(int i = 0; i < 6 && !guessed; i++) {
            //initialize indexes array to 0
            int indexes[6] = {0};
            //ask for input from user, then turn it to uppercase
            do{
                std::cin >> guess;
            } while(guess.length() != 6);
            for(auto &c : guess) c = toupper(c);


            //print inputted word
            print_word(guess);
             std::cout << "  try #" << i+1 << std::endl;

            //generate index array and print the result
            check(guess, secret_word, indexes);
            print_check(indexes);

            //winning case
            if(won(indexes)) {
                std::cout << "YOU WON!!!" << std::endl;
                guessed = true;
            }
            
        }

        //losing case
        if(!guessed) {
            std::cout << "YOU LOST!!" << std::endl;
            std::cout << "THE WORD WAS " << secret_word << std::endl;
        }

        //handle end of game
        std::cout << "PLAY AGAIN? Y/N " << std::endl;
        std::cin >> play_again;
        if (play_again == "n" || play_again == "N") {
            flag = false;
            }
        //print separator
        std::cout << "============\n" << std::endl; 
    }
    return 0;
}
