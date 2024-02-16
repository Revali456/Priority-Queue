/// @file tests.cpp
/// @author Ahmik Ruben Nallamala
/// @date October 20, 2023

/// 
/// This is the test case file for prqueue.h and contains
/// the various tests I used to see the functionality of 
/// all the functions in the file from enqueue to dequeue
/// to begin and next.
///

// Catch 2.x - Single Include Framework Testing
#define CATCH_CONFIG_MAIN

#include "prqueue.h"
#include "catch.hpp"

using namespace std;

// This is a basic test case example with sections.
// Requires: <no oter functions>
TEST_CASE("Test 0: The Null Test") {
    // In this section we test Scenario 1.
    SECTION("Test 0: Empty Truths")
    {
        REQUIRE(true == true);
    }

    // In this section we test Scenario 2.
    SECTION("Test 0: Empty Falsehoods")
    {
        REQUIRE(false == false);
    }
}

TEST_CASE("ToStringTest - BasicTest", "[prqueue]") {
    prqueue<string> pq;

    pq.enqueue("Ben", 1);
    pq.enqueue("Jen", 2);
    pq.enqueue("Sven", 2);
    pq.enqueue("Gwen", 3);

    // Expected string representation
    string expected =
        "1 value: Ben\n"
        "2 value: Jen\n"
        "2 value: Sven\n"
        "3 value: Gwen\n";

    // Call the toString function
    string result = pq.toString();

    // Check if the result matches the expected string
    REQUIRE(result == expected);
}

TEST_CASE("Enqueue elements and maintain priority order") {
    prqueue<int> pq;

    // Enqueue 50 elements
    for (int i = 1; i <= 50; i++) {
        pq.enqueue(i, 51 - i);
    }

    SECTION("Check size after enqueue") {
        REQUIRE(pq.size() == 50);
    }

    SECTION("Check dequeue order") {
        for (int i = 50; i >= 1; i--) {
            REQUIRE(pq.dequeue() == i);
        }
    }
}

TEST_CASE("Enqueue with numbers on both sides of the tree") {
    prqueue<string> pq;

    // Enqueue elements with different priorities
    pq.enqueue("Alice", 2);
    pq.enqueue("Bob", 1);
    pq.enqueue("Charlie", 3);
    pq.enqueue("Dave", 0);
    pq.enqueue("Eve", 4);

    SECTION("Check size after enqueue") {
        REQUIRE(pq.size() == 5);
    }

    SECTION("Check elements in order") {
        REQUIRE(pq.dequeue() == "Dave");
        REQUIRE(pq.dequeue() == "Bob");
        REQUIRE(pq.dequeue() == "Alice");
        REQUIRE(pq.dequeue() == "Charlie");
        REQUIRE(pq.dequeue() == "Eve");
    }
}

TEST_CASE("Handle duplicates and linked lists") {
    prqueue<string> pq;

    // Enqueue 50 elements with duplicates

        pq.enqueue("Alice", 2);
        pq.enqueue("Bob", 1);
        pq.enqueue("Bob1", 1);
        pq.enqueue("Bob2", 1);
        pq.enqueue("POKE", 3);



    SECTION("Check size after enqueue with duplicates") {
        REQUIRE(pq.size() == 5);
    }

    SECTION("Check linked list") {

        REQUIRE(pq.dequeue() == "Bob");
        REQUIRE(pq.dequeue() == "Bob1");
        REQUIRE(pq.dequeue() == "Bob2");
        REQUIRE(pq.dequeue() == "Alice");
        REQUIRE(pq.dequeue() == "POKE");
        


    }



    
}

