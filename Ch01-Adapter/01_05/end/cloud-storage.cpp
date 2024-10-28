#include <iostream>
#include <string>
#include <memory>
#include <random>

using namespace std;

// Abstract CloudStorage interface
class CloudStorage
{
public:
    virtual bool uploadContents(const string& content) = 0;
    virtual int getFreeSpace() = 0;
    virtual ~CloudStorage() = default;
};

// CloudDrive service
class CloudDrive : public CloudStorage
{
public:
    bool uploadContents(const string& content) override
    {
        cout << "Uploading " << content.length() << " bytes to CloudDrive." << endl;
        return true;
    }

    int getFreeSpace() override
    {
        // Using C++ <random> for cross-platform random number generation
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0, 20); // Random space between 0 and 20 GB

        int size = dist(gen);
        cout << "Available CloudDrive storage: " << size << "GB" << endl;
        return size;
    }
};

// FastShare service
class FastShare : public CloudStorage
{
public:
    bool uploadContents(const string& content) override
    {
        cout << "Uploading " << content.length() << " bytes to FastShare." << endl;
        return true;
    }

    int getFreeSpace() override
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0, 10); // Random space between 0 and 10 GB

        int size = dist(gen);
        cout << "Available FastShare storage: " << size << "GB" << endl;
        return size;
    }
};

// 3rd party VirtualDrive service (non-CloudStorage-compatible)
class VirtualDrive
{
public:
    bool uploadData(const string& data, const int uniqueID)
    {
        cout << "Uploading to VirtualDrive: \"" << data << "\" with ID: " << uniqueID << endl;
        return true;
    }
    
    int usedSpace()
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0, totalSpace); // Random used space
        return dist(gen);
    }
    
    int totalSpace = 15;
};

// Adapter to make VirtualDrive compatible with CloudStorage interface
class VirtualDriveAdapter : public CloudStorage
{
public:
    VirtualDriveAdapter(std::shared_ptr<VirtualDrive> vDrive) : vDrive_(vDrive) {}

    bool uploadContents(const string& content) override
    {
        int uniqueID = generateUniqueID();
        return vDrive_->uploadData(content, uniqueID);
    }

    int getFreeSpace() override
    {
        int used = vDrive_->usedSpace();
        int freeSpace = vDrive_->totalSpace - used;
        cout << "Available VirtualDrive storage: " << freeSpace << "GB" << endl;
        return freeSpace;
    }

private:
    std::shared_ptr<VirtualDrive> vDrive_;
    
    int generateUniqueID()
    {
        static int id = 0;
        return ++id; // Generate a simple incremental ID
    }
};

int main()
{
    // Create an array of pointers to CloudStorage objects, including the adapter for VirtualDrive
    const std::unique_ptr<CloudStorage> cloudServices[]
    {
        std::make_unique<CloudDrive>(),
        std::make_unique<FastShare>(),
        std::make_unique<VirtualDriveAdapter>(std::make_shared<VirtualDrive>())
    };

    // Test content to upload
    const string content = "Beam me up, Scotty!";

    // Iterate through the array and invoke the uploadContents and getFreeSpace methods on each object
    for (const auto& service : cloudServices)
    {
        service->uploadContents(content);
        service->getFreeSpace();
        cout << endl;
    }

    return 0;
}
