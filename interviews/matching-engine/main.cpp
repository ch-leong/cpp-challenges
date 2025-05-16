#include <functional>
#include <iterator>
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <unordered_set>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

namespace {
    std::vector<std::string> tokenizeString(std::string const& line) {
        std::vector<std::string> vec;
        std::stringstream ss(line);
        std::string token;
        while (std::getline(ss, token, ' ')) {
            vec.push_back(token);
        }
        return vec;
    }
}

struct Order {
/*
    Order()
        : m_Operation{'B'}
        , m_OrderType{'G'}
        , m_Price{0}
        , m_Quantity{0}
        , m_OrderID{}
    {}

    Order(char operation, char orderType, int price, int quantity, std::string const& orderID)
        : m_Operation{operation}
        , m_OrderType{orderType}
        , m_Price{price}
        , m_Quantity{quantity}
        , m_OrderID{orderID}
    {}

    Order(Order const& order)
        : m_Operation{order.m_Operation}
        , m_OrderType{order.m_OrderType}
        , m_Price{order.m_Price}
        , m_Quantity{order.m_Quantity}
        , m_OrderID{order.m_OrderID}
    {}

    Order(Order&& order)
        : m_Operation{'B'}
        , m_OrderType{'G'}
        , m_Price{0}
        , m_Quantity{0}
        , m_OrderID{}
    {
        std::swap(m_Operation, order.m_Operation);
        std::swap(m_OrderType, order.m_OrderType);
        std::swap(m_Price, order.m_Price);
        std::swap(m_Quantity, order.m_Quantity);
        std::swap(m_OrderID, order.m_OrderID);
    }

    Order& operator=(Order const& order) {
        m_Operation = order.m_Operation;
        m_OrderType = order.m_OrderType;
        m_Price = order.m_Price;
        m_Quantity = order.m_Quantity;
        m_OrderID = order.m_OrderID;
        return *this;
    }

    Order& operator=(Order&& order) {
        std::swap(m_Operation, order.m_Operation);
        std::swap(m_OrderType, order.m_OrderType);
        std::swap(m_Price, order.m_Price);
        std::swap(m_Quantity, order.m_Quantity);
        std::swap(m_OrderID, order.m_OrderID);
        return *this;
    }
    
    ~Order()
    {}
*/

    char m_Operation; // 'B'UY / 'S'ELL only the first character
    char m_OrderType; // 'G'FD / 'I'OC only the first character
    int m_Price;
    int m_Quantity;
    std::string m_OrderID;
};

class MatchingEngine {
    std::map<int, std::list<Order>, std::greater<int>> m_BuyOrders; // Sorted by highest price to lowest, then price-time priority.
    std::map<int, std::list<Order>> m_SellOrders; // Sorted by lowest price to highest, then price-time priority.
    std::unordered_map<std::string, char> m_OrderIDs; // Store ID and order type for quicker lookup.

public:
    void AddBuyOrder(Order const& buyOrder) {
        m_BuyOrders[buyOrder.m_Price].push_back(buyOrder); //std::cout << "Added " << buyOrder.m_Operation << "\n";
        AddOrderID(buyOrder.m_OrderID, buyOrder.m_Operation);
    }
    
    void AddSellOrder(Order const& sellOrder) {
        m_SellOrders[sellOrder.m_Price].push_back(sellOrder); //std::cout << "Added " << sellOrder.m_Operation << "\n";
        AddOrderID(sellOrder.m_OrderID, sellOrder.m_Operation);
    }
    
    void AddOrderID(std::string const& orderID, char operation) {
        m_OrderIDs[orderID] = operation;
    }
    
    bool OrderIDExist(std::string const& orderID) {
        return m_OrderIDs.find(orderID) != m_OrderIDs.end();
    }