TEST_CASE("extra dups") {
    prqueue<string> pq;

    // Enqueue elements with duplicates and priorities
    pq.enqueue("0", 0);
    pq.enqueue("0", 0);
    pq.enqueue("b", 0);
    pq.enqueue("1", 1);
    pq.enqueue("1", 1);
    pq.enqueue("c", 1);
    pq.enqueue("2", 2);
    pq.enqueue("2", 2);
    pq.enqueue("d", 2);
    pq.enqueue("3", 3);
    pq.enqueue("3", 3);
    pq.enqueue("e", 3);
    pq.enqueue("4", 4);
    pq.enqueue("4", 4);
    pq.enqueue("f", 4);
    pq.enqueue("5", 5);
    pq.enqueue("5", 5);
    pq.enqueue("g", 5);
    pq.enqueue("6", 6);
    pq.enqueue("6", 6);
    pq.enqueue("h", 6);
    pq.enqueue("7", 7);
    pq.enqueue("7", 7);
    pq.enqueue("i", 7);
    pq.enqueue("8", 8);
    pq.enqueue("8", 8);
    pq.enqueue("j", 8);
    pq.enqueue("9", 9);
    pq.enqueue("9", 9);
    pq.enqueue("k", 9);
    pq.enqueue("0", 10);
    pq.enqueue("1", 9);
    pq.enqueue("2", 8);
    pq.enqueue("3", 7);
    pq.enqueue("4", 6);
    pq.enqueue("5", 5);
    pq.enqueue("6", 4);
    pq.enqueue("7", 3);
    pq.enqueue("8", 2);
    pq.enqueue("9", 1);
    pq.enqueue("0", 9);
    pq.enqueue("1", 4);
    pq.enqueue("2", 8);
    pq.enqueue("3", 8);
    pq.enqueue("4", 10);
    pq.enqueue("5", 2);
    pq.enqueue("6", 4);
    pq.enqueue("7", 8);

    SECTION("Check size after enqueue with duplicates") {
        REQUIRE(pq.size() == 48);
    }

    SECTION("Check linked list") {
        REQUIRE(pq.dequeue() == "0");
        REQUIRE(pq.dequeue() == "0");
        REQUIRE(pq.dequeue() == "b");
        REQUIRE(pq.dequeue() == "1");
        REQUIRE(pq.dequeue() == "1");
        REQUIRE(pq.dequeue() == "c");
        REQUIRE(pq.dequeue() == "2");
        REQUIRE(pq.dequeue() == "2");
        REQUIRE(pq.dequeue() == "d");
        REQUIRE(pq.dequeue() == "3");
        REQUIRE(pq.dequeue() == "3");
        REQUIRE(pq.dequeue() == "e");
        REQUIRE(pq.dequeue() == "4");
        REQUIRE(pq.dequeue() == "4");
        REQUIRE(pq.dequeue() == "f");
        REQUIRE(pq.dequeue() == "5");
        REQUIRE(pq.dequeue() == "5");
        REQUIRE(pq.dequeue() == "g");
        REQUIRE(pq.dequeue() == "6");
        REQUIRE(pq.dequeue() == "6");
        REQUIRE(pq.dequeue() == "h");
        REQUIRE(pq.dequeue() == "7");
        REQUIRE(pq.dequeue() == "7");
        REQUIRE(pq.dequeue() == "i");
        REQUIRE(pq.dequeue() == "8");
        REQUIRE(pq.dequeue() == "8");
        REQUIRE(pq.dequeue() == "j");
        REQUIRE(pq.dequeue() == "9");
        REQUIRE(pq.dequeue() == "9");
        REQUIRE(pq.dequeue() == "k");
        REQUIRE(pq.dequeue() == "0");
        REQUIRE(pq.dequeue() == "1");
        REQUIRE(pq.dequeue() == "2");
        REQUIRE(pq.dequeue() == "3");
        REQUIRE(pq.dequeue() == "4");
        REQUIRE(pq.dequeue() == "5");
        REQUIRE(pq.dequeue() == "6");
        REQUIRE(pq.dequeue() == "7");
        REQUIRE(pq.dequeue() == "8");
    }
}


TEST_CASE("Handle dequeue from an empty priority queue") {
    prqueue<double> pq;

    SECTION("Dequeue from an empty queue should throw an exception") {
        REQUIRE_THROWS_AS(pq.dequeue(), std::runtime_error);
    }
}

TEST_CASE("Test prqueue dequeue") {
    prqueue<int> priorityQueue;

    // Enqueue some elements
    priorityQueue.enqueue(5, 2);  // Priority 2
    priorityQueue.enqueue(10, 1); // Priority 1
    priorityQueue.enqueue(15, 3); // Priority 3

    SECTION("Dequeue elements and check their values") {
        int value1 = priorityQueue.dequeue();
        REQUIRE(value1 == 10);  // Should dequeue the element with priority 1

        int value2 = priorityQueue.dequeue();
        REQUIRE(value2 == 5);   // Should dequeue the element with priority 2

        int value3 = priorityQueue.dequeue();
        REQUIRE(value3 == 15);  // Should dequeue the element with priority 3
    }

}

