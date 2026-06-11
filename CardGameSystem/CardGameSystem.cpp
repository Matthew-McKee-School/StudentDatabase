//Matthew McKee
//Note: I think there is an issue with the display functions and I'm not sure if its my fault or how to fix it.

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <Windows.h>

using namespace std;

struct Card
{
    string rank; // stores the visible card rank ("2", "10", "K", "A")
    string suit; // stores the visible suit symbol ("♥", "♣", "♦", "♠")
    int rankValue; // stores the numeric value used for sorting/comparing cards
    int suitValue; // stores the numeric value used for sorting suits
};

const int DECK_SIZE = 52;
const int HAND_SIZE = 5;

void buildDeck(Card deck[]);
void shuffleDeck(Card deck[]);
void displayDeck(Card deck[]);
void displayHand(Card hand[]);
void dealHand(Card deck[], Card hand[]);
void sortHand(Card hand[]);
void sortByRank(Card deck[], int size);
void sortBySuit(Card deck[], int size);
void searchHand(Card hand[]);



int main()
{
    srand(time(0));

    Card deck[DECK_SIZE];
    Card hand[5];
    int menu_choice;

    buildDeck(deck);

    do {
        cout << "Menu Options : \n1. Shuffle Deck \n2. Sort Deck by Number \n3. Sort Deck by Suit \n4. Deal Hand(5 cards) \n5. Sort Hand \n6. Search Hand \n7. Exit";
        cout << "\n\nYour choice: ";
        cin >> menu_choice;

        switch (menu_choice) {
        case 1:
            shuffleDeck(deck);
            break;
        case 2:
            sortByRank(deck, DECK_SIZE);
            break;
        case 3:
            sortBySuit(deck, DECK_SIZE);
            break;
        case 4:
            dealHand(deck, hand);
            break;
        case 5:
            sortHand(hand);
            break;
        case 6:
            searchHand(hand);
            break;
        case 7:
            cout << "Bye.";
            break;
        default:
            cout << "You must input an integer 1-7 \n\n";
            break;
        }

    } while (menu_choice != 7);
}

// ====================== BUILD DECK =======================

