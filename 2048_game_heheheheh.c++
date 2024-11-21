#include<iostream>
 #include<chrono>
 #include<thread>
#include <unistd.h>
#include <utility>
#include <conio.h> 
#include <iomanip>

void printMatrix(int , int , int , int ); // function to print the matrix
int homescreen();
void game();

void winscreen();



// making 2048 game HAHHAHAHAHAHAH 
//using 4 * 4 matrix

//matrix to be public 
int matrix[4][4] = {2};

const int terminalWidth = 120;
const int terminalHeight = 30;

int cat_index = 0;

//color to be public // not used yet , wanted to make a color gradient w.r.t time, but not doing it now.......
const std::string colors[] = {
        "\033[31m",  // Red
        "\033[32m",  // Green
        "\033[33m",  // Yellow
        "\033[34m",  // Blue
        "\033[35m",  // Magenta
        "\033[36m",  // Cyan
        "\033[0m"    // Reset to default
};

int main ()
{

    homescreen();

    return 0;
}

int homescreen()
{
    
    std::string pica = R"(
                                                                                          
                                                                                          
   ..                                                                                     
 ::::::.:. ..                                                                             
  .:.::.: .::.::                                                              .:..        
    -- :    . -.:-..                                                   :: -- :-.:-.::     
    :- =         : .- -.                                         .. -- :: :   - -- --     
     : ::             :- ::                                   :: ::          :: :: :      
       .- .            .- -.                              . ::.:. ..           :-.:-.     
        . -:              .- =. :. :. :. -- -:::-:.:. ...-- .                 .:-::.      
         .:.:.               :: :: ::                                   .:.::             
            ::.                                                       : ::                
             - -:                                                   :.-:.                 
               :- =- :                                        .  ..-- .                   
                . -                                           . .-:.                      
               .:..       :. -                     :-            :- -                     
              .::       :    -.                  -  - -:          - -:                    
             : =:       : =- =:                   -.--.-           : =-                   
             - -                    . .. .                           -- .                 
             - -: :: :               ::                  :: ::      .:.:.                 
            -- -. .. .-                                - ..  . --    :.:.                 
            -- -  .. .-              -- :: .          .-  . .  --    .:.-:                
            -- -: -- -            .:.:.     :          - :: -: -        :-                
            .- =                  --.       =             . .           --                
             = =:                  : =: :: =:                         -= -                
               :- .                                                    - :                
                :..                                                  : :                  
                 .:                                                  - -.                 
                ..:. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. -:.-. .. .           
                                                                                          
⠀)";

    std::cout << pica << std::endl;
    
    std::cout << "\033[35m";
    //aling center
    std::string title = "Welcome to 2048 Game!";
    std::string instruction1 = "Instructions: Use wasd keys to move the tiles, and press enter to merge them.";
    std::string instruction2 = "Press any key to start the game.";
    std::string instruction3 = "Press F to exit the game.";

    int startRow = terminalHeight / 2 - 2;
    int titleCol = (terminalWidth - title.length()) / 2;
    int instr1Col = (terminalWidth - instruction1.length()) / 2;
    int instr2Col = (terminalWidth - instruction2.length()) / 2;
    int instr3Col = (terminalWidth - instruction3.length()) / 2;

    std::cout << "\033[" << startRow << ";" << titleCol << "H" << title << std::endl;
    std::cout << "\033[" << startRow + 1 << ";" << instr1Col << "H" << instruction1 << std::endl;
    std::cout << "\033[" << startRow + 2 << ";" << instr2Col << "H" << instruction2 << std::endl;
    std::cout << "\033[" << startRow + 3 << ";" << instr3Col << "H" << instruction3 << std::endl;


    char input;
    std::cin.get(input);
    if(input == 'f' || input == 'F')
    {
        return 0;
    }
    else{
        game();
    }

    return 0;
    
}