    void RemoveOrder(std::string const& orderID) {
        char operation = m_OrderIDs[orderID]; // Using m_OrderIDs's second to selection operation.
        if (operation == 'B') {
            for (auto eachPriceGroup = m_BuyOrders.begin(); eachPriceGroup != m_BuyOrders.end(); ++eachPriceGroup) {
                for (auto eachBuyOrder = eachPriceGroup->second.begin(); eachBuyOrder != eachPriceGroup->second.end(); ++eachBuyOrder) {
                    if (eachBuyOrder->m_OrderID == orderID) {
                        m_OrderIDs.erase(orderID);
                        eachPriceGroup->second.erase(eachBuyOrder);
                        if (eachPriceGroup->second.empty())
                            m_BuyOrders.erase(eachPriceGroup);
                        return; //std::cout << "found " << orderID << " in buy orders\n";
                    }
                }
            }
        } else if (operation == 'S') {
            for (auto eachPriceGroup = m_SellOrders.begin(); eachPriceGroup != m_SellOrders.end(); ++eachPriceGroup) {
                for (auto eachSellOrder = eachPriceGroup->second.begin(); eachSellOrder != eachPriceGroup->second.end(); ++eachSellOrder) {
                    if (eachSellOrder->m_OrderID == orderID) {
                        m_OrderIDs.erase(orderID);
                        eachPriceGroup->second.erase(eachSellOrder);
                        if (eachPriceGroup->second.empty())
                            m_SellOrders.erase(eachPriceGroup);
                        return; //std::cout << "found " << orderID;
                    }
                }
            }
        }
    }

    void ModifyOrder(Order const& order) {
        RemoveOrder(order.m_OrderID);
        if (order.m_Operation == 'B') // BUY
            AddBuyOrder(order);
        else if (order.m_Operation == 'S') // SELL
            AddSellOrder(order);
    }

    void Match() { // Only need to match buy orders.
        for (auto eachPriceGroup = m_BuyOrders.begin(); eachPriceGroup != m_BuyOrders.end(); ++eachPriceGroup) {
            for (auto eachBuyOrder = eachPriceGroup->second.begin(); eachBuyOrder != eachPriceGroup->second.end(); ++eachBuyOrder) {
                MatchSellOrders(*eachBuyOrder);
                /*
                if (eachBuyOrder->m_Quantity == 0) {
                    m_OrderIDs.erase(eachBuyOrder->m_OrderID);
                    eachBuyOrder = eachPriceGroup->second.erase(eachBuyOrder);
                } else {
                    ++eachBuyOrder;
                }
                */
            }
            /*
            if (eachPriceGroup->second.empty()) {
                eachPriceGroup = m_BuyOrders.erase(eachPriceGroup);
            } else {
                ++eachPriceGroup;
            }
            */
        }
        Clean();
    
        /*
        for (auto eachPriceGroup = m_SellOrders.begin(); eachPriceGroup != m_SellOrders.end(); ++eachPriceGroup) {
            for (auto eachSellOrder = eachPriceGroup->second.begin(); eachSellOrder != eachPriceGroup->second.end(); ++eachSellOrder) {
                MatchBuyOrders(*eachSellOrder);
            }
        }
        Clean();
        */
    }

    void MatchBuyOrders(Order& sellOrder) { //std::cout << "Matching " << sellOrder.m_OrderID << "\n";
        for (auto eachPriceGroup = m_BuyOrders.begin(); eachPriceGroup != m_BuyOrders.end(); ++eachPriceGroup) {
            for (auto eachBuyOrder = eachPriceGroup->second.begin(); eachBuyOrder != eachPriceGroup->second.end(); ++eachBuyOrder) {
                if (eachBuyOrder->m_Quantity > 0 && eachBuyOrder->m_Price >= sellOrder.m_Price) { // Price cross.
                    int transactionQuantity = std::min(sellOrder.m_Quantity, eachBuyOrder->m_Quantity); //std::cout << "MatchBuyOrders: Matched " << eachBuyOrder->m_OrderID << "\n";
                    std::string tradeString = "TRADE "
                        + eachBuyOrder->m_OrderID + " " + std::to_string(eachBuyOrder->m_Price) + " " + std::to_string(transactionQuantity) + " "
                        + sellOrder.m_OrderID + " " + std::to_string(sellOrder.m_Price) + " " + std::to_string(transactionQuantity) + "\n";
                    std::cout << tradeString;
                    eachBuyOrder->m_Quantity -= transactionQuantity;// std::cout << "transactionQuantity " << transactionQuantity << "\n";
                    sellOrder.m_Quantity -= transactionQuantity;
                    
                    /*
                    if (eachBuyOrder->m_Quantity == 0) {
                        m_OrderIDs.erase(eachBuyOrder->m_OrderID);
                        eachBuyOrder = eachPriceGroup->second.erase(eachBuyOrder);
                    } else {
                        ++eachBuyOrder;
                    }
                    */
                    if (sellOrder.m_Quantity == 0) { // sell finished.
                        return;
                    }
                }
            }
            /*
            if (eachPriceGroup->second.empty()) {
                eachPriceGroup = m_BuyOrders.erase(eachPriceGroup);
            } else {
                ++eachPriceGroup;
            }
            if (sellOrder.m_Quantity == 0) { // sell finished.
                return;
            }
            */
        }
    }

