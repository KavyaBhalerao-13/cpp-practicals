#include <iostream>
#include <memory>   // for std::unique_ptr, std::shared_ptr
#include <string>
#include <utility>  // for std::move

class Resource {
private:
    std::string name;

public:
    explicit Resource(const std::string& n) : name(n) {
        std::cout << "[Acquired] Resource: " << name << "\n";
    }

    ~Resource() {
        std::cout << "[Released] Resource: " << name << "\n";
    }

    void use() const {
        std::cout << "  -> Using resource: " << name << "\n";
    }
};

// Function that shares ownership of a Resource
void workerModule(std::shared_ptr<Resource> sharedRes) {
    std::cout << "  [workerModule] Inside function. Owner count = " << sharedRes.use_count() << "\n";
    sharedRes->use();
    // When this function ends, sharedRes is destroyed and use_count decreases by 1
}

int main() {
    std::cout << "--- 1. std::unique_ptr (Exclusive Ownership) ---\n";
    {
        // Only ONE unique_ptr can own this Resource at a time
        std::unique_ptr<Resource> u1(new Resource("Database_Connection"));
        u1->use();

        // std::unique_ptr<Resource> u2 = u1; // ERROR: Copying is not allowed!

        // Ownership can only be MOVED
        std::unique_ptr<Resource> u2 = std::move(u1);
        std::cout << "  Ownership moved from u1 to u2.\n";
        std::cout << "  u1 is now: " << (u1 == nullptr ? "nullptr" : "valid") << "\n";
        u2->use();

        // u2 goes out of scope here -> Resource is automatically deleted!
    }

    std::cout << "\n--- 2. std::shared_ptr (Shared Ownership) ---\n";
    {
        // Multiple shared_ptrs can share ownership of the same Resource
        std::shared_ptr<Resource> s1 = std::make_shared<Resource>("Shared_Config");
        std::cout << "  s1 created. Owner count = " << s1.use_count() << "\n";

        {
            std::shared_ptr<Resource> s2 = s1; // Copying is allowed
            std::cout << "  s2 copied from s1. Owner count = " << s1.use_count() << "\n";
            workerModule(s2); // Temporarily increases count to 3
            std::cout << "  Back from workerModule. Owner count = " << s1.use_count() << "\n";
        } // s2 goes out of scope here; Resource is STILL alive because s1 owns it

        std::cout << "  s2 destroyed. Owner count = " << s1.use_count() << "\n";
        // s1 goes out of scope here -> count hits 0 -> Resource is automatically deleted!
    }

    std::cout << "\n--- 3. Stress Test (1000 Iterations with RAII) ---\n";
    for (int i = 0; i < 1000; ++i) {
        std::unique_ptr<int[]> tempArray(new int[100]);
        tempArray[0] = i;
        // Automatically freed at the end of every loop iteration (no delete[] needed)
    }
    std::cout << "  1000 iterations completed cleanly with zero manual delete calls.\n";

    return 0;
}