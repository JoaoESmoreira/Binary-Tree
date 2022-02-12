#include "binarytree.hpp"

int main() {
    Tree<int> tree = {30, 20};

    //tree = {1 , 2, 10};

    tree.insert(5);
    tree.insert(8);
    tree.insert(2121);
    tree.insert(4444);
    tree.insert(34);
    tree.insert(35);
    tree.insert(1);

    tree.print();

    if (tree.search(34)) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }

    if (tree[34]) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }

    std::cout << tree.size() << std::endl;

    tree.remove(2121);
    tree.print();

    std::cin >> &tree;

    std::cout << &tree << std::endl;

    std::cout << tree.size() << std::endl;
    

    for (Tree<int>::Iterator it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *(it) << "\n";
    }

    for (auto value : tree) {
        std::cout << value << " ";
    }

    return 0;
}