#include <iostream>
#include <string>
#include <sstream>
#include <memory>

template <typename T>
class Node{
public:
    int counter;
    T data;
    std::shared_ptr<Node<T>> left {nullptr};
    std::shared_ptr<Node<T>> right {nullptr};
    std::weak_ptr<Node<T>> parent;
    Node(){
        counter = 0;
    }
};

template <typename T>
class BSTree {
public:

    std::shared_ptr<Node<T>> head {nullptr};

    BSTree(std::string &input) {
        std::istringstream s(input);
        T elem;
        while (s >> elem) {
            searchAndInsert(elem, head);
        }
        setParent(head);
    }

    ~BSTree() = default;

    void searchAndInsert(T elem, std::shared_ptr<Node<T>>& ptr) {
        if (!ptr) {
            ptr = std::make_shared<Node<T>>();
            ptr->data = elem;
            ptr->counter = 1;
        } else if (elem < ptr->data) {
            searchAndInsert(elem, ptr->left);
        } else if (elem > ptr->data) {
            searchAndInsert(elem, ptr->right);
        } else {
            ptr->counter++;
        }
    }

    void setParent(std::shared_ptr<Node<T>>& ptr){
        if(ptr){
            if(ptr->left){
                ptr->left->parent = ptr;
                setParent(ptr->left);
            }
            if (ptr->right){
                ptr->right->parent = ptr;
                setParent(ptr->right);
            }
        }
    }

    void searchAndDelete(T elem, std::shared_ptr<Node<T>>& ptr){
        if(ptr) {
            if(ptr == head && !ptr->left && !ptr->right){
                head = nullptr;
                return;
            }
            if (elem < ptr->data) {
                searchAndDelete(elem, ptr->left);
            } else if (elem > ptr->data) {
                searchAndDelete(elem, ptr->right);
            } else if (elem == ptr->data) {
                if (ptr->counter > 1) {
                    ptr->counter -= 1;
                    return;
                } else {
                    if (!ptr->left && !ptr->right) {//если нет потомков
                        std::shared_ptr<Node<T>> father = ptr->parent.lock();
                        ptr->parent.lock()->left = nullptr;
                        if(father->left){
                            if(father->left->data == ptr->data){
                                father->left = nullptr;
                            }
                        }
                        if(father->right){
                            if(father->right->data == ptr->data){
                                father->right = nullptr;
                            }
                        }
                        return;
                    } else if (ptr->right) {
                        T leftSon = findMin(ptr->right, ptr->counter);
                        searchAndDelete(leftSon, head);
                        ptr->data = leftSon;
                        return;
                    } else if (ptr->left) {
                        T rightSon = findMax(ptr->left, ptr->counter);
                        searchAndDelete(rightSon, head);
                        ptr->data = rightSon;
                        return;
                    }
                }
            }
        }else{
            std::cout << "There is no element " << elem << " in tree.\n";
        }
    }

    T findMin(std::shared_ptr<Node<T>> p, int& ct){
        std::shared_ptr<Node<T>> temp = std::make_shared<Node<T>>();
        temp = p;
        while(temp->left){
            temp = temp->left;
        }
        ct = temp->counter;
        return temp->data;
    }

    T findMax(std::shared_ptr<Node<T>> p, int& ct){
        std::shared_ptr<Node<T>> temp = std::make_shared<Node<T>>();
        temp = p;
        while(temp->right){
            temp = temp->right;
        }
        ct = temp->counter;
        return temp->data;
    }

    void klp(std::shared_ptr<Node<T>> tmp) {
        if (tmp) {
            std::cout << tmp->data << ' ';
            if (tmp->left) klp(tmp->left);
            if (tmp->right) klp(tmp->right);
        }
    }

    void printBST(std::shared_ptr<Node<T>> bt, std::string str=""){
        if(!bt){
            return;
        }
        std::string cpyStr = str;
        std::cout << bt->data << '\n';
        if(bt->right){
            std::cout << str;
        }
        if(!bt->left && bt->right){
            std::cout << "\x1b[31m└▶ \x1b[0m";
        }
        if(bt->left && bt->right){
            std::cout << "\x1b[31m├▶ \x1b[0m";
        }
        if(bt->left){
            printBST(bt->right, str.append("\x1b[34m│ \x1b[0m"));
        }else{
            printBST(bt->right, str.append(" "));
        }
        if(bt->left){
            std::cout << cpyStr;
        }
        if(bt->left){
            std::cout << "\x1b[34m└▶ \x1b[m";
        }
        printBST(bt->left, cpyStr.append(" "));
    }

};

bool digitChecker(std::string& s){
    int len = s.length();
    int counter = 0;
    for(int i = 0; i < len; i++){
        if(isdigit(s[i]) || s[i] == ' '){
            counter++;
        }else{
            break;
        }
    }
    return counter==len;
}

bool charChecker(std::string& s){
    int len = s.length();
    int counter = 0;
    for(int i = 0; i < len; i++){
        if(isalpha(s[i]) || s[i] == ' '){
            counter++;
        }else{
            break;
        }
    }
    return counter==len;
}

int main() {
    std::string input;
    std::string elemsToDelete;
    getline(std::cin, input);
    getline(std::cin, elemsToDelete);
    if(isdigit(input[0])){
        if(digitChecker(input) && digitChecker(elemsToDelete)){
            BSTree<int> BTree(input);
            std::cout << "Before deleting:\n";
            //BTree.klp(BTree.head);
            BTree.printBST(BTree.head);
            std::cout << '\n';
            std::istringstream s(elemsToDelete);
            int elem;
            while (s >> elem) {
                BTree.searchAndDelete(elem, BTree.head);
            }
            std::cout << "After deleting:\n";
            //BTree.klp(BTree.head);
            BTree.printBST(BTree.head);
            std::cout << '\n';
        }else{
            std::cout << "Incorrect input!\n";
            return 0;
        }
    }else if(isalpha(input[0])){
        if(charChecker(input) && charChecker(elemsToDelete)){
            BSTree<char> BTree(input);
            std::cout << "Before deleting:\n";
            BTree.klp(BTree.head);
            std::cout << '\n';
            std::istringstream s(elemsToDelete);
            char elem;
            while (s >> elem) {
                BTree.searchAndDelete(elem, BTree.head);
            }
            std::cout << "After deleting:\n";
            BTree.klp(BTree.head);
            std::cout << '\n';
        }else{
            std::cout << "Incorrect input!\n";
            return 0;
        }
    }else{
        std::cout << "Incorrect input!\n";
        return 0;
    }
    std::cout << "Finished successful!\n";
    return 0;
}