void buildDeck(Card deck[]) {
    string card_ranks[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king"};
    string card_suits[] = { "♥", "♣", "♦", "♠" };
    int card_counter = 0;
    
    for (int card_rank_iteration = 0; card_rank_iteration < 13; card_rank_iteration++) {
        for (int card_suit_iteration = 0; card_suit_iteration < 4; card_suit_iteration++) {
            deck[card_counter].rank = card_ranks[card_rank_iteration];
            deck[card_counter].suit = card_suits[card_suit_iteration];
            deck[card_counter].rankValue = card_rank_iteration;
            deck[card_counter].suitValue = card_suit_iteration;
            card_counter++;
        }
    }
    
}

// ===================== SHUFFLE DECK ======================

void shuffleDeck(Card deck[]) {
    int card_position_one;
    int card_position_two;
    for (int shuffle_num = 0; shuffle_num < 200; shuffle_num++) {
        do {
            card_position_one = rand() % 52;
            card_position_two = rand() % 52;
        } while (card_position_one == card_position_two);
        swap(deck[card_position_one], deck[card_position_two]);
    }
    cout << "Shuffling completed. \n\n";

    displayDeck(deck);
}

// ====================== DEAL HAND ========================

void dealHand(Card deck[], Card hand[]) {
    for (int hand_iteration = 0; hand_iteration < 5; hand_iteration++) {
        hand[hand_iteration] = deck[hand_iteration];
    }
    cout << "Your hand has been dealt \n\n";
    displayHand(hand);

}

// ====================== SORT HAND ========================

void sortHand(Card hand[]) {
    int smallest;
    for (int i = 0; i < 5; i++) {
        smallest = i;
        for (int j = i +1; j < 5; j++) {
            if (hand[j].rankValue < hand[smallest].rankValue) {
                smallest = j;
            }
        }
        swap(hand[i], hand[smallest]);
    }
    cout << "\n\n";
    displayHand(hand);
}

// ================== SORT DECK BY RANK ====================

void sortByRank(Card deck[], int size) {
    int smallest;
    for (int i = 0; i < size; i++) {
        smallest = i;
        for (int j = i + 1; j < size; j++) {
            if (deck[j].rankValue < deck[smallest].rankValue) {
                smallest = j;
            }
        }
        swap(deck[i], deck[smallest]);
    }
    cout << "\n\n";
    displayDeck(deck);
}

// ================== SORT DECK BY SUIT ====================

void sortBySuit(Card deck[], int size) {
    int smallest;
    for (int i = 0; i < size; i++) {
        smallest = i;
        for (int j = i + 1; j < size; j++) {
            if (deck[j].suitValue < deck[smallest].suitValue) {
                smallest = j;
            }
        }
        swap(deck[i], deck[smallest]);
    }
    cout << "\n\n";
    displayDeck(deck);
}

// ===================== SEARCH HAND =======================

void searchHand(Card hand[]) {
    char current_suit;
    bool result = false;
    string target;
    cout << "What card would you like to search for? (ex: 3D): ";
    cin >> target;
    for (int hand_iteration = 0; hand_iteration < 5; hand_iteration++) {
        if (target[1] != '0') {
            switch (target[1]) {
            case 'H':
                current_suit = '♥';
                break;
            case 'D':
                current_suit = '♦';
                break;
            case 'C':
                current_suit = '♣';
                break;
            case 'S':
                current_suit = '♠';
                break;
            }
            if (hand[hand_iteration].rank[0] == target[0] && hand[hand_iteration].suit[0] == current_suit) {
                result = true;
            }
        }
        else {
            if (hand[hand_iteration].suit[0] == current_suit) {
                result = true;
            }
        }
    }
    if (result == true) {
        cout << "Yes, you have " << target << endl;
    }
    else {
        cout << "No, you do not have that card. \n";
    }
}

// ================= DISPLAY HAND FUNCTION =================

void displayHand(Card hand[])
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << "\n===== PLAYER HAND =====\n";

    // ==== TOP BORDER ====
    for (int i = 0; i < HAND_SIZE; i++)
    {
        cout << "+-----+ ";
    }
    cout << endl;

    // ==== TOP RANK ====
    for (int i = 0; i < HAND_SIZE; i++)
    {
        cout << "| " << hand[i].rank;

        if (hand[i].rank.length() == 1)
            cout << "   | ";
        else
            cout << "  | ";
    }
    cout << endl;

    // ==== SUIT ROW ====
    for (int i = 0; i < HAND_SIZE; i++)
    {
        cout << "|  ";

        // red suits
        if (hand[i].suit == "♥" || hand[i].suit == "♦")
            SetConsoleTextAttribute(hConsole, 12);
        else
            SetConsoleTextAttribute(hConsole, 7);

        cout << hand[i].suit;

        SetConsoleTextAttribute(hConsole, 7);

        cout << "  | ";
    }
    cout << endl;

    // ==== BOTTOM RANK ====
    for (int i = 0; i < HAND_SIZE; i++)
    {
        if (hand[i].rank.length() == 1)
        {
            cout << "|    " << hand[i].rank << "| ";
        }
        else
        {
            cout << "|   " << hand[i].rank << "| ";
        }
    }
    cout << endl;

    // ================= BOTTOM BORDER =================
    for (int i = 0; i < HAND_SIZE; i++)
    {
        cout << "+-----+ ";
    }
    cout << endl;
}

// ==== DECK DISPLAY FUNCTION ====
void displayDeck(Card deck[])
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << "\n===== DECK (52 CARDS) =====\n\n";

    // ==== ROW 1: RANKS ====
    for (int i = 0; i < DECK_SIZE; i++)
    {
        cout << deck[i].rank;

        // FIX: alignment per slot
        if (deck[i].rank == "10")
            cout << "";   // 2-char rank
        else
            cout << " ";  // 1-char rank padding

        cout << "";       // spacing between cards
    }

    cout << "\n";

    // ==== ROW 2: SUITS ====
    for (int i = 0; i < DECK_SIZE; i++)
    {
        if (deck[i].suit == "♥" || deck[i].suit == "♦")
            SetConsoleTextAttribute(hConsole, 12); // red
        else
            SetConsoleTextAttribute(hConsole, 7);

        cout << deck[i].suit;

        SetConsoleTextAttribute(hConsole, 7);

        // FIX: must match rank spacing exactly
        if (deck[i].rank == "10")
            cout << " ";   // align under 10
        else
            cout << " ";

        cout << "";       // spacing between cards
    }

    cout << "\n";
}





//SetConsoleOutputCP(CP_UTF8);
//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


//string suits[] = { "♥", "♣", "♦", "♠" };