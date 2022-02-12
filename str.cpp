#include "binarytree.hpp"

int main() {
    Tree<std::string> tree {"I", "did", "it"};

    tree.insert("Hello");
    tree.insert("Ola");
    tree.insert("Como estas?");
    tree.insert("How there?");
    tree.insert("Adeus!");
    tree.insert("Bye!");

    tree.print();

    if (tree.search("Hello")) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }

    std::cout << tree.size() << std::endl;

    tree.remove("Hello");
    std::cout << tree.size() << std::endl;
    tree.print();

    std::cin >> &tree;
    std::cin >> &tree;

    std::cout << &tree << std::endl;

    std::cout << tree.size() << std::endl;


    for (Tree<std::string>::Iterator it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << std::endl;
    }

    return 0;
}