void game()
{
    std::pair<int, int> position; // Correct type declaration
    position.first = 0;           // Assigning integer value
    position.second = 0;

    std::pair<int, int> selected_pos; // Correct type declaration
    selected_pos.first = -1;         // Use an appropriate value instead of NULL
    selected_pos.second = -1;
    

    //set the matrix to 2 ;
    for (int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            matrix[i][j] = 2;
        }
    }
    
    while(true)
    {
        
        
        system("cls");
        printMatrix(position.first, position.second ,selected_pos.first, selected_pos.second);

        //geting player input to play 
        char input;
        input = _getch();

        //CHECK FOR WIN
        if( matrix[position.first][position.second] == 2048)
        {
            std::cout << "Congratulations! You win!" << std::endl;
            winscreen();
        }

        if(input == 'W' || input == 'w')
        {
            if( position.first > 0)
                position.first--;

        }
        else if(input == 'A' ||input == 'a' )
        {
            if(position.second > 0) 
            {
                position.second--;
            }
        }
        else if( input == 'S' || input == 's' )
        {
            if( position.first < 4)
                position.first++;
        }
        else if(input == 'D' || input == 'd' )
        {
            if(position.second < 4) 
            {
                position.second++;
            }

        }
        else if(input == 'Q' || input == 'q' )
        {
            selected_pos.first = position.first;
            selected_pos.second = position.second;
        }
        else if(input == 'E' || input == 'e' )
        {
            if ((abs(position.first - selected_pos.first) == 1 && position.second == selected_pos.second) || 
                (position.first == selected_pos.first && abs(position.second - selected_pos.second) == 1)) 
            {
                // Check if the values are the same before merging
                if (matrix[position.first][position.second] == matrix[selected_pos.first][selected_pos.second]) 
                {
                    matrix[position.first][position.second] *= 2; 
                    matrix[selected_pos.first][selected_pos.second] = 2; 
                    position.first = selected_pos.first;
                    position.second = selected_pos.second;
                } 
                else 
                {
                    std::cout << "Cannot merge different values" << std::endl;
                }
            } 
            else 
            {
                std::cout << "Invalid move" << std::endl;
            }

        }
        else if(input == 'F'||input == 'f' )
        {
            break;
        }


        
    }
    //homescreen();
    winscreen();

}

std::string cats[3] = { R"(
   /\_/\  
  (='.'=) 
  (")__(")
)" ,
R"( 
   /\_/\  
  ( -.- ) 
   > ^ <
)",
R"(
   /\_/\ 
  ( o.o )
   > ^ <
)"};

void printMatrix(int x, int y , int sx , int sy)
{
    // system("cls");
    //print the updated matrix

    //center it 

    
    
    std::cout << colors[cat_index%6];
    std::string cat = cats[cat_index%3];

    std::cout << "\033[H\033[J"; 
    std::cout << "\n\n";        
    std::cout << cat << std::endl;

    int padding = 20; 
    for (int i = 0; i < 4; i++) {

        std::cout << std::string(padding, ' ');

        for (int j = 0; j < 4; j++) {

            if (x == i && y == j) {
                std::cout << "\033[5;32m"; 
            } else if (sx == i && sy == j) {
                std::cout << "\033[36m";
            } else {
                std::cout << "\033[0m"; 
            }


            std::cout << "| " << std::setw(4) << matrix[i][j] << " ";
        }
        std::cout << "|" << std::endl;

        // Add a separator row for the box
        std::cout << std::string(padding, ' ');
        std::cout << "+------" << "+------" << "+------" << "+------+" << std::endl;
    }

    // Reset the color at the end
    std::cout << "\033[0m";

    // Display instructions
    std::cout << std::endl
              << std::string(padding, ' ')
              << "Use WASD to move, Q to Select, and E to switch; to play the game" << std::endl;
    std::cout << std::string(padding, ' ') << "Press F to exit the game" << std::endl;

    cat_index++;
}

void winscreen() {
//YOUT HAVE WON


//clear the screen
system("cls");

std::cout << colors[cat_index%6];
std::string cat = R"(                                                                              
                                                   .-.                                      
                                                 `I;. "?                                    
                                                <^    "?                                    
                                             .I;.     "?                                    
                                            ,!        "?                                    
                                         .I;'         "?  "^                                
                                        ,!            "?   'l                               
                                      .;'                                                   
                                      "".                                                   
                                  ,;.`^^,                        :::::i_                    
                                 ,,                                  't^                    
                                 _                                  .)`                     
                                .]                                  <'                      
                                 _                  ^'             ,:                       
                                 ,,                ?'?"           ';                        
                                  ,:.     .,`       ^'                                      
                                     .                ."'.^.    ^                           
                                    .;                ^.';'     '|.                         
                                    .;                           .?,                        
                                    .;                             <`                       
                                    .;                              i.                      
                                    .;  ",                          `]                      
                                    .^   '"                          `                                                                                                
                                    '     '       '.                 .                      
                                   .?    ^',.     !`                 !+.           _.       
                                   .~     .       >'                  ^|.        .l`        
                                   'I             <.                   +^       .<.         
                                   `!     ..     .-.     .             !,      `"           
                                   .[.  .,".      >^  .`:'        '"  .)`   .Il.            
                                     `^`.          '^`'.     """^.>? .ii    '               
                                                                 .` .i'         
)";


    std::cout << cat << std::endl;

    std::cout << "\n\n";
    std::cout << std::string(40, '*') << std::endl;
    std::cout << "*       You have won the 2048 game!       *" << std::endl;
    std::cout << std::string(40, '*') << std::endl;
    std::cout << "Press any key to exit" << std::endl;
    std::cin.get();
    exit(0);

}