    void MatchSellOrders(Order& buyOrder) { //std::cout << "MatchSellOrders: Matching " << buyOrder.m_OrderID << "\n";
        for (auto eachPriceGroup = m_SellOrders.begin(); eachPriceGroup != m_SellOrders.end(); ++eachPriceGroup) {
            for (auto eachSellOrder = eachPriceGroup->second.begin(); eachSellOrder != eachPriceGroup->second.end(); ++eachSellOrder) {
                if (eachSellOrder->m_Quantity > 0 && eachSellOrder->m_Price <= buyOrder.m_Price) { // Price cross.
                    int transactionQuantity = std::min(buyOrder.m_Quantity, eachSellOrder->m_Quantity); //std::cout << "MatchSellOrders: Matched " << eachSellOrder->m_OrderID << "\n";
                    std::string tradeString = "TRADE "
                        + buyOrder.m_OrderID + " " + std::to_string(buyOrder.m_Price) + " " + std::to_string(transactionQuantity) + " "
                        + eachSellOrder->m_OrderID + " " + std::to_string(eachSellOrder->m_Price) + " " + std::to_string(transactionQuantity) + "\n";
                    std::cout << tradeString;
                    eachSellOrder->m_Quantity -= transactionQuantity;// std::cout << "transactionQuantity " << transactionQuantity << "\n";
                    buyOrder.m_Quantity -= transactionQuantity;
                    
                    /*
                    if (eachSellOrder->m_Quantity == 0) {
                        m_OrderIDs.erase(eachSellOrder->m_OrderID);
                        eachSellOrder = eachPriceGroup->second.erase(eachSellOrder);
                    } else {
                        ++eachSellOrder;
                    }
                    */
                    if (buyOrder.m_Quantity == 0) { // buy finished.
                        return;
                    }
                }
            }
            /*
            if (eachPriceGroup->second.empty()) {
                eachPriceGroup = m_BuyOrders.erase(eachPriceGroup);
            } else {
                ++eachPriceGroup;
            }
            if (buyOrder.m_Quantity == 0) { // buy finished.
                return;
            }
            */
        }
    }
    
    void Clean() {
        for (auto eachPriceGroup = m_BuyOrders.begin(); eachPriceGroup != m_BuyOrders.end();) {
            for (auto eachBuyOrder = eachPriceGroup->second.begin(); eachBuyOrder != eachPriceGroup->second.end();) {
                if (eachBuyOrder->m_Quantity == 0) { //std::cout << "Removing " << eachBuyOrder->m_OrderID << " from buy orders\n";
                    m_OrderIDs.erase(eachBuyOrder->m_OrderID);
                    eachBuyOrder = eachPriceGroup->second.erase(eachBuyOrder); // Quantity empty means order done.
                } else {
                    ++eachBuyOrder;
                }
            }
            if (eachPriceGroup->second.size() == 0) {
                eachPriceGroup = m_BuyOrders.erase(eachPriceGroup);
            } else {
                ++eachPriceGroup;
            }
        }

        for (auto eachPriceGroup = m_SellOrders.begin(); eachPriceGroup != m_SellOrders.end();) {
            for (auto eachSellOrder = eachPriceGroup->second.begin(); eachSellOrder != eachPriceGroup->second.end();) { //std::cout << eachSellOrder->m_OrderID << " has " << eachSellOrder->m_Quantity << "\n";
                if (eachSellOrder->m_Quantity == 0) { //std::cout << eachSellOrder->m_OrderID;
                    m_OrderIDs.erase(eachSellOrder->m_OrderID);
                    eachSellOrder = eachPriceGroup->second.erase(eachSellOrder); // Quantity empty means order done.
                } else {
                    ++eachSellOrder;
                }
            }
            if (eachPriceGroup->second.size() == 0) {
                eachPriceGroup = m_SellOrders.erase(eachPriceGroup);
            } else {
                ++eachPriceGroup;
            }
        }
    }

