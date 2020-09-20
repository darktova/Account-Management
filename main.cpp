#include "IndexFileSystem.h"

int main()
{
	try
	{
		IndexFileSystem database("AccountTest");
	
		Account acc1("Vivi", 490UL, 12340.57);
		database.insert(acc1);
		
		SavAcc acc2("Ulla", 590UL, 4321.19, 2.5);
		database.insert(acc2);
		
		DepAcc acc3("Jeany", 390UL, 12340.20, 10000.0, 12.9);
		database.insert(acc3);
		
		database.IndexFile::display();
		std::cin.get();
		
		database.AccFile::display();
		
		unsigned long key;
		std::cout << "Key? "; std::cin >> key;
		
		if (database.search(key) != -1)
			std::cout << "Key " << key << " found\n";
		else
			std::cout << "Key " << key << " not found\n";
		
		Account* pAcc = database.retrieve(key);
		
		if (pAcc != NULL)
		{
			pAcc->display();
			delete pAcc;
			pAcc = NULL;
		}
		else std::cout << "Retrieving failed\n";
	}
	catch (OpenError& err)
	{
		std::cerr << "Error on opening the file:" << err.getName() << '\n';
		exit(1);
	}
	catch (WriteError& err)
	{
		std::cerr << "Error on writing into the file: "
			<< err.getName() << '\n';
		exit(1);
	}
	catch (ReadError& err)
	{
		std::cerr << "Error on reading from the file: "
			<< err.getName() << '\n';
		exit(1);
	}
	catch (...)
	{
		std::cerr << " Unhandled Exception" << '\n';
		exit(1);
	}
	
	return 0;
}