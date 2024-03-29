#include <iostream>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <climits>
#include <cstring>
#include <algorithm>
#include <string>
using namespace std;


class Node {
public:
    int id; // generated randomly
    int reward_r; // r of a particular reward you obtained
    int count; // to avoid duplicate id nodes (maintain count of the id)
    Node* left;
    Node* right;
    int height;

    Node(int i, int r) {
        id = i;
        reward_r = r;
        count = 1;
        left = NULL;
        right = NULL;
        height = 1;
    }
};

class AVLTree {
public:
    Node* root;
    int size;

    AVLTree() {
        root = NULL;
        size = 0;
    }

    int generateID() {
        if (size == 0) {
            return 100;
        }
        else {
            srand(time(NULL));
            int random_id = rand() % 201;
            while (search(random_id)) {
                random_id = rand() % 201;
            }
            return random_id;
        }
    }

    int getHeight(Node* node) {
        if (node == NULL) {
            return 0;
        }
        else {
            return node->height;
        }
    }

    int balancefactor(Node* node) {
        if (node == NULL) {
            return 0;
        }
        else {
            return getHeight(node->left) - getHeight(node->right);
        }
    }


    void updateHeight(Node* node) {
        int left_height = getHeight(node->left);
        int right_height = getHeight(node->right);
        node->height = max(left_height, right_height) + 1;
    }


    Node* RL(Node* node) {
        Node* new_root = node->right;
        node->right = new_root->left;
        new_root->left = node;
        updateHeight(node);
        updateHeight(new_root);
        return new_root;
    }

    Node* RR(Node* node) {
        Node* new_root = node->left;
        node->left = new_root->right;
        new_root->right = node;
        updateHeight(node);
        updateHeight(new_root);
        return new_root;
    }


    Node* balance(Node* node) {
        updateHeight(node);
        int balance_factor = balancefactor(node);
        if (balance_factor > 1) {
            if (balancefactor(node->left) < 0) {
                node->left = RL(node->left);
            }
            return RR(node);
        }
        else if (balance_factor < -1) {
            if (balancefactor(node->right) > 0) {
                node->right = RR(node->right);
            }
            return RL(node);
        }
        else {
            return node;
        }
    }

    Node* insert(Node* node, int i, int r) {

        if (node == NULL) {
            size++;
            return new Node(i, r);
        }
        else if (i < node->id) {
            node->left = insert(node->left, i, r);
        }
        else if (i > node->id) {
            node->right = insert(node->right, i, r);
        }
        else {
            node->reward_r = r;
            node->count++;
            return node;
        }
        node = balance(node);
        return node;
    }


    Node* search(int i)
    {
        Node* current = root;
        while (current != NULL) {
            if (i < current->id) {
                current = current->left;
            }
            else if (i > current->id) {
                current = current->right;
            }
            else {
                return current;
            }
        }
        return NULL;
    }


    Node* delnode(Node* node, int i) {
        if (node == NULL) {
            return node;
        }
        else if (i < node->id) {
            node->left = delnode(node->left, i);
        }
        else if (i > node->id) {
            node->right = delnode(node->right, i);
        }
        else {
            if (node->count > 1) {
                node->count--;
                return node;
            }
            else {
                if (node->left == NULL && node->right == NULL) {
                    delete node;
                    node = NULL;
                }
                else if (node->left == NULL) {
                    Node* temp = node;
                    node = node->right;
                    delete temp;
                }
                else if (node->right == NULL) {
                    Node* temp = node;
                    node = node->left;
                    delete temp;
                }
                else {
                    Node* temp = findMin(node->right);
                    node->id = temp->id;
                    node->reward_r = temp->reward_r;
                    node->count = temp->count;
                    node->right = delnode(node->right, temp->id);
                }
            }
        }
        if (node != NULL) {
            node = balance(node);
        }
        return node;
    }

    Node* findMin(Node* node) {
        while (node->left != NULL) {
            node = node->left;
        }
        return node;
    }

    void displayInOrder(Node* node) {
        if (node == NULL) {
            return;
        }
        displayInOrder(node->left);
        cout << "ID: " << node->id << " r: " << node->reward_r << endl;
        displayInOrder(node->right);
    }

