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
    f.clear();
    f.seekg(pos);

    // f stream ok?
    if (!f.good())
        throw ReadError(name);

    // Getting type id from file
    TypeId id;
    f.read((char*)&id, sizeof(id));
    
    // Getting suitable type
    Account* acc = nullptr;
    switch (id)
    {
    case ACCOUNT:
        acc = new Account();
        break;
    case DEP_ACC:
        acc = new DepAcc();
        break;
    case SAV_ACC:
        acc = new SavAcc();
        break;
    }

    // Exc. handling
    if (!acc->read(f)) 
        throw ReadError(name);

    return acc;
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