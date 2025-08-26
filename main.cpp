#include <iostream>
#include <vector>
#include <algorithm>
#include <format>


struct Item {
	std::string itemId;
	int itemPrice;

	void print() {
		std::cout << "Item ID: " << itemId << ", Item Price: " << itemPrice << '\n';
	}
};

class ItemList {
	std::vector<Item> itemList {};

public:
	void addItem(std::string itemId, int itemPrice) {
		Item newItem {itemId, itemPrice};
		itemList.push_back(newItem);
	}

	void printList() {
		for(Item item : itemList) {
			item.print();
		}
	}

	void updateItemPrice() {
		std::cout << "Enter Item Id: ";
		std::string itemId;
		std::cin >> itemId;

		std::cout << "Enter New Price: ";
		int newPrice;
		std::cin >> newPrice;

		for (Item& item : itemList) {
			if (item.itemId == itemId) {
				item.itemPrice = newPrice; 				
			}
		}
	}

	void deleteItems() {
		std::cout << "Enter Item Id: ";
		std::string itemIdtobeDeleted;
		std::cin >> itemIdtobeDeleted;

		itemList.erase(std::remove_if(itemList.begin(), itemList.end(),
			[&itemIdtobeDeleted](const Item& item) {
				return item.itemId == itemIdtobeDeleted;
			}), itemList.end());
	}

	void displayItemsAbove500() {
		int count {};
		std::vector<std::string> itemIds {};

		for (Item& item : itemList) {
			if (item.itemPrice > 500) {
				count++;
				itemIds.push_back(item.itemId);
			}
		}

		std::cout << "Count of items with prices exceeding Rs.500: " << count << '\n';
		std::cout << "Item list with prices exceeding Rs.500: ";
		for(int i {}; i < itemIds.size(); i++) {
			if(itemIds.size() == (i + 1)) {
				std::cout << itemIds[i] << '\n';
			} else {
				std::cout << itemIds[i] << ", ";
			}
		}
	}

	Item findbyItemId(std::string itemId) {
		for (Item& item : itemList) {
			if (item.itemId == itemId) {
				return item;
			}
		}
		return Item {"", -1};
	}
};

class order {
	Item item {};
	double quantity {};
	double discount {};
	int price {};

public:

	void setItem(std::string itemId, ItemList itemList) {
		item = itemList.findbyItemId(itemId);
	}

	void setQuantity(int quantityBykg) {
		quantity = quantityBykg;
	}

	double getQuantity() {
		return quantity;
	}

	void calcPrice() {
		price = item.itemPrice * quantity;
	}

	void calcDiscount() {
		if (item.itemId == "1005" && quantity > 5) {
			price -= price * 20 / 100;
		} else if (item.itemId == "1007" && quantity > 2.50) {
			price -= price * 5 / 100;
		}
	}

	int getPrice() {
		return price;
	}

	std::string getItemId() {
		return item.itemId;
	}
};

class ShoppingCart {
	std::vector<order> shoppingCart {};
	int amount {};

public:
	void addItem(std::string itemId, double quantity, ItemList& itemList) {
		order newPurchase;

		newPurchase.setItem(itemId, itemList);
		newPurchase.setQuantity(quantity);
		newPurchase.calcPrice();
		newPurchase.calcDiscount();

		shoppingCart.push_back(newPurchase);
	}

	int calcAmount() {
		for (order& order : shoppingCart) {
			amount += order.getPrice();
		}

		return amount;
	}  

	void print() {
		std::cout << "Total amount: " << amount;
	}

	void execute(ItemList itemList) {

		while (true) {
			std::cout << "Enter item ID: ";
			std::string itemId;
			std::cin >> itemId;

			std::cout << "Quantity(kg): ";
			double quantity;
			std::cin >> quantity;

			addItem(itemId, quantity, itemList);

			std::cout << "Add the new item to the bill (1.Yes or 2.No): ";
			int command;
			std::cin >> command;

			if (command == 2) {
				break;
			}
		}
		printBill();
	}

	void printBill() {

		std::cout << "Item ID		Quantity(Kg)		Price(Rs.)" << '\n';

		for (order& order : shoppingCart) {
			std::cout << order.getItemId() << "		" << order.getQuantity() << "			" << order.getPrice() << '\n';
		}

		std::cout << "Total gross amount = " << calcAmount();
	}
};


int main() {

	ItemList vegetables;

	vegetables.addItem("1005", 650);
	vegetables.addItem("1007", 758);
	vegetables.addItem("1009", 105);
	vegetables.addItem("1004", 400);
	vegetables.addItem("1006", 410);

	vegetables.addItem("1008", 750);
	vegetables.addItem("1003", 800);

	vegetables.printList();

	ShoppingCart customer;
	customer.addItem("1005", 1, vegetables);
	customer.addItem("1007", 1, vegetables);
	customer.execute(vegetables);

	return 0;
}