TEST_CASE("Duplicate elements with linked list") {
    prqueue<string> pq;

    SECTION("Enqueue duplicates with linked list") {
        for (int i = 0; i < 5; i++) {
            pq.enqueue("Duplicate", 2);
        }

        pq.enqueue("Unique1", 1);
        pq.enqueue("Unique2", 3);

        // Check all enqueues
        REQUIRE(pq.dequeue() == "Unique1");
        REQUIRE(pq.dequeue() == "Duplicate");
        REQUIRE(pq.dequeue() == "Duplicate");
        REQUIRE(pq.dequeue() == "Duplicate");
        REQUIRE(pq.dequeue() == "Duplicate");
        REQUIRE(pq.dequeue() == "Duplicate");
        REQUIRE(pq.dequeue() == "Unique2");
    }

    SECTION("Enqueue unique elements") {
        pq.enqueue("Unique1", 1);
        pq.enqueue("Unique0", 0);
        pq.enqueue("Unique01", 0);
        pq.enqueue("Unique02", 0);
        pq.enqueue("Unique2", 2);
        pq.enqueue("Unique22", 2);
        pq.enqueue("Unique23", 2);
        pq.enqueue("Unique24", 2);
        pq.enqueue("Unique25", 2);
        pq.enqueue("Unique3", 3);
        pq.enqueue("Unique4", 4);
        pq.enqueue("Unique5", 5);
        pq.enqueue("Unique32", 3);
        pq.enqueue("Unique33", 3);
        pq.enqueue("Unique34", 3);

        // Check all enqueues
        REQUIRE(pq.dequeue() == "Unique0");
        REQUIRE(pq.dequeue() == "Unique01");
        REQUIRE(pq.dequeue() == "Unique02");
        REQUIRE(pq.dequeue() == "Unique1");
        REQUIRE(pq.dequeue() == "Unique2");
        REQUIRE(pq.dequeue() == "Unique22");
        REQUIRE(pq.dequeue() == "Unique23");
        REQUIRE(pq.dequeue() == "Unique24");
        REQUIRE(pq.dequeue() == "Unique25");
        REQUIRE(pq.dequeue() == "Unique3");
        REQUIRE(pq.dequeue() == "Unique32");
        REQUIRE(pq.dequeue() == "Unique33");
        REQUIRE(pq.dequeue() == "Unique34");
    }
}

TEST_CASE("Test begin() function when the tree is empty") {
    prqueue<int> pq;
    pq.begin();

    SECTION("Check if the internal state is nullptr when the tree is empty") {
        int value;
        int priority;
        REQUIRE(pq.next(value, priority) == false);
    }
}

TEST_CASE("Test begin() function when the tree is not empty") {
    prqueue<int> pq;
    pq.enqueue(5, 10);
    pq.enqueue(7, 8);
    pq.enqueue(3, 12);
    pq.begin();
}

TEST_CASE("Test next() function when the internal state is at the end") {
    prqueue<int> pq;
    pq.begin();

    SECTION("Check that next() returns false when the internal state is null") {
        int value;
        int priority;
        REQUIRE_FALSE(pq.next(value, priority));
    }
}

TEST_CASE("Test next() function when there are nodes to traverse") {
    prqueue<int> pq;
    pq.enqueue(5, 10);
    pq.enqueue(7, 8);
    pq.enqueue(3, 12);
    pq.begin();

    SECTION("Check if next() returns true and retrieves the correct value and priority") {
        int value;
        int priority;

        while (pq.next(value, priority)){
            cout << value << " " << priority << endl;
        }
        cout << value << " " << priority << endl;
        REQUIRE(pq.next(value, priority));
        REQUIRE(value == 7);
        REQUIRE(priority == 8);

        REQUIRE(pq.next(value, priority));
        REQUIRE(value == 5);
        REQUIRE(priority == 10);

        REQUIRE(pq.next(value, priority));
        REQUIRE(value == 3);
        REQUIRE(priority == 12);

        REQUIRE_FALSE(pq.next(value, priority));
    }

}
TEST_CASE("Equality operator returns true for identical priority queues") {
    prqueue<string> pq1;
    prqueue<string> pq2;

    // Enqueue elements to pq1
    pq1.enqueue("10", 1);
    pq1.enqueue("20", 2);
    pq1.enqueue("30", 3);


    // Enqueue the same elements to pq2
    pq2.enqueue("10", 1);
    pq2.enqueue("20", 2);
    pq2.enqueue("30", 3);


    REQUIRE(pq1 == pq2);
}

TEST_CASE("Equality operator returns false for different priority queues") {
    prqueue<string> pq1;
    prqueue<string> pq2;


    // Enqueue elements to pq1
    pq1.enqueue("10", 1);
    pq1.enqueue("20", 2);
    pq1.enqueue("30", 3);

    // Enqueue different elements to pq2
    pq2.enqueue("5", 1);
    pq2.enqueue("15", 2);
    pq2.enqueue("25", 3);

    REQUIRE_FALSE(pq1 == pq2);
}

TEST_CASE("Equality operator returns false for priority queues with different sizes") {
    prqueue<string> pq1;
    prqueue<string> pq2;


    // Enqueue elements to pq1
    pq1.enqueue("10", 1);
    pq1.enqueue("20", 2);

    // Enqueue the same elements to pq2
    pq2.enqueue("10", 1);
    pq2.enqueue("20", 2);
    pq2.enqueue("30", 3);

    REQUIRE_FALSE(pq1 == pq2);
}




