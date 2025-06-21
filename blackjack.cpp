#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <numeric>

// references
std::string input(std::string prompt);
void dealCard(std::vector<int>& player);
int randomCard();
std::string displayHands(bool play);
bool underLimit(std::vector<int>& player);
void finalResult(bool reveal);

// game assets
const int CARD_AMOUNT = 13;
int cards[CARD_AMOUNT] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
int limit = 21;
bool keep_playing = true;

std::vector<int> dealer_hand;
std::vector<int> client_hand;

// functions
int main() {
    std::srand(std::time(NULL)); // seed rand()

    bool play = false;

    // init game

    std::cout << "\n=====================\nLet's play BlackJack!\n=====================\n" << std::endl;

    for (int deal = 0; deal < 2; deal++) {
        dealCard(dealer_hand);
        dealCard(client_hand);
    };

    // continue playing

    while (!play) {
        if (underLimit(client_hand)) {
            std::cout << displayHands(play) << std::endl;
            std::string deal = input("Another card? (y/n): ");
        
            if (deal == "y") {
                dealCard(client_hand);
            } else {
                play = true;
            }
        } else {
            break;
        }
    }

    while (play && std::accumulate(dealer_hand.begin(), dealer_hand.end(), 0) < 17) {
        dealCard(dealer_hand);
    }

    std::cout << displayHands(play) << std::endl;
    finalResult(play);

    std::string play_again = input("Do you want to play again? (y/n): ");

    if (play_again != "y") {
        keep_playing = false;
    }

    for (int i = 0; i < 50; i++) {
        std::cout << std::endl;
    }

    while (keep_playing) {
        dealer_hand = {};
        client_hand = {};
        main();
    }

    return 0;
}

std::string input(std::string prompt) {
    std::string value;
    std::cout << prompt;
    std::cin >> value;

    return value;
}

void dealCard(std::vector<int>& player) {
    player.push_back(randomCard());
}

int randomCard() {
    return cards[(rand() % CARD_AMOUNT)];
}

std::string displayHands(bool play) {
    std::string dealer_hand_descriptor = "\nDealer's hand\n";
    std::string client_hand_descriptor = "\nYour hand:\n";
    int dealer_draw = std::accumulate(dealer_hand.begin(), dealer_hand.end(), 0);

    for (int card = 0; card < dealer_hand.size(); card++) {
        if (!play) {
            if (card == 0) {
                dealer_hand_descriptor += "[?]";
            } else {
                dealer_hand_descriptor += "[" + std::to_string(dealer_hand[card]) + "]";
            }

        } else {
            dealer_hand_descriptor += "[" + std::to_string(dealer_hand[card]) + "]";
        }
    };

    dealer_hand_descriptor += "\n";
    
    for (int card = 0; card < client_hand.size(); card++) {
        client_hand_descriptor += "[" + std::to_string(client_hand[card]) + "]";
    };

    client_hand_descriptor += "\n";

    return (dealer_hand_descriptor + client_hand_descriptor);
}

bool underLimit(std::vector<int>& player) {
    int hand_sum = std::accumulate(player.begin(), player.end(), 0);
    return hand_sum <= limit;
}

void finalResult(bool reveal) {
    int dealer_draw = std::accumulate(dealer_hand.begin(), dealer_hand.end(), 0);
    int client_draw = std::accumulate(client_hand.begin(), client_hand.end(), 0);

    if (reveal) {
        std::cout << "Dealer drew " << dealer_draw << std::endl;
    }

    std::cout << "You drew " << client_draw << std::endl;

    if (underLimit(client_hand) && (dealer_draw < client_draw || !underLimit(dealer_hand))) {
        std::cout << "\n========\nYou win!\n========\n" << std::endl;
    } else if (dealer_draw == client_draw) {
        std::cout << "\n============\nIt's a draw!\n============\n" << std::endl;
    } else {
        std::cout << "\n=========\nYou lose!\n=========\n" << std::endl;
    }
}