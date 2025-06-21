#include <unordered_map>
#include <stdexcept>
#include <string>

struct AccountNotFoundError: std::runtime_error {
    AccountNotFoundError(long id): std::runtime_error{"Account not found: " + std::to_string(id)} {
    }
};

struct AccountDatabase
{
    virtual void setAmount(long id, double amount) = 0;

    virtual double getAmount(long id) = 0;

    virtual ~AccountDatabase() = default;
};


struct InMemoryAccountDatabase: AccountDatabase {
    InMemoryAccountDatabase(): db{} {}

    void setAmount(long id, double amount) noexcept override{
        db.insert({id, amount});
    }

    double getAmount(long id) override {
        auto it = db.find(id);
        if (it == db.end()) { throw AccountNotFoundError{id}; }
        return it->second;
    }


    private:
    std::unordered_map<long, double> db;
   


};