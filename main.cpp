#include "LinkedList.h"
#include <iostream>

int main() {
    try {
        std::cout << "=== LinkedList Demonstration ===\n\n";

        LinkedList<int> list;
        list.push_tail(10);
        list.push_tail(20);
        list.push_tail(30);
        list.push_head(5);

        std::cout << "Forward order:  ";
        list.print_forward();

        std::cout << "Reverse order (operator<<): " << list << "\n\n";

        std::cout << "Random list (10 elements from 1 to 100):\n";
        LinkedList<int> random(10, 1, 100);
        std::cout << random << "\n\n";

        std::cout << "Prepending {100, 200} to the list:\n";
        LinkedList<int> extra;
        extra.push_tail(100);
        extra.push_tail(200);
        list.push_head(extra);
        std::cout << list << "\n\n";

        std::cout << "Removing all nodes with value 20:\n";
        list.delete_node(20);
        std::cout << list << "\n";

        std::cout << "\nAll operations completed successfully!\n";

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    // Чтобы консоль не закрывалась сразу (удобно при запуске .exe)
    system("pause");
    return 0;
}