    void Print() const {
        std::cout << "SELL:\n";
        for (auto eachPriceGroup = m_SellOrders.rbegin(); eachPriceGroup != m_SellOrders.rend(); ++eachPriceGroup) { // m_SellOrders is lowest to highest. so reverse.
            std::cout << eachPriceGroup->first << " ";
            int totalQuantity = 0;
            for (auto eachOrder = eachPriceGroup->second.begin(); eachOrder != eachPriceGroup->second.end(); ++eachOrder) {
                totalQuantity += eachOrder->m_Quantity;
            }
            std::cout << totalQuantity << "\n";
        }

        std::cout << "BUY:\n";
        for (auto eachPriceGroup = m_BuyOrders.begin(); eachPriceGroup != m_BuyOrders.end(); ++eachPriceGroup) { // Highest to lowest.
            std::cout << eachPriceGroup->first << " ";
            int totalQuantity = 0;
            for (auto eachOrder = eachPriceGroup->second.begin(); eachOrder != eachPriceGroup->second.end(); ++eachOrder) {
                totalQuantity += eachOrder->m_Quantity;
            }
            std::cout << totalQuantity << "\n";
        }
    }
    
    void DebugPrint() const { //std::cout << "s: ";
        for (auto eachPriceGroup = m_SellOrders.begin(); eachPriceGroup != m_SellOrders.end(); ++eachPriceGroup) {
            for (auto eachOrder = eachPriceGroup->second.begin(); eachOrder != eachPriceGroup->second.end(); ++eachOrder) {
                std::cout << eachOrder->m_OrderID[eachOrder->m_OrderID.size() - 2] << eachOrder->m_OrderID.back() << " " << eachOrder->m_Price << " " << eachOrder->m_Quantity << " ";
            }
        }
        std::cout << " | ";
        for (auto eachPriceGroup = m_BuyOrders.begin(); eachPriceGroup != m_BuyOrders.end(); ++eachPriceGroup) {
            for (auto eachOrder = eachPriceGroup->second.begin(); eachOrder != eachPriceGroup->second.end(); ++eachOrder) {
                std::cout << eachOrder->m_OrderID[eachOrder->m_OrderID.size() - 2] << eachOrder->m_OrderID.back() << " " << eachOrder->m_Price << " " << eachOrder->m_Quantity << " ";
            }
        }
        std::cout << "\n";
    }
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    MatchingEngine engine;
    const std::unordered_set<std::string> supportedOperations = { "BUY", "SELL", "CANCEL", "MODIFY", "PRINT" };
    const std::unordered_set<std::string> supportedOrderType = { "IOC", "GFD" };

    std::string line;
    while(std::getline(std::cin, line)) {
        std::vector<std::string> columns = tokenizeString(line); //std::cout << line << "-------------- ";
        //continue; // uncomment to check inputs.
        if (supportedOperations.find(columns[0]) == supportedOperations.end())
            continue;

        char operation = columns[0][0];
        if (operation == 'C') { // CANCEL
            //std::transform(columns[1].begin(), columns[1].end(), columns[1].begin(), [](char c){ return std::tolower(c); }); // cannot use
            if (columns[1].empty() || !engine.OrderIDExist(columns[1])) { // order id
                continue;
            }
            engine.RemoveOrder(columns[1]); // order id.
            //engine.DebugPrint();
            continue;
        } else if (operation == 'P') { // PRINT
            engine.Print(); //std::cout << "\n";
            continue;
        } else if (operation == 'M') { // MODIFY
            //std::transform(columns[1].begin(), columns[1].end(), columns[1].begin(), [](char c){ return std::tolower(c); }); // cannot use
            if (columns[1].empty() || !engine.OrderIDExist(columns[1])) { // order id
                continue;
            }
            // columns are in the order: operation, order id, new operation, new price, new quantity.
            Order order{ columns[2][0], 'G', static_cast<int>(std::stol(columns[3])), static_cast<int>(std::stol(columns[4])), columns[1] }; // operation, order type (default to GFD), price, quantity, order id.
            if (order.m_Price <= 0 || order.m_Quantity <= 0) {
                continue;
            }
            engine.ModifyOrder(order);
            engine.Match();
            //engine.DebugPrint();
            continue;
        }
        
        if (supportedOrderType.find(columns[1]) == supportedOrderType.end())
            continue;
        //std::transform(columns[4].begin(), columns[4].end(), columns[4].begin(), [](char c){ return std::tolower(c); }); // cannot use
        Order order{ operation, columns[1][0], static_cast<int>(std::stol(columns[2])), static_cast<int>(std::stol(columns[3])), columns[4] }; // operation, order type, price, quantity, order id.
        //std::cout << order.m_OrderID << " starting\n";
        if (order.m_Price <= 0 || order.m_Quantity <= 0 || order.m_OrderID.empty() || engine.OrderIDExist(order.m_OrderID)) { //std::cout << "\n";
            continue;
        }
        if (order.m_Operation == 'B') { // BUY
            if (order.m_OrderType == 'I') { // IOC
                engine.MatchSellOrders(order);
                engine.Clean();
                //engine.AddOrderID(order.m_OrderID, order.m_Operation);
            } else {
                engine.AddBuyOrder(order);
                engine.Match();
            }
        } else if (order.m_Operation == 'S') { // SELL
            if (order.m_OrderType == 'I') { // IOC
                engine.MatchBuyOrders(order);
                engine.Clean();
                //engine.AddOrderID(order.m_OrderID, order.m_Operation);
            } else {
                engine.AddSellOrder(order);
                engine.Match();
            }
        } //std::cout << order.m_OrderID << " done\n\n";
        //engine.DebugPrint();
    }
    return 0;
}


