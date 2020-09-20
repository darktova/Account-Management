#include "AccFile.h"

AccFile::AccFile(const std::string s) throw(OpenError)
{
    f.open(s);
    if (!f.is_open())
        throw OpenError(s);
}

long AccFile::append(Account& acc) throw(WriteError)
{
    // Seek to end,
    f.seekp(0L, std::ios::end);

    // save the position.
    long pos = f.tellp();

    if (!f)
        throw WriteError(name);

    // To write the TypeId
    TypeId id = acc.getTypeId();
    f.write((char*)&id, sizeof(id));

    if (!f)
        throw WriteError(name);
    else
        // To write an object to the file.
        acc.write(f);
    
    if (!f)
        throw WriteError(name);
    else
        return pos;
}

Account* AccFile::retrieve(long pos) throw(ReadError)
{
    // Negative position
    if (!pos)
        throw ReadError(name);

    // Seek to position
    f.seekg(0L, pos);

    // f stream ok?
    if (!f.good())
        return nullptr;

    // Getting type id from file
    TypeId id;
    f.read((char*)&id, sizeof(id));

    // Result
    Account* acc = new Account();
    
    // Read type id equal to current one
    if ((id == acc->getTypeId()) 
        && (f.good()))
    {
        // Read data from file
        acc->read(f);

        // Return result
        return acc;
    }

    // The type id is differ from Account
    return nullptr;
}

void AccFile::display() throw(ReadError)
{
    Account acc, * pAcc = NULL;
    DepAcc depAcc;
    SavAcc savAcc;
    TypeId id;
    
    if (!f.seekg(0L))
        throw ReadError(name);

    std::cout << "\nThe account file: \n";
    while (f.read((char*)&id, sizeof(TypeId)))
    {
        switch (id)
        {
        case ACCOUNT: pAcc = &acc;
            break;
        case DEP_ACC: pAcc = &depAcc;
            break;
        case SAV_ACC: pAcc = &savAcc;
            break;
        default: std::cerr << "Invalid flag in account file\n";
            exit(1);
        }

        if (!pAcc->read(f))
            break;

        pAcc->display();

        // Go on with return
        std::cin.get(); 
    }
    
    if (!f.eof())
        throw ReadError(name);

    f.clear();
}