    int findIdByReward(Node* node, int r) {
        if (node == NULL) {
            return -1;
        }

        int leftSearch = findIdByReward(node->left, r);
        if (leftSearch != -1) {
            return leftSearch;
        }

        if (node->reward_r == r) {
            return node->id;
        }

        return findIdByReward(node->right, r);
    }
};



class Graph {
public:
    int size; //also is v 
    char** map;
    int** mat;
    int size2;
    int INF = 9999999999;
    AVLTree inventory;
    int score = 0;
    int ww;
    int* path;
    int cc = 1;

    char getchar(int index)
    {
        int temp = 0;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (temp == index)
                {
                    return map[i][j];
                }
                else
                {
                    temp++;
                }
            }
        }

    }

    void play()
    {
        int id = 0;
        int l = findlocas();

        int choice = -1;

        while (choice != 0)
        {
            system("cls");

            cout << "Floyd Warshall Algorithm          (1)" << endl;
            cout << "Floyd Warshall Algorithm (Custom) (2)" << endl;
            cout << "Dijkstra's Algorithm              (3)" << endl;
            cout << "Dijkstra's Algorithm     (Custom) (4)" << endl;
            cout << "Prim's Algorithm                  (5)" << endl;
            cout << "Kruskal's Algorithm               (6)" << endl;




            cin >> choice;
            if (choice == 0)
            {
                break;
            }

            switch (choice)
            {
            case 1:
            {
                system("cls");

                printMap();

                floydWarshall(400, 0, l);

                score = 0;
                cout << endl;
                for (int i = 0; i < ww; i++)
                {
                    if (getchar(path[i]) == 'J')
                    {
                        id = inventory.generateID();
                        score += 50;
                        inventory.insert(inventory.root, id, 50);
                        cout << "Jewel Obtained." << endl << "Score: " << score << endl;
                        cout << endl;

                    }
                    else if (getchar(path[i]) == 'W')
                    {
                        id = inventory.generateID();
                        score += 30;
                        inventory.insert(inventory.root, id, 30);
                        cout << "Weapon Obtained." << endl << "Score: " << score << endl;
                        cout << endl;

                    }
                    else if (getchar(path[i]) == 'P')
                    {
                        id = inventory.generateID();
                        score += 70;
                        inventory.insert(inventory.root, id, 70);
                        cout << "Potion Obtained." << endl << "Score: " << score << endl;
                        cout << endl;
                    }
                    else if (getchar(path[i]) == '&')
                    {
                        cout << "Dragon Encountered" << endl;
                        if (inventory.findIdByReward(inventory.root, 50) != -1)
                        {
                            inventory.delnode(inventory.root, inventory.findIdByReward(inventory.root, 50));
                            cout << "Jewel Used. " << endl;
                        }
                        else
                        {
                            cout << "No Jewel" << endl;
                            score -= 50;
                        }
                        cout << "Score: " << score << endl;
                        cout << endl;

                    }
                    else if (getchar(path[i]) == '@')
                    {
                        cout << "Werewolf Encountered" << endl;
                        if (inventory.findIdByReward(inventory.root, 30) != -1)
                        {
                            inventory.delnode(inventory.root, inventory.findIdByReward(inventory.root, 30));
                            cout << "Weapon Used. " << endl;
                        }
                        else
                        {
                            cout << "No Weapon" << endl;
                            score -= 30;
                        }
                        cout << "Score: " << score << endl;
                        cout << endl;
                    }
                    else if (getchar(path[i]) == '$')
                    {
                        cout << "Goblin Encountered" << endl;
                        if (inventory.findIdByReward(inventory.root, 70) != -1)
                        {
                            inventory.delnode(inventory.root, inventory.findIdByReward(inventory.root, 70));
                            cout << "Potion Used. " << endl;
                        }
                        else
                        {
                            cout << "No Potion" << endl;
                            score -= 70;
                        }
                        cout << "Score: " << score << endl;
                        cout << endl;
                    }
                    else if (getchar(path[i]) == '%')
                    {
                        cout << "YOU DIED...." << endl << "Score: " << score << endl << endl;
                        break;

                    }
                    else
                    {
                        cout << "Clear Path." << endl << "Score: " << score << endl << endl;
                    }
                }
                system("pause");
                break;
            }

            case 2:
            {
                int nnn;
                cout << "Enter the Starting Location: ";
                cin >> nnn;

                system("cls");

                printMap();
                score = 0;
                floydWarshall(400, nnn, l);

                cout << endl;
                for (int i = 0; i < ww; i++)
                {
                    if (getchar(path[i]) == 'J')
                    {
                        id = inventory.generateID();
                        score += 50;
                        inventory.insert(inventory.root, id, 50);
                        cout << "Jewel Obtained." << endl << "Score: " << score << endl;
                        cout << endl;

                    }
                    else if (getchar(path[i]) == 'W')
                    {
                        id = inventory.generateID();
                        score += 30;
                        inventory.insert(inventory.root, id, 30);
                        cout << "Weapon Obtained." << endl << "Score: " << score << endl;
                        cout << endl;

                    }
                    else if (getchar(path[i]) == 'P')
                    {
                        id = inventory.generateID();
                        score += 70;
                        inventory.insert(inventory.root, id, 70);
                        cout << "Potion Obtained." << endl << "Score: " << score << endl;
                        cout << endl;
                    }
                    else if (getchar(path[i]) == '&')
                    {
                        cout << "Dragon Encountered" << endl;
                        if (inventory.findIdByReward(inventory.root, 50) != -1)
                        {
                            inventory.delnode(inventory.root, inventory.findIdByReward(inventory.root, 50));
                            cout << "Jewel Used. " << endl;
                        }
                        else
                        {
                            cout << "No Jewel" << endl;
                            score -= 50;
                        }
                        cout << "Score: " << score << endl;
                        cout << endl;

                    }
                    else if (getchar(path[i]) == '@')
                    {
                        cout << "Werewolf Encountered" << endl;
                        if (inventory.findIdByReward(inventory.root, 30) != -1)
                        {
                            inventory.delnode(inventory.root, inventory.findIdByReward(inventory.root, 30));
                            cout << "Weapon Used. " << endl;
                        }
                        else
                        {
                            cout << "No Weapon" << endl;
                            score -= 30;
                        }
                        cout << "Score: " << score << endl;
                        cout << endl;
                    }
                    else if (getchar(path[i]) == '$')
                    {
                        cout << "Goblin Encountered" << endl;
                        if (inventory.findIdByReward(inventory.root, 70) != -1)
                        {
                            inventory.delnode(inventory.root, inventory.findIdByReward(inventory.root, 70));
                            cout << "Potion Used. " << endl;
                        }
                        else
                        {
                            cout << "No Potion" << endl;
                            score -= 70;
                        }
                        cout << "Score: " << score << endl;
                        cout << endl;
                    }
                    else if (getchar(path[i]) == '%')
                    {
                        cout << "YOU DIED...." << endl << "Score: " << score << endl << endl;
                        break;

                    }
                    else
                    {
                        cout << "Clear Path." << endl << "Score: " << score << endl << endl;
                    }
                }
                system("pause");
                break;
            }


            case 3:
            {
                system("cls");

                printMap();
                score = 0;
                dijkstra(400, 0, l);


                cout << endl;
                for (int i = 0; i < ww; i++)
                {
                    if (getchar(path[i]) == 'J')
                    {
                        id = inventory.generateID();
                        score += 50;
                        inventory.insert(inventory.root, id, 50);
                        cout << "Jewel Obtained." << endl << "Score: " << score << endl;
                        cout << endl;

                    }
                    else if (getchar(path[i]) == 'W')
                    {
                        id = inventory.generateID();
                        score += 30;
                        inventory.insert(inventory.root, id, 30);
                        cout << "Weapon Obtained." << endl << "Score: " << score << endl;
                        cout << endl;

                    }
                    else if (getchar(path[i]) == 'P')
                    {
                        id = inventory.generateID();
                        score += 70;
                        inventory.insert(inventory.root, id, 70);
                        cout << "Potion Obtained." << endl << "Score: " << score << endl;
                        cout << endl;
                    }
                    else if (getchar(path[i]) == '&')
                    {
                        cout << "Dragon Encountered" << endl;
                        if (inventory.findIdByReward(inventory.root, 50) != -1)
                        {
                            inventory.delnode(inventory.root, inventory.findIdByReward(inventory.root, 50));
                            cout << "Jewel Used. " << endl;
                        }
                        else
                        {
                            cout << "No Jewel" << endl;
                            score -= 50;
                        }
                        cout << "Score: " << score << endl;
                        cout << endl;

                    }
                    else if (getchar(path[i]) == '@')
                    {
                        cout << "Werewolf Encountered" << endl;
                        if (inventory.findIdByReward(inventory.root, 30) != -1)
                        {
                            inventory.delnode(inventory.root, inventory.findIdByReward(inventory.root, 30));
                            cout << "Weapon Used. " << endl;
                        }
                        else
                        {
                            cout << "No Weapon" << endl;
                            score -= 30;
                        }
                        cout << "Score: " << score << endl;
                        cout << endl;
                    }
                    else if (getchar(path[i]) == '$')
                    {
                        cout << "Goblin Encountered" << endl;
                        if (inventory.findIdByReward(inventory.root, 70) != -1)
                        {
                            inventory.delnode(inventory.root, inventory.findIdByReward(inventory.root, 70));
                            cout << "Potion Used. " << endl;
                        }
                        else
                        {
                            cout << "No Potion" << endl;
                            score -= 70;
                        }
                        cout << "Score: " << score << endl;
                        cout << endl;
                    }
                    else if (getchar(path[i]) == '%')
                    {
                        cout << "YOU DIED...." << endl << "Score: " << score << endl << endl;
                        break;

                    }
                    else
                    {
                        cout << "Clear Path." << endl << "Score: " << score << endl << endl;
                    }
                }
                system("pause");
                break;
            }


            case 4:
            {
                int nnn;
                cout << "Enter the Starting Location: ";
                cin >> nnn;

                system("cls");

                printMap();
                score = 0;
                dijkstra(400, nnn, l);

                cout << endl;
                for (int i = 0; i < ww; i++)
                {
                    if (getchar(path[i]) == 'J')
                    {
                        id = inventory.generateID();
                        score += 50;
                        inventory.insert(inventory.root, id, 50);
                        cout << "Jewel Obtained." << endl << "Score: " << score << endl;
                        cout << endl;

                    }
                    else if (getchar(path[i]) == 'W')
                    {
                        id = inventory.generateID();
                        score += 30;
                        inventory.insert(inventory.root, id, 30);
                        cout << "Weapon Obtained." << endl << "Score: " << score << endl;
                        cout << endl;

                    }
                    else if (getchar(path[i]) == 'P')
                    {
                        id = inventory.generateID();
                        score += 70;
                        inventory.insert(inventory.root, id, 70);
                        cout << "Potion Obtained." << endl << "Score: " << score << endl;
                        cout << endl;
                    }
                    else if (getchar(path[i]) == '&')
                    {
                        cout << "Dragon Encountered" << endl;
                        if (inventory.findIdByReward(inventory.root, 50) != -1)
                        {
                            inventory.delnode(inventory.root, inventory.findIdByReward(inventory.root, 50));
                            cout << "Jewel Used. " << endl;
                        }
                        else
                        {
                            cout << "No Jewel" << endl;
                            score -= 50;
                        }
                        cout << "Score: " << score << endl;
                        cout << endl;

                    }
                    else if (getchar(path[i]) == '@')
                    {
                        cout << "Werewolf Encountered" << endl;
                        if (inventory.findIdByReward(inventory.root, 30) != -1)
                        {
                            inventory.delnode(inventory.root, inventory.findIdByReward(inventory.root, 30));
                            cout << "Weapon Used. " << endl;
                        }
                        else
                        {
                            cout << "No Weapon" << endl;
                            score -= 30;
                        }
                        cout << "Score: " << score << endl;
                        cout << endl;
                    }
                    else if (getchar(path[i]) == '$')
                    {
                        cout << "Goblin Encountered" << endl;
                        if (inventory.findIdByReward(inventory.root, 70) != -1)
                        {
                            inventory.delnode(inventory.root, inventory.findIdByReward(inventory.root, 70));
                            cout << "Potion Used. " << endl;
                        }
                        else
                        {
                            cout << "No Potion" << endl;
                            score -= 70;
                        }
                        cout << "Score: " << score << endl;
                        cout << endl;
                    }
                    else if (getchar(path[i]) == '%')
                    {
                        cout << "YOU DIED...." << endl << "Score: " << score << endl << endl;
                        break;

                    }
                    else
                    {
                        cout << "Clear Path." << endl << "Score: " << score << endl << endl;
                    }
                }
                system("pause");
                break;

            }


            case 5:
            {
                system("cls");
                printMap();
                primMST(400);
                system("pause");
                break;
            }

            case 6:
            {
                system("cls");
                printMap();
                Kruskal(400);
                system("pause");
                break;
            }

            }

        }

    }

    Graph(int n = 0)
    {
        ww = 0;
        score = 0;
        size = n;
        size2 = n * n;
        map = new char* [size];
        for (int i = 0; i < size; i++)
        {
            map[i] = new char[size];
        }

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                map[i][j] = '-';
                //graph[i][j] = '-';
            }
        }

        mat = new int* [size2];
        for (int i = 0; i < size2; i++)
        {
            mat[i] = new int[size2];
        }

        for (int i = 0; i < size2; i++)
        {
            for (int j = 0; j < size2; j++)
            {
                mat[i][j] = 0;
                //graph[i][j] = '-';
            }
        }

    }


    void WriteMap(string name)
    {
        ofstream outfile(name);
        if (outfile.is_open()) {
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    outfile << map[i][j] << " ";
                }
                outfile << "\n";
            }
            outfile.close();
        }
    }

    void ReadMap(string name)
    {
        ifstream infile(name);
        if (infile.is_open()) {
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    infile >> map[i][j];
                }
            }
            infile.close();
        }
    }


    ~Graph() {
        for (int i = 0; i < size; i++) {
            delete[] map[i];
        }
        delete[] map;

        for (int i = 0; i < size2; i++) {
            delete[] mat[i];
        }
        delete[] mat;
        delete[] path;
    }

    void printMap() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << map[i][j] << " ";
            }
            cout << endl;
        }
    }

    void GenerateRandomMap()
    {


        char SAFE = 'C';
        char JEWEL = 'J';
        char POTION = 'P';
        char WEAPON = 'W';
        char DEATH = '%';
        char OBSTACLE = '#';
        char DRAGON = '&';
        char GOBLIN = '$';
        char WEREWOLF = '@';
        char CRYSTAL = '*';
        int reward_r_JEWEL = 50;
        int reward_r_WEAPON = 30;
        int reward_r_POTION = 70;


        srand(time(0));


        int random = 0;


        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                random = (rand() % 20) + 1;

                if (random == 1 || random == 2 || random >= 10)
                {
                    map[i][j] = SAFE;
                }
                else if (random == 3)
                {
                    map[i][j] = JEWEL;
                }
                else if (random == 4)
                {
                    map[i][j] = POTION;
                }
                else if (random == 5)
                {
                    map[i][j] = WEAPON;
                }
                else if (random == 6)
                {
                    map[i][j] = DEATH;
                }
                else if (random == 7)
                {
                    map[i][j] = OBSTACLE;
                }
                else if (random == 8)
                {
                    map[i][j] = WEREWOLF;
                }
                else if (random == 9)
                {
                    map[i][j] = DRAGON;
                }
                else if (random == 0)
                {
                    map[i][j] = GOBLIN;
                }

            }
        }

        map[0][0] = SAFE;

        int ran2 = (rand() % 20) + 1;
        random = (rand() % 20) + 1;

        map[random][ran2] = CRYSTAL;



        /*for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                cout << map[i][j] << " ";
            }
            cout << endl;
        }*/

        //cout << endl << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    }

    void GenerateAdjency()
    {

        int a = 0;
        int curr = 0;
        {
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {

                    if (i == 0 && j == 0)//case1
                    {
                        if (map[i][j + 1] == '#')
                        {
                            mat[a][curr + 1] = 100;
                            //cin >> temp;
                        }
                        else
                        {
                            mat[a][i + 1] = 1;
                        }
                        if (map[i + 1][j] == '#')
                        {
                            mat[a][curr + size] = 100;
                        }
                        else {
                            mat[a][curr + size] = 1;
                        }
                    }




                    else if (i == 0 && j != 0 && j < size - 1)//case 2
                    {
                        if (map[i][j + 1] == '#')
                        {
                            mat[a][curr + 1] = 100;
                        }
                        else
                        {
                            mat[a][curr + 1] = 1;
                        }
                        if (map[i + 1][j] == '#')
                        {
                            mat[a][curr + size] = 100;
                        }
                        else
                        {
                            mat[a][curr + size] = 1;
                        }

                        if (map[i][j - 1] == '#')
                        {
                            mat[a][curr - 1] = 100;
                        }
                        else
                        {
                            mat[a][curr - 1] = 1;
                        }

                    }


                    else if (i != 0 && j == 0 && i < size - 1)//case 3
                    {

                        if (map[i][j + 1] == '#')
                        {
                            mat[a][curr + 1] = 100;
                        }
                        else
                        {
                            mat[a][curr + 1] = 1;
                        }
                        if (map[i + 1][j] == '#')
                        {
                            mat[a][curr + size] = 100;
                        }
                        else
                        {
                            mat[a][curr + size] = 1;
                        }

                        if (map[i - 1][j] == '#')
                        {
                            mat[a][curr - size] = 100;
                        }
                        else
                        {
                            mat[a][curr - size] = 1;
                        }



                    }






                    else if (i != 0 && j != 0 && j < size - 1 && i < size - 1)//casse4
                    {
                        if (map[i][j + 1] == '#')
                        {
                            mat[a][curr + 1] = 100;
                        }
                        else
                        {
                            mat[a][curr + 1] = 1;
                        }
                        if (map[i + 1][j] == '#')
                        {
                            mat[a][curr + size] = 100;
                        }
                        else
                        {
                            mat[a][curr + size] = 1;
                        }

                        if (map[i - 1][j] == '#')
                        {
                            mat[a][curr - size] = 100;
                        }
                        else
                        {
                            mat[a][curr - size] = 1;
                        }

                        if (map[i][j - 1] == '#')
                        {
                            mat[a][curr - 1] = 100;
                        }
                        else
                        {
                            mat[a][curr - 1] = 1;
                        }
                    }






                    else if (i == 0 && j == size - 1)// case 5
                    {

                        if (map[i + 1][j] == '#')
                        {
                            mat[a][curr + size] = 100;
                        }
                        else
                        {
                            mat[a][curr + size] = 1;
                        }


                        if (map[i][j - 1] == '#')
                        {
                            mat[a][curr - 1] = 100;
                        }
                        else
                        {
                            mat[a][curr - 1] = 1;
                        }
                    }




                    else if (i == size - 1 && j == 0)// case 6
                    {
                        if (map[i][j + 1] == '#')
                        {
                            mat[a][curr + 1] = 100;
                        }
                        else
                        {
                            mat[a][curr + 1] = 1;
                        }


                        if (map[i - 1][j] == '#')
                        {
                            mat[a][curr - size] = 100;
                        }
                        else
                        {
                            mat[a][curr - size] = 1;
                        }


                    }



                    else if (i == size - 1 && j == size - 1)//case 7
                    {



                        if (map[i - 1][j] == '#')
                        {
                            mat[a][curr - size] = 100;
                        }
                        else
                        {
                            mat[a][curr - size] = 1;
                        }

                        if (map[i][j - 1] == '#')
                        {
                            mat[a][curr - 1] = 100;
                        }
                        else
                        {
                            mat[a][curr - 1] = 1;
                        }
                    }


                    else if (i == size - 1 && j != 0 && j < size - 1)//case 8
                    {
                        if (map[i][j + 1] == '#')
                        {
                            mat[a][curr + 1] = 100;
                        }
                        else
                        {
                            mat[a][curr + 1] = 1;
                        }


                        if (map[i - 1][j] == '#')
                        {
                            mat[a][curr - size] = 100;
                        }
                        else
                        {
                            mat[a][curr - size] = 1;
                        }

                        if (map[i][j - 1] == '#')
                        {
                            mat[a][curr - 1] = 100;
                        }
                        else
                        {
                            mat[a][curr - 1] = 1;
                        }
                    }


                    else if (i != 0 && j == size - 1 && i < size - 1)
                    {

                        if (map[i + 1][j] == '#')
                        {
                            mat[a][curr + size] = 100;
                        }
                        else
                        {
                            mat[a][curr + size] = 1;
                        }

                        if (map[i - 1][j] == '#')
                        {
                            mat[a][curr - size] = 100;
                        }
                        else
                        {
                            mat[a][curr - size] = 1;
                        }

                        if (map[i][j - 1] == '#')
                        {
                            mat[a][curr - 1] = 100;
                        }
                        else
                        {
                            mat[a][curr - 1] = 1;
                        }
                    }





                    a++;
                    curr++;

                }

            }

        }

    }
    class Edge {
    public:
        int u, v, weight;
    };

    void printMatrix()
    {
        for (int i = 0; i < size2; i++)
        {
            for (int j = 0; j < size2; j++)
            {
                cout << mat[i][j] << " ";
            }
            cout << endl << "(" << i + 1 << ")" << endl << endl;
        }
    }


    void printpath(int walid[], int v) {
        if (walid[v] == -1) {
            return;
        }
        printpath(walid, walid[v]);
        cout << v << "-->";
        path[cc] = v;
        cc++;
    }
    //v is denoted for vertex

    void floydWarshall(int V, int aghaaz, int ikhtatam) {
        int** fasla = new int* [400];
        int counterForFloyd;
        int i = 0;
        while (i < 400)
        {
            fasla[i] = new int[400];
            i++;
        }
        int** walid = new int* [400];
        int j = 0;
        while (j < 400)
        {
            walid[j] = new int[400];
            j++;
        }

        // Initializing distance matrix
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (i == j)
                {
                    fasla[i][j] = 0;
                    walid[i][j] = -1;
                }
                else if (mat[i][j] != 0)
                {
                    fasla[i][j] = mat[i][j];
                    walid[i][j] = i;
                }
                else
                {
                    fasla[i][j] = INT_MAX;              //giving max value making it unreacheable 
                    walid[i][j] = -1;
                }
            }
        }

        // Applying Floyd-Warshall algorithm
        for (int k = 0; k < V; k++)
        {
            for (int i = 0; i < V; i++)
            {
                for (int j = 0; j < V; j++)
                {
                    if (fasla[i][k] != INT_MAX && fasla[k][j] != INT_MAX && fasla[i][j] > fasla[i][k] + fasla[k][j])
                    {
                        fasla[i][j] = fasla[i][k] + fasla[k][j];
                        walid[i][j] = walid[k][j];
                    }
                }
            }
        }

        // Printing the shortest distance between start and end vertices
        if (fasla[aghaaz][ikhtatam] == INT_MAX)
        {
            cout << "No path exists between " << aghaaz << " and " << ikhtatam << endl;
        }
        else
        {
            cout << "Shortest distance between " << aghaaz << " and " << ikhtatam << ": " << fasla[aghaaz][ikhtatam] << endl;
            ww = fasla[aghaaz][ikhtatam];
            ww++;
            cc = aghaaz;
            path = new int[ww];
            path[0] = aghaaz;
        }

        printpath(walid[aghaaz], ikhtatam);
    }

    // to find the location of the crystal and return its position 

    int findlocas()
    {
        int temp = 0;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (map[i][j] != '*')           //we used big brain here plz bonus marks maam
                {
                    temp++;
                }
                else
                {
                    return temp;
                }
            }
        }

    }


    //

    int minDistance(int fasla[], bool sputSet[], int V)
    {
        int min = INT_MAX, min_index;

        for (int v = 0; v < V; v++)
        {
            if (sputSet[v] == false && fasla[v] <= min)
            {
                min = fasla[v], min_index = v;
            }
        }

        return min_index;
    }

    void printPath(int walid[], int j)
    {
        if (walid[j] == -1)
            return;

        printPath(walid, walid[j]);

        cout << j << "-->";
        path[cc] = j;
        cc++;
    }

    void dijkstra(int V, int source, int ikhtatam)
    {
        bool* sputSet = new bool[V];
        int* fasla = new int[V];
        int* walid = new int[V];

        int i = 0;
        while (i < V)
        {
            walid[source] = -1;
            fasla[i] = INT_MAX;
            sputSet[i] = false;
            i++;
        }

        fasla[source] = 0;

        for (int count = 0; count < V - 1; count++)
        {
            int u = minDistance(fasla, sputSet, V);

            sputSet[u] = true;

            for (int v = 0; v < V; v++)
                if (!sputSet[v] && mat[u][v] && fasla[u] + mat[u][v] < fasla[v])
                {
                    walid[v] = u;
                    fasla[v] = fasla[u] + mat[u][v];
                }
        }

        if (fasla[ikhtatam] != INT_MAX) {
            cout << endl << "Shortest distance from " << source << " to " << ikhtatam << ": " << fasla[ikhtatam] << "\n";
            cout << "Path: " << source << " ";
            ww = fasla[ikhtatam];
            ww++;
            cc = source;
            path = new int[ww];
            path[0] = source;
            printPath(walid, ikhtatam);
        }
        else {
            cout << "No path exists between " << source << " and " << ikhtatam << endl;
        }
    }

    int minKey(int chabi[], bool mstSet[], int V)
    {
        int min = INT_MAX, min_index;

        int v = 0;
        while (v < V)
        {
            if (mstSet[v] == false && chabi[v] < min)
            {
                min_index = v;
                min = chabi[v];
            }
            v++;
        }
        return min_index;
    }

    void printMST(int walid[], int** graph, int V)
    {
        cout << "Edge \tWeight\n";
        for (int i = 1; i < V; i++)
        {
            cout << walid[i] << " - " << i << " \t" << graph[i][walid[i]] << " \n";
        }
    }
    //recursion
    void primMST(int V)
    {
        int* walid = new int[V];
        bool* mstSet = new bool[V];
        int* chabi = new int[V];

        for (int i = 0; i < V; i++)
            chabi[i] = INT_MAX, mstSet[i] = false;

        chabi[0] = 0;
        walid[0] = -1;

        for (int count = 0; count < V - 1; count++)
        {
            int u = minKey(chabi, mstSet, V);

            mstSet[u] = true;

            int v = 0;
            while (v < V)
            {
                if (mat[u][v] && mstSet[v] == false && mat[u][v] < chabi[v])
                {
                    walid[v] = u;
                    chabi[v] = mat[u][v];
                }
                v++;
            }
        }

        printMST(walid, mat, V);
    }




    // Function to find the of a vertex in a set
    int find(int father[], int i) {
        if (father[i] == i) {
            return i;
        }
        return find(father, father[i]);
    }

    // Function to perform union of two sets
    void unionSet(int* father, int rank[], int x, int y) {
        int xroot = find(father, x);
        int yroot = find(father, y);
        if (rank[xroot] < rank[yroot]) {
            father[xroot] = yroot;
        }
        else if (rank[xroot] > rank[yroot]) {
            father[yroot] = xroot;
        }
        else {
            father[yroot] = xroot;
            rank[xroot]++;
        }
    }

    void bubbleSort(Edge arr[], int n) {
        for (int i = 0; i < n - 1; i++) {
            // Last i elements are already in place  
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j].weight > arr[j + 1].weight) {
                    // swap arr[j] and arr[j+1]
                    Edge temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }

    // Function to find minimum spanning tree using Kruskal's algorithm
    void Kruskal(int V) {
        Edge* edges = new Edge[40 * 40]; // Array to store edges
        int k = 0;
        for (int i = 0; i < V; i++) {
            for (int j = i + 1; j < V; j++) {
                if (mat[i][j] != 0) {
                    edges[k] = { i, j, mat[i][j] };
                    ++k;
                }
            }
        }

        bubbleSort(edges, k);
        int* father = new int[400];
        int* rank = new int[400];
        for (int i = 0; i < V; i++) {
            father[i] = i;
            rank[i] = 0;
        }
        Edge* tree = new Edge[400]; // Array to store minimum spanning tree edges
        int index = 0;
        for (int i = 0; i < k; i++) {
            int u = edges[i].u;
            int v = edges[i].v;
            int weight = edges[i].weight;
            int x = find(father, u);
            int y = find(father, v);
            if (y != x) {
                tree[index] = { u, v, weight };
                unionSet(father, rank, x, y);
                ++index;
            }
        }
        int temp = 0;
        cout << "Minimum Spanning Tree:" << endl;
        for (int i = 0; i < index; i++) {
            cout << "(" << tree[i].u << ", " << tree[i].v << ") - " << tree[i].weight << endl;
            temp++;
        }
        cout << temp << endl;
    }



};




int main() {

    int size = 20;

    Graph g(20);
    //g.GenerateRandomMap();
    //g.WriteMap("map.txt");
    g.ReadMap("result.txt");
    g.printMap();
    g.GenerateAdjency();

    //g.printMatrix();
    //int l = g.findlocas();
    g.play();

    //g.floydWarshall(400, 0, l);
   // g.dijkstra(400, 0, l);
   // g.primMST(400);
}