/*
failed test case debugging:

test case 3
BUY GFD 1000 10 order1
SELL GFD 900 20 order2
PRINT

test case 6
BUY GFD 1000 10 order1
SELL IOC 900 20 order2

test case 7
BUY GFD 1000 10 order1
SELL GFD 1010 20 order2
SELL GFD 2000 30 order3
PRINT

test case 12
BUY GFD 1000 10 ORDER1
PRINT
MODIFY ORDER1 SELL 1000 10

test case 13
BUY GFD 1000 10 ORDER1
BUY GFD 1100 20 ORDER2
BUY GFD 900 30 ORDER3
BUY GFD 1100 30 ORDER4
BUY GFD 1100 40 ORDER5
SELL GFD 1100 100 ORDER6

test case 15
BUY GFD 1000 10 ORDER1
BUY GFD 1100 20 ORDER2
SELL GFD 900 100 ORDER6

test case 16
BUY GFD 1003 30 order3
BUY GFD 1002 20 order2
BUY GFD 1003 30 order3_1
BUY GFD 1001 10 order1
BUY GFD 1003 30 order3_2
BUY GFD 1002 20 order2_1
SELL GFD 1003 30 order3_3
SELL GFD 1003 60 order3_4
SELL GFD 1002 20 order2_2
PRINT

test case 17
BUY GFD 9300 67 order0
MODIFY order0 SELL 1 85
PRINT
PRINT
SELL GFD 1500 71 order1
CANCEL order0
PRINT
SELL IOC 4700 64 order2
BUY GFD 6500 54 order3
CANCEL order2
MODIFY order1 SELL 1 84
CANCEL order3
BUY GFD 3800 84 order4
SELL IOC 3700 87 order5
MODIFY order0 BUY 1 61
BUY IOC 8500 53 order6
PRINT
PRINT
MODIFY order1 SELL 1 64
BUY IOC 5200 41 order7
BUY IOC 8300 0 order8
BUY IOC 6300 25 order9
MODIFY order3 BUY 1 24
PRINT
SELL GFD 200 56 order10
SELL GFD 8100 7 order11
SELL IOC 300 65 order12
PRINT
MODIFY order1 BUY 1 90
BUY GFD 5700 23 order13
MODIFY order10 BUY 1 72
SELL GFD 4300 41 order14
SELL GFD 7400 74 order15
SELL IOC 900 18 order16
SELL IOC 6400 79 order17
CANCEL order13
MODIFY order11 SELL 1 35
CANCEL order10
CANCEL order16
CANCEL order6
CANCEL order9
MODIFY order3 BUY 1 0
PRINT
BUY IOC 9300 86 order18
PRINT
PRINT
MODIFY order0 SELL 1 50
SELL IOC 6900 84 order19
BUY IOC 2200 56 order20
SELL IOC 8000 48 order21
BUY GFD 7700 30 order22

test case 30
SELL GFD 100 100 one
SELL GFD 100 100 two
BUY IOC 100 10 three
BUY IOC 100 10 three
BUY IOC 100 10 three
BUY IOC 100 10 three
PRINT

*/
